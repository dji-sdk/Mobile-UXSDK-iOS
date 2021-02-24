#
#  Be sure to run `pod spec lint DJI-UXSDK-iOS.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|

  s.name            = "DJI-UXSDK-iOS"
  s.version         = "4.14"
  s.summary         = "DJI UX SDK for iOS"
  s.homepage        = "https://github.com/dji-sdk/Mobile-UXSDK-iOS"
  s.license         = { :type => 'CUSTOM', :text => <<-LICENSE
****************************************************************************************************************************

DJI UX SDK for iOS is offered under DJI's END USER LICENSE AGREEMENT. You can obtain the license from the below link:

http://developer.dji.com/policies/eula/

****************************************************************************************************************************

Sample code is offered under MIT License (See below).

The MIT License (MIT)
Copyright (c) 2018-2020 DJI

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************************************************************
    LICENSE
  }

  s.author          = { "DJI SDK" => "dev@dji.com" }
  s.platform        = :ios, '10.0'
  s.requires_arc    = true
  s.source       = { :http => "https://terra-1-g.djicdn.com/71a7d383e71a4fb8887a310eb746b47f/msdk/iOS_UX_SDK_4.14_20210223.zip" }

  s.ios.vendored_frameworks = 'iOS_UX_SDK/DJIUXSDK.framework'

  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => "arm64 armv7 i386" }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => "arm64 armv7 i386" }

end
