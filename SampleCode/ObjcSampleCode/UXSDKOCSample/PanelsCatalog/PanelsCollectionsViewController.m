//
//  PanelsCollectionsViewController.m
//  UXSDKOCSample
//
//  MIT License
//
//  Copyright © 2018-2020 DJI
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#import "PanelsCollectionsViewController.h"
#import <DJIUXSDK/DJIUXSDK.h>

#define WeakRef(__obj) __weak typeof(self) __obj = self
#define WeakReturn(__obj) if(__obj ==nil)return;

@interface PanelsCollectionsViewController ()

@property (weak, nonatomic) IBOutlet UIView *statusBarContainingView;
@property (strong, nonatomic) DUXStatusBarViewController *statusBarVC;
@property (strong, nonatomic) NSTimer *widgetMovingTimer;
@property (readwrite, nonatomic) DUXWidgetCollectionViewStack lastStack;

- (IBAction)onBackButtonClicked:(id)sender;

@end

@implementation PanelsCollectionsViewController

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    // You can also change the UI dynamically.
    self.widgetMovingTimer = [NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(moveWidget) userInfo:nil repeats:YES];
    self.lastStack = DUXWidgetCollectionViewStackFirst;
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    [self.widgetMovingTimer invalidate];
    self.widgetMovingTimer = nil;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.statusBarVC = [[DUXStatusBarViewController alloc] init];
    
    // Adding our DUXStatusBarViewController to our container in code.
    // This could be done in the storyboard
    [self addChildViewController:self.statusBarVC];
    [self.statusBarContainingView addSubview:self.statusBarVC.view];
    self.statusBarVC.view.translatesAutoresizingMaskIntoConstraints = NO;
    [self.statusBarVC.view.topAnchor constraintEqualToAnchor:self.statusBarContainingView.topAnchor].active = YES;
    [self.statusBarVC.view.bottomAnchor constraintEqualToAnchor:self.statusBarContainingView.bottomAnchor].active = YES;
    [self.statusBarVC.view.leadingAnchor constraintEqualToAnchor:self.statusBarContainingView.leadingAnchor].active = YES;
    [self.statusBarVC.view.trailingAnchor constraintEqualToAnchor:self.statusBarContainingView.trailingAnchor].active = YES;
    [self.statusBarVC didMoveToParentViewController:self];
    
    /*
     *  Customizing a predefined widget view collection
     */
    
    // Removing a pre-defined widget you don't want.
    UIView<DUXWidgetProtocol> *preflightChecklistWidget = [self.statusBarVC widgetAtIndex:1];
    
    if (preflightChecklistWidget)
    {
        [self.statusBarVC removeWidget:preflightChecklistWidget];
    }
    
    // Changing the edgeInset of a placed widget.
    DUXWidgetItem *widgetItem = [self.statusBarVC widgetItemAtIndex:0];
    if (widgetItem) {
        widgetItem.edgeInset = UIEdgeInsetsMake(10, widgetItem.edgeInset.left, 10, widgetItem.edgeInset.right);
    }
    
    // Switch stack for widgets in stack collections
    UIView<DUXWidgetProtocol> *batteryWidget = [self.statusBarVC widgetWithClass:[DUXBatteryWidget class]];
    if (batteryWidget) {
        [self.statusBarVC.statusBarView moveWidget:batteryWidget to:DUXWidgetCollectionViewStackFirst];
    }
    
    // We need to call reloadData to adjust the rendering, but we call it at the end to avoid redundant calls
    [self.statusBarVC.statusBarView reloadData];
    
}

- (void)moveWidget
{
    
    // Switch stack for widgets in stack collections

    UIView<DUXWidgetProtocol> *batteryWidget = [self.statusBarVC widgetWithClass:[DUXBatteryWidget class]];
    
    if (self.lastStack == DUXWidgetCollectionViewStackFirst) {
        self.lastStack = DUXWidgetCollectionViewStackLast;
    }else
    {
        self.lastStack = DUXWidgetCollectionViewStackFirst;
    }
    
    if (batteryWidget) {
        [self.statusBarVC.statusBarView moveWidget:batteryWidget to:self.lastStack];
    }
    
    WeakRef(target);
    dispatch_async(dispatch_get_main_queue(),^ {
        WeakReturn(target);
        [target.statusBarVC.statusBarView reloadData];
    });
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

- (IBAction)onBackButtonClicked:(id)sender {
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
