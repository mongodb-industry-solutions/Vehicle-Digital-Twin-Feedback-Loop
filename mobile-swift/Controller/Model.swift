//
//  DataModel.swift
//  Easy
//
//  Created by Felix Reichenbach on 03.06.21.
//

import Foundation
import RealmSwift

class Vehicle: Object, ObjectKeyIdentifiable {
    @Persisted(primaryKey: true) var _id: String = ""
    @Persisted var CurrentLocation: Vehicle_CurrentLocation?
    @Persisted var IsMoving: Bool?
    @Persisted var Speed: Double?
    @Persisted var StartTime: String?
    @Persisted var TraveledDistanceSinceStart: Double?
    @Persisted var VehicleIdentification: Vehicle_VehicleIdentification?
    @Persisted var battery: Battery?
    @Persisted var commands: List<Command>
    @Persisted var components: List<Component>
    @Persisted var current: Int?
    @Persisted var isOn: Bool = false
    @Persisted var mixedTypes: AnyRealmValue
    @Persisted var name: String = ""
    @Persisted var owner_id: String = ""
}

class Vehicle_CurrentLocation: EmbeddedObject {
    @Persisted var Altitude: Double?
    @Persisted var GNSSReceiver_FixType: String?
    @Persisted var GNSSReceiver_MountingPosition_X: Int?
    @Persisted var GNSSReceiver_MountingPosition_Y: Int?
    @Persisted var GNSSReceiver_MountingPosition_Z: Int?
    @Persisted var Heading: Double?
    @Persisted var HorizontalAccuracy: Double?
    @Persisted var Latitude: Double?
    @Persisted var Longitude: Double?
    @Persisted var Timestamp: String?
    @Persisted var VerticalAccuracy: Double?
}

class Vehicle_VehicleIdentification: EmbeddedObject {
    @Persisted var AcrissCode: String?
    @Persisted var BodyType: String?
    @Persisted var Brand: String?
    @Persisted var DateVehicleFirstRegistered: String?
    @Persisted var KnownVehicleDamages: String?
    @Persisted var MeetsEmissionStandard: String?
    @Persisted var Model: String?
    @Persisted var OptionalExtras: List<String>
    @Persisted var Owner: ObjectId?
    @Persisted var ProductionDate: String?
    @Persisted var PurchaseDate: String?
    @Persisted var VIN: String?
    @Persisted var VehicleConfiguration: String?
    @Persisted var VehicleInteriorColor: String?
    @Persisted var VehicleInteriorType: String?
    @Persisted var VehicleModelDate: String?
    @Persisted var VehicleSeatingCapacity: Int?
    @Persisted var VehicleSpecialUsage: String?
    @Persisted var WMI: String?
    @Persisted var Year: Int?
}

class Battery: EmbeddedObject {
    @Persisted var capacity: Int?
    @Persisted var current: Int?
    @Persisted var sn: String?
    @Persisted var voltage: Int?
    @Persisted var status: String?
}

class Component: Object {
    @Persisted(primaryKey: true) var _id: ObjectId
    @Persisted var name: String?
    @Persisted var owner_id: String = ""
}

class Command: EmbeddedObject, Identifiable {
    @Persisted var command: String?
    @Persisted var status: CmdStatus?
    @Persisted var ts: Date? = Date()
}

enum CmdStatus: String, PersistableEnum {
    case submitted
    case inProgress
    case completed
    case failed
}
