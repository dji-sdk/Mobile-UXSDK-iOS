# DJI UX SDK for iOS

## What Is This?

The UX SDK is a suite of product agnostic UI objects that fast tracks the development of iOS applications using the [DJI Mobile SDK](http://developer.dji.com/mobile-sdk/).

## Get Started Immediately

### UX SDK Installation with CocoaPods

Since this project has been integrated with [DJI iOS UX SDK CocoaPods](https://cocoapods.org/pods/DJI-UXSDK-iOS) now, please check the following steps to install **DJISDK.framework** using CocoaPods after you downloading this project:

**1.** Install CocoaPods

Open Terminal and change to the download project's directory, enter the following command to install it:

~~~
sudo gem install cocoapods
~~~

The process may take a long time, please wait. For further installation instructions, please check [this guide](https://guides.cocoapods.org/using/getting-started.html#getting-started).

**2.** Install UX SDK and DJIWidget with CocoaPods in the Project

Run the following command in the **ObjcSampleCode** and **SwiftSampleCode** paths:

~~~
pod install
~~~

If you install it successfully, you should get the messages similar to the following:

~~~
Analyzing dependencies
Downloading dependencies
Installing DJI-SDK-iOS (4.16)
Installing DJI-UXSDK-iOS (4.16)
Installing DJIWidget (1.6.6)
Installing DJIFlySafeDatabaseResource (01.00.01.18)
Generating Pods project
Integrating client project

[!] Please close any current Xcode sessions and use `UXSDKOCSample.xcworkspace` for this project from now on.
Pod installation complete! There is 1 dependency from the Podfile and 1 total pod
installed.
~~~

> **Note**: If you saw "Unable to satisfy the following requirements" issue during pod install, please run the following commands to update your pod repo and install the pod again:
>
> ~~~
> pod repo update
> pod install
> ~~~

### Run Sample Code

Developers will need to setup the App Key by editing the sample code's info.plist, [after generating their unique App Key](https://developer.dji.com/mobile-sdk/documentation/quick-start/index.html#generate-an-app-key).

For the Objective-C sample app, the key value **DJISDKAppKey** should to be added to "Info.plist" with your unique app key as a string.  

For the Swift sample app, the **DJISDKAppKey** is present in the "Info.plist" - developers just need to add their unique key.
In both cases developers will still need to update the [Bundle Identifier](http://developer.dji.com/user/mobile-sdk/ios-configuration/) .

One of DJI's aircraft or handheld cameras will be required to run the sample application.  

### DJIWidget Integration

Starting from DJI iOS SDK 4.7, we have replaced the **VideoPreviewer** with **DJIWidget** for video decoding. Please add the following line to your Podfile to install it to your Xcode project:

~~~
pod 'DJIWidget', '~> 1.6.6'
~~~

> Note: Remember to add the `use_frameworks!` in the pod file.

## Learn More about DJI UX SDK

Please visit [UX SDK Introduction](http://developer.dji.com/mobile-sdk/documentation/introduction/ux_sdk_introduction.html) for more details.

## Development Workflow

From registering as a developer, to deploying an application, the following will take you through the full Mobile SDK Application development process:

- [Prerequisites](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-prerequisits.html)
- [Register as DJI Developer & Download SDK](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-register.html)
- [Integrate SDK into Application](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-integrate.html)
- [Run Application](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-run.html)
- [Testing, Profiling & Debugging](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-testing.html)
- [Deploy](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-deploy.html)

## Feedback

We’d love to have your feedback as soon as possible. Reach out to us when you hit roadblocks, or want to talk through something. At a minimum please let us know:

- What improvements would you like to see?
- What is hard to use or inconsistent with your expectations?
- What is good?
- Any bugs you come across.

## Support

You can get support from DJI with the following methods:

- Post questions, keep up to date on DJI developer news and contribute to the community by visiting the [DJI's Developer Forum here](https://forum.dji.com/forum-139-1.html?from=developer)
- dev@dji.com

## Join Us

DJI is looking for all kinds of Software Engineers to continue building the Future of Possible. Available positions in Shenzhen, China and around the world. If you are interested, please send your resume to <software-sz@dji.com>. For more details, and list of all our global offices, please check <https://we.dji.com/jobs_en.html>.

DJI 招软件工程师啦，based在深圳，如果你想和我们一起把DJI产品做得更好，请发送简历到 <software-sz@dji.com>.  详情请浏览 <https://we.dji.com/zh-CN/recruitment>.


