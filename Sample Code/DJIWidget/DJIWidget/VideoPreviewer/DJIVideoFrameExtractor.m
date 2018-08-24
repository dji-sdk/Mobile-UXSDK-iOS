//
//  Video.m
//  iFrameExtractor
//
//  Created by lajos on 1/10/10.
//  Copyright 2010 www.codza.com. All rights reserved.
//

#import "DJIVideoFrameExtractor.h"
#import "DJIVideoHelper.h"
#import <sys/time.h>
#import <pthread.h>

#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavcodec/avcodec.h"

@interface DJIVideoFrameExtractor (){
    pthread_mutex_t _frameMutex; //mutex for pframe object
    AVFrame *_pFrame;   //frame
    
    pthread_mutex_t _codecMutex; //mutex for codec ctx and parser object
    BOOL _codecInitited;
    AVCodecContext *_pCodecCtx; //decode
    AVCodecParserContext *_pCodecPaser;
    VideoFrameH264Raw* _frameInfoList;
    int _frameInfoListCount;
	uint32_t _frameUuidCounter;
}

@end

@implementation DJIVideoFrameExtractor

#define _CP_YUV_FRAME_(dst, src, linesize, width, height) \
do{ \
if(dst == NULL || src == NULL || linesize < width || width <= 0)\
break;\
uint8_t * dd = (uint8_t* ) dst; \
uint8_t * ss = (uint8_t* ) src; \
int ll = linesize; \
int ww = width; \
int hh = height; \
for(int i = 0 ; i < hh ; ++i) \
{ \
memcpy(dd, ss, width); \
dd += ww; \
ss += ll; \
} \
}while(0)

#define DJIPigeonResetFrameStateForFlag(__state__,__flag__)     do{\
(__state__) &= (~(__flag__));\
} while(0)

-(id) init{
    self = [self initExtractor];
    return self;
}

-(void)getYuvFrame:(VideoFrameYUV *)yuv
{
    pthread_mutex_lock(&_frameMutex);
    do{
        if(!_pFrame) break ;
        
        //get info from current avframe
        int input_width = _pFrame->width, input_height = _pFrame->height;
        int line_size[3] = {0};
        line_size[0] = _pFrame->linesize[0];
        line_size[1] = _pFrame->linesize[1];
        line_size[2] = _pFrame->linesize[2];
        
        if(yuv->luma != NULL && ((yuv->width != input_width) || (yuv->height != (input_height))))
        {
            free(yuv->luma);
            free(yuv->chromaB);
            free(yuv->chromaR);
            
            yuv->luma = NULL;
            yuv->chromaB = NULL;
            yuv->chromaR = NULL;
        }
        
        if(yuv->luma == NULL)
        {
            yuv->luma = (uint8_t*) malloc(input_width * input_height);
            yuv->chromaB = (uint8_t*) malloc(input_width * input_height/4);
            yuv->chromaR = (uint8_t*) malloc(input_width * input_height/4);
        }
        
        _CP_YUV_FRAME_(yuv->luma, _pFrame->data[0], _pFrame->linesize[0], input_width, input_height);
        
        _CP_YUV_FRAME_(yuv->chromaB, _pFrame->data[1], _pFrame->linesize[1], input_width/2, input_height/2);
        _CP_YUV_FRAME_(yuv->chromaR, _pFrame->data[2], _pFrame->linesize[2], input_width/2, input_height/2);
        
        yuv->width = input_width;
        yuv->height = input_height;
        yuv->frame_uuid = H264_FRAME_INVALIED_UUID;
        memset(&yuv->frame_info, 0, sizeof(VideoFrameH264BasicInfo));
        
        if (_pFrame->poc < _frameInfoListCount) {
            yuv->frame_uuid = _frameInfoList[_pFrame->poc].frame_uuid;
            yuv->frame_info = _frameInfoList[_pFrame->poc].frame_info;
        }
    }while (false);
    pthread_mutex_unlock(&_frameMutex);
}

#undef _CP_YUV_FRAME_

-(void) setShouldVerifyVideoStream:(BOOL)shouldVerify
{
    _shouldVerifyVideoStream = shouldVerify;
}

