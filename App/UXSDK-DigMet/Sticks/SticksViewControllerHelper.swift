//
//  SticksViewControllerHelper.swift
//  UXSDK-DigMet
//
//  Created by Andreas Gising on 2020-08-31.
//  Copyright © 2020 DJI. All rights reserved.
//

import UIKit

// https://www.hackingwithswift.com/books/ios-swiftui/how-to-save-images-to-the-users-photo-library
class imageSaver: NSObject {
    func writeToPhotoAlbum(image: UIImage) {
        UIImageWriteToSavedPhotosAlbum(image, self, #selector(saveError), nil)
    }
    @objc func saveError(_ image: UIImage, didFinishSavingWithError error: Error?, contextInfo: UnsafeRawPointer) {
        print("Save Finished")
    }
}

class my_Helper: NSObject {
    func my_test(number: Int) -> Int{
        return -number
    }
}

