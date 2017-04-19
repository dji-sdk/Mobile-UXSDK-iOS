# DJI UILibrary for iOS

## What Is This?

The UILibrary is a suite of product agnostic UI objects that fast tracks the development of iOS applications using the [DJI Mobile SDK](http://developer.dji.com/mobile-sdk/).

## Get Started Immediately

### UILibrary Installation with CocoaPods

Since this project has been integrated with [DJI iOS UILibrary CocoaPods](https://cocoapods.org/pods/DJI-UILibrary-iOS) now, please check the following steps to install **DJISDK.framework** using CocoaPods after you downloading this project:

**1.** Install CocoaPods

Open Terminal and change to the download project's directory, enter the following command to install it:

~~~
sudo gem install cocoapods
~~~

The process may take a long time, please wait. For further installation instructions, please check [this guide](https://guides.cocoapods.org/using/getting-started.html#getting-started).

**2.** Install UILibrary with CocoaPods in the Project

Run the following command in the **ObjcSampleCode** and **SwiftSampleCode** paths:

~~~
pod install
~~~

If you install it successfully, you should get the messages similar to the following:

~~~
Analyzing dependencies
Downloading dependencies
Installing DJI-SDK-iOS (4.0.1)
Installing DJI-UILibrary-iOS (4.0.1.1.0.0)
Generating Pods project
Integrating client project

[!] Please close any current Xcode sessions and use `UILibOCSample.xcworkspace` for this project from now on.
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

For the Objective-C sample app, the key value **DJISDKAppKey** should to be added to Info.plist with your unique app key as a string.  

For the Swift sample app, the DJISDKAppKey is present in the Info.plist - developers just need to add their unique key.
In both cases developers will still need to update the [Bundle Identifier](http://developer.dji.com/user/mobile-sdk/ios-configuration/) .


One of DJI's aircraft or handheld cameras will be required to run the sample application.  

## Development Workflow

From registering as a developer, to deploying an application, the following will take you through the full Mobile SDK Application development process:

- [Prerequisites](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-prerequisits.html)
- [Register as DJI Developer & Download SDK](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-register.html)
- [Integrate SDK into Application](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-integrate.html)
- [Run Application](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-run.html)
- [Testing, Profiling & Debugging](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-testing.html)
- [Deploy](https://developer.dji.com/mobile-sdk/documentation/application-development-workflow/workflow-deploy.html)

## Learn More about DJI Products, UILibrary and the Mobile SDK

Please visit [DJI Mobile SDK Documentation](https://developer.dji.com/mobile-sdk/documentation/introduction/index.html) for more details.

## Core Concepts
UILibrary was designed around core concepts that help categorize the kind of UI elements available and their expectable behavior both at runtime and while being customized.

### Widgets
Widget represent the major part of the UI. They are small view which display a specific piece of information.

They may also offer a precise control point to a specific action - for instance, take off.

Widgets offer many different customization angle. You may simply edit the image assets provided inside the UILibrary framework, change the visual rendering of the information consumed or provide your own information logic and reuse the existing rendering.

### Widget Collections
Widget Collections are grouping objects which allow the developer to easily display a set of widgets in an orderly fashion without the hassle of building the organization mechanism.

They also provide structure for the widgets to look alike each other while inside the same collection and apply an interaction level to all as to offer potential customization points in behavior.

You can also create your own collections and add pre-existing widgets to them.

### Panels
Panels are more complex control elements. They are usually a lot more enclosed because they handle very complex logics.
They can be placed in your app's UI using native methods.

### Contents
Contents represent the element that usually populates the background of the UI.
FPV is the most commonly used today.
They come ready to use and may have direct interactions with other widgets/panels.


### Default Layout
The default layout is a fully functioning mini-DJI Go.
It uses all the elements of the UILibrary to give you the foundation of your app.

The default layout is easily changeable and configurable.

### Model
Finally, the Model is a high level data accessor living inside the UILibrary and directly built on top of the mobile SDK.

It registers intentions from UILibrary objects and provides the data to them while handling most of the SDK's life cycle events.

It is heavily used by widgets today and we recommend you using it in your custom work in the future.

## Support

You can get support from DJI with the following methods:

- [**DJI Forum**](http://forum.dev.dji.com/en)
- Post questions in [**Stackoverflow**](http://stackoverflow.com) using [**dji-sdk**](http://stackoverflow.com/questions/tagged/dji-sdk) tag
- dev@dji.com
