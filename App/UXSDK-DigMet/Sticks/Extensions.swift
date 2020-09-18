//
//  Extensions.swift
//  UXSDK-DigMet
//
//  Created by Andreas Gising on 2020-09-11.
//  Copyright © 2020 DJI. All rights reserved.
//

import Foundation
import UIKit
import Photos


// Save UIImage, post "Xcode Version 10.2 (10E125), Swift 5" https://stackoverflow.com/questions/37344822/saving-image-and-then-loading-it-in-swift-ios
extension UIImage {

    func save(at directory: FileManager.SearchPathDirectory,
              pathAndImageName: String,
              createSubdirectoriesIfNeed: Bool = true,
              compressionQuality: CGFloat = 1.0)  -> URL? {
            print("ett")
            do {
                let documentsDirectory = try FileManager.default.url(for: directory, in: .userDomainMask, appropriateFor: nil, create: false)
                print(documentsDirectory.absoluteString)
                print("tva")
                return save(at: documentsDirectory.appendingPathComponent(pathAndImageName),
                    createSubdirectoriesIfNeed: createSubdirectoriesIfNeed,
                    compressionQuality: compressionQuality)
            }
            catch {
                print("-- Error: \(error)")
                return nil
        }
    }

    func save(at url: URL,
              createSubdirectoriesIfNeed: Bool = true,
              compressionQuality: CGFloat = 1.0)  -> URL? {
        do {
            print("one")
            if createSubdirectoriesIfNeed {
                try FileManager.default.createDirectory(at: url.deletingLastPathComponent(),
                                                        withIntermediateDirectories: true,
                                                        attributes: nil)
            }
            print("two")
            guard let data = jpegData(compressionQuality: compressionQuality) else { return nil }
            
            print("three")
            print(url)
            try data.write(to: url)
            return url
        } catch {
            print("-- Error: \(error)")
            return nil
        }
    }
}

// load UIImage from path, post "Xcode Version 10.2 (10E125), Swift 5" https://stackoverflow.com/questions/37344822/saving-image-and-then-loading-it-in-swift-ios
extension UIImage {
    convenience init?(fileURLWithPath url: URL, scale: CGFloat = 1.0) {
        do {
            let data = try Data(contentsOf: url)
            self.init(data: data, scale: scale)
        } catch {
            print("-- Error: \(error)")
            return nil
        }
    }
}


// Extension to convert PHAsset to UIImage, https://stackoverflow.com/questions/30812057/phasset-to-uiimage
extension PHAsset {

    var image : UIImage {
        var thumbnail = UIImage()
        let imageManager = PHCachingImageManager()
        imageManager.requestImage(for: self, targetSize: CGSize(width: 100, height: 100), contentMode: .aspectFit, options: nil, resultHandler: { image, _ in
            thumbnail = image!
        })
        return thumbnail
    }
}


// Extension to easily handle background threads, https://stackoverflow.com/questions/24056205/how-to-use-background-thread-in-swift
typealias Dispatch = DispatchQueue
extension Dispatch {

    static func background(_ task: @escaping () -> ()) {
        Dispatch.global(qos: .background).async {
            task()
        }
    }

    static func superBackground(_ task: @escaping () -> ()) {
        Dispatch.global(qos: .unspecified).async {
            task()
        }
    }

    static func main(_ task: @escaping () -> ()) {
        Dispatch.main.async {
            task()
        }
    }
}

extension Notification.Name {
    static let didPosUpdate = Notification.Name("didPosUpdate")
}
