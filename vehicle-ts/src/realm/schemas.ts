import Realm, { Dictionary } from 'realm';
import { vehicleConfig } from './config';


 // To use classes instead of types refer here https://github.com/realm/realm-js#typescript-models and here https://www.npmjs.com/package/@realm/babel-plugin 
 //COMMENT: It seems nested objects don't work well with classes and using the types and schemas only seems to work well.
 

/*
  Class disabled and type + schema enabled due to problems with assigning a new battery instance

export class Battery extends Realm.Object<Battery, "capacity" | "current" | "sn" | "status" | "voltage" > {
  capacity?: number;
  current?: number;
  sn?: string;
  status?: string;
  voltage?: number;

  static embedded = true;

  constructor(realm: Realm, capacity: number, current: number, sn: string, status: string, voltage: number) {
    super(realm, {
      capacity,
      current,
      sn,
      status,
      voltage
    });
  }

  static schema = {
    name: 'Battery',
    embedded: true,
    properties: {
      capacity: 'int?',
      current: 'int?',
      sn: 'string?',
      status: 'string?',
      voltage: 'int?',
    },
  };
};
*/

export type Battery = {
  capacity?: number;
  current?: number;
  sn?: string;
  status?: string;
  voltage?: number;
};
export const BatterySchema = {
  name: 'Battery',
  embedded: true,
  properties: {
    capacity: 'int?',
    current: 'int?',
    sn: 'string?',
    status: 'string?',
    voltage: 'int?',
  },
};

export class Command extends Realm.Object<Command> {
  command?: string;
  status?: string;
  ts?: Date;

  static schema = {
    name: 'Command',
    embedded: true,
    properties: {
      command: 'string?',
      status: 'string?',
      ts: 'date?',
    },
  };
};

export class Component extends Realm.Object<Component, "name" | "owner_id"> {
  _id!: Realm.BSON.ObjectId;
  name?: string;
  owner_id!: string;

  constructor(realm: Realm, name: string, owner_id: string) {
    super(realm, {
      _id: new Realm.BSON.ObjectId(),
      name,
      owner_id,
    });
  }

  static schema = {
    name: 'Component',
    properties: {
      _id: 'objectId',
      name: 'string?',
      owner_id: 'string',
    },
    primaryKey: '_id',
  };
};

export class Measurement extends Realm.Object<Measurement, "current" | "ts" | "voltage"> {
  current?: number;
  ts!: Date;
  voltage?: number;

  constructor(realm: Realm, current: number, ts: Date, voltage: number) {
    super(realm, {
      current,
      ts,
      voltage
    });
  }

  static schema = {
    name: 'Measurement',
    embedded: true,
    properties: {
      current: 'int?',
      ts: 'date?',
      voltage: 'int?',
    },
  };
};

export class Sensor extends Realm.Object<Sensor, "sn" | "type" | "vin"> {
  _id!: Realm.BSON.ObjectId;
  measurements!: Realm.List<Measurement>;
  sn?: string;
  type!: string;
  vin!: string;

  constructor(realm: Realm, sn: string, type: string, vin: string) {
    super(realm, {
      _id: new Realm.BSON.ObjectId(),
      measurements: [],
      sn,
      type,
      vin
    });
  }

  static schema = {
    name: 'Sensor',
    asymmetric: true,
    properties: {
      _id: 'objectId',
      measurements: 'Measurement[]',
      sn: 'string?',
      type: 'string',
      vin: 'string',
    },
    primaryKey: '_id',
  };
};

export class Vehicle extends Realm.Object<Vehicle, "owner_id"> {
  _id!: string;
  CurrentLocation?: Vehicle_CurrentLocation;
  IsMoving?: boolean;
  Speed?: number;
  StartTime?: string;
  TraveledDistanceSinceStart?: number;
  VehicleIdentification?: Vehicle_VehicleIdentification;
  battery!: Battery;
  commands!: Realm.List<Command>;
  components!: Realm.List<Component>;
  current?: number;
  isOn!: boolean;
  mixedTypes?: unknown;
  name!: string;
  owner_id!: string;