-(void) privateParseVideo:(uint8_t*)buf length:(int)length withOutputBlock:(void (^)(AVPacket* frame))block
{
    // Need padding for FFMpeg. Otherwise Address Sanitizer will complain heap overflow.
    size_t lengthWithPadding = length + FF_INPUT_BUFFER_PADDING_SIZE;
    uint8_t *bufWithPadding = malloc(lengthWithPadding);
    memset(bufWithPadding, 0, lengthWithPadding);
    memcpy(bufWithPadding, buf, length);
    
    uint8_t *paserBuffer_In = bufWithPadding;
    int paserLength_In = (int)length;
    int paserLen = 0;
    //获取到帧信息后回调的帧数
    NSUInteger callbackCount = 0;
    //成功组帧数目
    NSUInteger packetFoundCount = 0;
    
    while (paserLength_In > 0) {
        BOOL shouldDoCallback = NO;
        AVPacket packet;
        av_init_packet(&packet);
        pthread_mutex_lock(&_codecMutex);
        do{
            if (_pCodecCtx == NULL
                || _pCodecPaser == NULL) {
                break;
            }
            
            paserLen = av_parser_parse2(_pCodecPaser,
                                        _pCodecCtx,
                                        &packet.data,
                                        &packet.size,
                                        paserBuffer_In,
                                        paserLength_In,
                                        AV_NOPTS_VALUE,
                                        AV_NOPTS_VALUE,
                                        AV_NOPTS_VALUE);
            
            paserLength_In -= paserLen;
            paserBuffer_In += paserLen;
            
            if (packet.size <= 0) {
                break;
            }
            packetFoundCount++;
            //实际图传是1080P，但是组帧时解析得到是1088P，后面解码器会自动裁切成1080P，所以这里需要先保证分辨率正确
            if(_pCodecPaser->height_in_pixel == 1088){
                //1080p hack
                _pCodecPaser->height_in_pixel = 1080;
            }
			
			//P4P拍全景的时候图传宽度在1088/1080间切换，WM240会有1088x720的分辨率，这里暂时做了特殊判断
			if (_pCodecPaser->width_in_pixel == 1088
				&& [self.controlHandler isNeedFitFrameWidth]) {
				_pCodecPaser->width_in_pixel = 1080;
			}
			
            bool isSpsPpsFound = false;
            _outputWidth = _pCodecPaser->width_in_pixel;
            _outputHeight = _pCodecPaser->height_in_pixel;
            
            isSpsPpsFound = _pCodecPaser->frame_has_sps?YES:NO;
            
            if (isSpsPpsFound) {
                if (_frameInfoListCount != _pCodecPaser->max_frame_num_plus1) {
                    //recreate frame info list
                    if (_frameInfoList) {
                        free(_frameInfoList);
                        _frameInfoList = nil;
                    }
                    
                    if (_pCodecPaser->max_frame_num_plus1) {
                        _frameInfoListCount = _pCodecPaser->max_frame_num_plus1;
                        _frameInfoList = malloc(sizeof(VideoFrameH264Raw)*_frameInfoListCount);
                        memset(_frameInfoList, 0, _frameInfoListCount*sizeof(VideoFrameH264Raw));
                    }
                }
            }
            
            int rate = 0;
            if (_pCodecPaser->frame_rate_den) {
                // If the stream is encoded by DJI's encoder, the frame rate
                // should be double of the value from the parser.
                double scale = _usingDJIAircraftEncoder?2.0:1.0;
                rate = (int)(0.5+_pCodecPaser->frame_rate_num/(scale*_pCodecPaser->frame_rate_den));
                _frameRate = rate;
            }
            
            if (_shouldVerifyVideoStream) {
                if (isSpsPpsFound) {
                    _shouldVerifyVideoStream = NO;
                }
                else{
                    break;
                }
            }
            
            if (!_shouldVerifyVideoStream){
                //need do callback for this frame
                shouldDoCallback = YES;
            }
        }while(false);
        pthread_mutex_unlock(&_codecMutex);
        
        if(shouldDoCallback){
            callbackCount++;
            if (block != nil){
                block(&packet);
            }
        }
        
        av_free_packet(&packet);
    }
	
	if (callbackCount == 0 && packetFoundCount > 0) {
		[self.controlHandler updateIFrameDecodeStateIsMissed:YES];
	}
	
    if (bufWithPadding){
        free(bufWithPadding);
    }
}


