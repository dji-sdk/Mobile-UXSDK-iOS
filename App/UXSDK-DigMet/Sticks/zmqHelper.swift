//
//  zmqHelper.swift
//  UXSDK-DigMet
//
//  Created by Andreas Gising on 2020-09-11.
//  Copyright © 2020 DJI. All rights reserved.
//

import Foundation
import SwiftyJSON

func cleanUpString(str: String)->String{
     let str2 = str.dropLast()
     let str3 = str2.dropFirst()
     let str4 = str3.replacingOccurrences(of: "\\", with: "")
     return str4
 }

 func uglyfyString(_ str: String)->String{
     let str2 = str.replacingOccurrences(of: "\"", with: "\\\"")
     let str3 = "\"" + str2 + "\""
     return str3
 }

 func getJsonObject(uglyString: String) -> JSON {
     let str = cleanUpString(str: uglyString)
     guard let data = str.data(using: .utf8) else {return JSON()}
     guard let json = try? JSON(data: data) else {return JSON()}
     return json
 }

 func getJsonString(json: JSON) -> String{
     let _str = json.rawString(.utf8, options: .withoutEscapingSlashes)!
     let str = uglyfyString(_str)
     return str
 }

func createJsonAck(_ fcnString: String) -> JSON {
     var json = JSON()
     json["fcn"] = JSON("ack")
     json["arg"] = JSON(fcnString)
     return json
 }

 func createJsonNack(_ str: String) -> JSON {
     var json = JSON()
     json["fcn"] = JSON("nack")
     json["arg"] = JSON(str)
     return json
 }


