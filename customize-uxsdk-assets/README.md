How to Customize Image Assets in UXSDK

Note: Your asset needs to be sized and named the same as the exising asset or it will not be displayed correctly by the framework. If UXSDK is not able to find the asset it is expecting, it will draw a small orange square around the center of where the asset will be to help with visibility.

1. Navigate the attached .xcassets folders to find the asset you'd like to change.
2. Remove the image files from .xcassets. Please DO NOT remove any other files, including the contents.json.
3. Add the image files you'd like to use. Make sure they have the same name, @2x/@3x, are in the same location, and the same size as the original files.
4. Run the asset-swap.sh script. The script will output an Assets.car file. 
5. Replace the Assets.car file inside DJIUXSDK.framework with the newly generated Assets.car file.
6. You may need to clear DerivedData and reset your device in order for these changes to take effect.
7. UXSDK will now automatically pick up and use your custom image file.