-(void) parseVideo:(uint8_t *)buf length:(int)length withFrame:(void (^)(VideoFrameH264Raw *))block{
    
    [self privateParseVideo:buf length:length withOutputBlock:^(AVPacket* frame) {
        if (!block
            || !frame
            || !frame->data) {
            return;
        }
        int frameSize = frame->size;
        
        VideoFrameH264Raw* outputFrame = (VideoFrameH264Raw*)malloc(sizeof(VideoFrameH264Raw) + frameSize);
        outputFrame->type_tag = TYPE_TAG_VideoFrameH264Raw;
        memset(outputFrame, 0, sizeof(VideoFrameH264Raw));
        memcpy(outputFrame+1, frame->data, frameSize);
        
        [self popNextFrameUUID];
        
        outputFrame->frame_uuid = _frameUuidCounter;
        outputFrame->frame_size = frame->size;
		
		BOOL shouldCallback = YES;
		if (self.controlHandler) {
			shouldCallback = [self.controlHandler parseSeiInfoWithFrameBuffer:frame->data length:frame->size outputFrame:outputFrame];
			if ((outputFrame->frame_info.frame_sei_info.fov_state == DJISEIInfoLiveViewFOVState_Undefined
				 || outputFrame->frame_info.frame_sei_info.fov_state == DJISEIInfoLiveViewFOVState_GDC_No_Needed)
				&& outputFrame->frame_info.frame_sei_info.has_lut_idx != 0){
				outputFrame->frame_info.frame_sei_info.has_lut_idx = 0;
				outputFrame->frame_info.frame_sei_info.lut_idx = 0;
				outputFrame->frame_info.frame_sei_info.fov_state = DJISEIInfoLiveViewFOVState_GDC_No_Needed;
			}
		}

        pthread_mutex_lock(&_codecMutex);
        
        if(_pCodecPaser){ //patch by amanda
            
            outputFrame->frame_info.frame_index = _pCodecPaser->frame_num;
            outputFrame->frame_info.max_frame_index_plus_one = _pCodecPaser->max_frame_num_plus1;
            
            if (outputFrame->frame_info.frame_index >= outputFrame->frame_info.max_frame_index_plus_one) {
                // something wrong;
            }
            //实际图传是1080P，但是组帧时解析得到是1088P，后面解码器会自动裁切成1080P，所以这里需要先保证分辨率正确
            if(_pCodecPaser->height_in_pixel == 1088){
                //1080p hack
                _pCodecPaser->height_in_pixel = 1080;
            }

			if (_pCodecPaser->width_in_pixel == 1088 &&
				[self.controlHandler isNeedFitFrameWidth]) {
				_pCodecPaser->width_in_pixel = 1080;
			}
			
            outputFrame->frame_info.width = _pCodecPaser->width_in_pixel;
            outputFrame->frame_info.height = _pCodecPaser->height_in_pixel;
            
            if (_pCodecPaser->frame_rate_den) {
                // If the stream is encoded by DJI's encoder, the frame rate
                // should be double of the value from the parser.
                double scale = _usingDJIAircraftEncoder?2.0:1.0;
                outputFrame->frame_info.fps = ceil(_pCodecPaser->frame_rate_num/(scale*_pCodecPaser->frame_rate_den));
            }
            //由于在pigeon方案中，天空端图传模式选择流畅模式，会有60fps的码流，为了避免额外的开销，在这种情况下使能force_30_fps，保证只会渲染成30fps，并且全帧编码也使用30fps
            if (outputFrame->frame_info.frame_sei_info.force_30_fps != 0){
                outputFrame->frame_info.fps = 30;//强制30fps
                _frameRate = 30;
            }
            
            outputFrame->frame_info.frame_poc = _pCodecPaser->output_picture_number;
            outputFrame->frame_info.frame_flag.has_sps = _pCodecPaser->frame_has_sps;
            outputFrame->frame_info.frame_flag.has_pps = _pCodecPaser->frame_has_pps;
            outputFrame->frame_info.frame_flag.has_idr = (_pCodecPaser->key_frame ==1)?1:0;
            outputFrame->frame_info.frame_flag.is_fullrange = NO; //we can only get this in sps, set this bit later
        }
        pthread_mutex_unlock(&_codecMutex);

		if (shouldCallback
            && block != nil
            && outputFrame != NULL){
            block(outputFrame);
            return;
        }
        if (outputFrame != NULL){
            free(outputFrame);
            outputFrame = NULL;
        }
    }];
}

-(void) decodeRawFrame:(VideoFrameH264Raw*)frame callback:(void(^)(BOOL b))callback{
    if (!frame) {
        if (callback) {
            callback(NO);
        }
        
        return;
    }
    
    AVPacket packet;
    av_init_packet(&packet);
    packet.data = frame->frame_data;
    packet.size = frame->frame_size;
    
    pthread_mutex_lock(&_codecMutex);
    
    if (_frameInfoListCount > frame->frame_info.frame_index) {
        _frameInfoList[frame->frame_info.frame_index] = *frame;
    }else{
    }
    
    int got_picture;
    pthread_mutex_lock(&_frameMutex);
    avcodec_decode_video2(_pCodecCtx, _pFrame, &got_picture, &packet);
    pthread_mutex_unlock(&_frameMutex);
    //实际图传是1080P，但是组帧时解析得到是1088P，后面解码器会自动裁切成1080P，所以这里需要先保证分辨率正确
    if (_pCodecCtx->height == 1088) {
        _pCodecCtx->height = 1080;
    }
    
    if (_pCodecCtx->width == 1088) {
        _pCodecCtx->width = 1080;
    }
    
    _outputWidth = _pCodecCtx->width;
    _outputHeight = _pCodecCtx->height;
    
    pthread_mutex_unlock(&_codecMutex);
    
    if (callback) {
        callback(got_picture);
    }
    av_free_packet(&packet);
}