  constructor(realm: Realm, owner_id: string) {
    super(realm, {
      _id: vehicleConfig._id,
      name: vehicleConfig.name,
      battery: vehicleConfig.battery,
      isOn: false,
      owner_id
    });
  }

  static schema = {
    name: 'Vehicle',
    properties: {
      _id: 'string',
      CurrentLocation: 'Vehicle_CurrentLocation',
      IsMoving: 'bool?',
      Speed: 'double?',
      StartTime: 'string?',
      TraveledDistanceSinceStart: 'double?',
      VehicleIdentification: 'Vehicle_VehicleIdentification',
      battery: 'Battery',
      commands: 'Command[]',
      components: 'Component[]',
      current: 'int?',
      isOn: 'bool',
      mixedTypes: 'mixed',
      name: 'string',
      owner_id: 'string',
    },
    primaryKey: '_id',
  };
};

export class Vehicle_CurrentLocation extends Realm.Object<Vehicle_CurrentLocation> {
  Altitude?: number;
  GNSSReceiver_FixType?: string;
  GNSSReceiver_MountingPosition_X?: number;
  GNSSReceiver_MountingPosition_Y?: number;
  GNSSReceiver_MountingPosition_Z?: number;
  Heading?: number;
  HorizontalAccuracy?: number;
  Latitude?: number;
  Longitude?: number;
  Timestamp?: string;
  VerticalAccuracy?: number;

  static schema = {
    name: 'Vehicle_CurrentLocation',
    embedded: true,
    properties: {
      Altitude: 'double?',
      GNSSReceiver_FixType: 'string?',
      GNSSReceiver_MountingPosition_X: 'int?',
      GNSSReceiver_MountingPosition_Y: 'int?',
      GNSSReceiver_MountingPosition_Z: 'int?',
      Heading: 'double?',
      HorizontalAccuracy: 'double?',
      Latitude: 'double?',
      Longitude: 'double?',
      Timestamp: 'string?',
      VerticalAccuracy: 'double?',
    },
  };
};

export class Vehicle_VehicleIdentification extends Realm.Object<Battery> {
  AcrissCode?: string;
  BodyType?: string;
  Brand?: string;
  DateVehicleFirstRegistered?: string;
  KnownVehicleDamages?: string;
  MeetsEmissionStandard?: string;
  Model?: string;
  OptionalExtras!: Realm.List<string>;
  Owner?: Realm.BSON.ObjectId;
  ProductionDate?: string;
  PurchaseDate?: string;
  VIN?: string;
  VehicleConfiguration?: string;
  VehicleInteriorColor?: string;
  VehicleInteriorType?: string;
  VehicleModelDate?: string;
  VehicleSeatingCapacity?: number;
  VehicleSpecialUsage?: string;
  WMI?: string;
  Year?: number;

  static schema = {
    name: 'Vehicle_VehicleIdentification',
    embedded: true,
    properties: {
      AcrissCode: 'string?',
      BodyType: 'string?',
      Brand: 'string?',
      DateVehicleFirstRegistered: 'string?',
      KnownVehicleDamages: 'string?',
      MeetsEmissionStandard: 'string?',
      Model: 'string?',
      OptionalExtras: 'string[]',
      Owner: 'objectId?',
      ProductionDate: 'string?',
      PurchaseDate: 'string?',
      VIN: 'string?',
      VehicleConfiguration: 'string?',
      VehicleInteriorColor: 'string?',
      VehicleInteriorType: 'string?',
      VehicleModelDate: 'string?',
      VehicleSeatingCapacity: 'int?',
      VehicleSpecialUsage: 'string?',
      WMI: 'string?',
      Year: 'int?',
    },
  };
};