-(id)initExtractor
{
    self = [super init];
    
    _usingDJIAircraftEncoder = YES;
    pthread_mutex_init(&_frameMutex, nil);
    pthread_mutex_init(&_codecMutex, nil);
    
    [self setupExtractor];
    return self;
}

-(void)setupExtractor{
    
    _frameRate = 0;
    _shouldVerifyVideoStream = YES;
    
    AVCodec *pCodec;
    
    pthread_mutex_lock(&_frameMutex);
    if(_pFrame == NULL){
        _pFrame = av_frame_alloc();
    }
    pthread_mutex_unlock(&_frameMutex);
    
    pthread_mutex_lock(&_codecMutex);
    if(_codecInitited == NO){
        av_register_all();
        
        pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
        _pCodecCtx = avcodec_alloc_context3(pCodec);
        _pCodecPaser = av_parser_init(AV_CODEC_ID_H264);
        if (_pCodecPaser == NULL) {
            // NSLog(@"Can't find H264 frame paser!");
        }
        _pCodecCtx->flags2|=CODEC_FLAG2_FAST;
        _pCodecCtx->thread_count = 2;
        //_pCodecCtx->thread_type = FF_THREAD_SLICE;
        _pCodecCtx->thread_type = FF_THREAD_FRAME;
        
        if(pCodec->capabilities&CODEC_FLAG_LOW_DELAY){
            _pCodecCtx->flags|=CODEC_FLAG_LOW_DELAY;
        }
        
        if (avcodec_open2(_pCodecCtx, pCodec, NULL)) {
            // NSLog(@"Could not open codec");
            //Could not open codec
        }
        
        _frameInfoListCount = 0;
        _frameInfoList = nil;
        NSLog(@"Frame Extractor Init param:%d %d %d %d %d",_pCodecCtx->ticks_per_frame,_pCodecCtx->delay,_pCodecCtx->thread_count,_pCodecCtx->thread_type,_pCodecCtx->active_thread_type);
        _codecInitited = YES;
    }
    pthread_mutex_unlock(&_codecMutex);
}

-(void)freeExtractor
{
    pthread_mutex_lock(&_frameMutex);
    if (_pFrame){
        av_free(_pFrame);
    }
    _pFrame = NULL;
    pthread_mutex_unlock(&_frameMutex);
    
    pthread_mutex_lock(&_codecMutex);
    if(_codecInitited == YES){
        
        if (_pCodecCtx) {
            avcodec_close(_pCodecCtx);
            av_free(_pCodecCtx);
            _pCodecCtx = NULL;
        }
        if (_pCodecPaser) {
            av_parser_close(_pCodecPaser);
            av_free(_pCodecCtx);
            _pCodecPaser = NULL;
        }
        
        if (_frameInfoList) {
            free(_frameInfoList);
            _frameInfoList = nil;
            _frameInfoListCount = 0;
        }
        
        _codecInitited = NO;
    }
    pthread_mutex_unlock(&_codecMutex);
}

- (void)updateDecodeResult:(BOOL)success {
	[self.controlHandler updateDecodeResult:success];
}

- (void)updateIFrameReceived {
	[self.controlHandler updateIFrameDecodeStateIsMissed:NO];
}

- (void)clearBuffer{
    [self freeExtractor];
    [self setupExtractor];
}

-(uint32_t) popNextFrameUUID{
    _frameUuidCounter++;
    if (_frameUuidCounter == H264_FRAME_INVALIED_UUID) {
        _frameUuidCounter++;
    }
    
    return _frameUuidCounter;
}

-(void)dealloc {
    [self freeExtractor];
    
    pthread_mutex_destroy(&_frameMutex);
    pthread_mutex_destroy(&_codecMutex);
}

-(void)setControlHandler:(id<DJIVideoDataFrameControlDelegate>)controlHandler{
    if (_controlHandler == controlHandler){
        return;
    }
    _controlHandler = controlHandler;
}

@end

