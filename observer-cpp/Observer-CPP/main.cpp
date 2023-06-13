//
//  main.cpp
//  Observer-CPP
//
//
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <cpprealm/sdk.hpp>


/**
 Observer-CPP - Application Configuration
 */
const std::string app_id = "YOUR-MONGODB-APPSERVICES-APPID";   // Must match your Atlas App Services application id!
const std::string VIN = "5UXFE83578L342684";            // Vehicle identifier number must match the vehicle id of other Realm apps
const std::string userID = "demo";                      // Atlas App Services user id
const std::string password = "demopw";                  // Atlas App Services user password

/**
 Model Section
 
 TODO: 3rd level nesting doesn't compile yet in the C++ SDK -> https://jira.mongodb.org/browse/HELP-46424 ETA: Beta Release
 TODO: Only changes on vehicle level fields trigger notifications as noted further down. Key path filters available in the Swift SDK not yet available in the CPP SDK.
 */

/*
 struct Vehicle_CurrentLocation_GNSSReceiver_MountingPosition : realm::embedded_object<Vehicle_CurrentLocation_GNSSReceiver_MountingPosition> {
 realm::persisted<std::optional<int64_t>> X;
 realm::persisted<std::optional<int64_t>> Y;
 realm::persisted<std::optional<int64_t>> Z;
 
 static constexpr auto schema = realm::schema("Vehicle_CurrentLocation_GNSSReceiver_MountingPosition",
 realm::property<&Vehicle_CurrentLocation_GNSSReceiver_MountingPosition::X>("X"),
 realm::property<&Vehicle_CurrentLocation_GNSSReceiver_MountingPosition::Y>("Y"),
 realm::property<&Vehicle_CurrentLocation_GNSSReceiver_MountingPosition::Z>("Z")
 );
 };
 
 struct Vehicle_CurrentLocation_GNSSReceiver : realm::embedded_object<Vehicle_CurrentLocation_GNSSReceiver> {
 realm::persisted<std::optional<std::string>> FixType;
 realm::persisted<std::optional<Vehicle_CurrentLocation_GNSSReceiver_MountingPosition>> MountingPosition;
 
 static constexpr auto schema = realm::schema("Vehicle_CurrentLocation_GNSSReceiver",
 realm::property<&Vehicle_CurrentLocation_GNSSReceiver::FixType>("FixType"),
 realm::property<&Vehicle_CurrentLocation_GNSSReceiver::MountingPosition>("MountingPosition")
 );
 };
 */

struct Battery : realm::embedded_object<Battery> {
    realm::persisted<std::optional<int64_t>> capacity;
    realm::persisted<std::optional<int64_t>> current;
    realm::persisted<std::optional<std::string>> sn;
    realm::persisted<std::optional<std::string>> status;
    realm::persisted<std::optional<int64_t>> voltage;
    
    static constexpr auto schema = realm::schema("Battery",
        realm::property<&Battery::capacity>("capacity"),
        realm::property<&Battery::current>("current"),
        realm::property<&Battery::sn>("sn"),
        realm::property<&Battery::status>("status"),
        realm::property<&Battery::voltage>("voltage")
    );
};

struct Command : realm::embedded_object<Command> {
    realm::persisted<std::optional<std::string>> command;
    realm::persisted<std::optional<std::string>> status;
    realm::persisted<std::optional<std::chrono::time_point<std::chrono::system_clock>>> ts;
    static constexpr auto schema = realm::schema("Command",
        realm::property<&Command::command>("command"),
        realm::property<&Command::status>("status"),
        realm::property<&Command::ts>("ts")
    );
};

struct Component : realm::object<Component> {
    realm::persisted<realm::object_id> _id;
    realm::persisted<std::optional<std::string>> name;
    realm::persisted<std::string> owner_id;
    static constexpr auto schema = realm::schema("Component",
        realm::property<&Component::_id, true>("_id"),
        realm::property<&Component::name>("name"),
        realm::property<&Component::owner_id>("owner_id")
    );
};

struct Vehicle_CurrentLocation : realm::embedded_object<Vehicle_CurrentLocation> {
    realm::persisted<std::optional<double>> Altitude;
    //realm::persisted<std::optional<Vehicle_CurrentLocation_GNSSReceiver>> GNSSReceiver;
    //flat
    realm::persisted<std::optional<std::string>> GNSSReceiver_FixType;
    realm::persisted<std::optional<std::int64_t>> GNSSReceiver_MountingPosition_X;
    realm::persisted<std::optional<std::int64_t>> GNSSReceiver_MountingPosition_Y;
    realm::persisted<std::optional<std::int64_t>> GNSSReceiver_MountingPosition_Z;
    //end
    realm::persisted<std::optional<double>> Heading;
    realm::persisted<std::optional<double>> HorizontalAccuracy;
    realm::persisted<std::optional<double>> Latitude;
    realm::persisted<std::optional<double>> Longitude;
    realm::persisted<std::optional<std::string>> Timestamp;
    realm::persisted<std::optional<double>> VerticalAccuracy;
    
    static constexpr auto schema = realm::schema("Vehicle_CurrentLocation",
        realm::property<&Vehicle_CurrentLocation::Altitude>("Altitude"),
        //realm::property<&Vehicle_CurrentLocation::GNSSReceiver>("GNSSReceiver"),
        realm::property<&Vehicle_CurrentLocation::GNSSReceiver_FixType>("GNSSReceiver_FixType"),
        realm::property<&Vehicle_CurrentLocation::GNSSReceiver_MountingPosition_X>("GNSSReceiver_MountingPosition_X"),
        realm::property<&Vehicle_CurrentLocation::GNSSReceiver_MountingPosition_Y>("GNSSReceiver_MountingPosition_Y"),
        realm::property<&Vehicle_CurrentLocation::GNSSReceiver_MountingPosition_Z>("GNSSReceiver_MountingPosition_Z"),
        realm::property<&Vehicle_CurrentLocation::Heading>("Heading"),
        realm::property<&Vehicle_CurrentLocation::HorizontalAccuracy>("HorizontalAccuracy"),
        realm::property<&Vehicle_CurrentLocation::Latitude>("Latitude"),
        realm::property<&Vehicle_CurrentLocation::Longitude>("Longitude"),
        realm::property<&Vehicle_CurrentLocation::Timestamp>("Timestamp"),
        realm::property<&Vehicle_CurrentLocation::VerticalAccuracy>("VerticalAccuracy")
    );
};

struct Vehicle_VehicleIdentification : realm::embedded_object<Vehicle_VehicleIdentification> {
    realm::persisted<std::optional<std::string>> AcrissCode;
    realm::persisted<std::optional<std::string>> BodyType;
    realm::persisted<std::optional<std::string>> Brand;
    realm::persisted<std::optional<std::string>> DateVehicleFirstRegistered;
    realm::persisted<std::optional<std::string>> KnownVehicleDamages;
    realm::persisted<std::optional<std::string>> MeetsEmissionStandard;
    realm::persisted<std::optional<std::string>> Model;
    realm::persisted<std::vector<std::string>> OptionalExtras;
    realm::persisted<std::optional<realm::object_id>> Owner;
    realm::persisted<std::optional<std::string>> ProductionDate;
    realm::persisted<std::optional<std::string>> PurchaseDate;
    realm::persisted<std::optional<std::string>> VIN;
    realm::persisted<std::optional<std::string>> VehicleConfiguration;
    realm::persisted<std::optional<std::string>> VehicleInteriorColor;
    realm::persisted<std::optional<std::string>> VehicleInteriorType;
    realm::persisted<std::optional<std::string>> VehicleModelDate;
    realm::persisted<std::optional<int64_t>> VehicleSeatingCapacity;
    realm::persisted<std::optional<std::string>> VehicleSpecialUsage;
    realm::persisted<std::optional<std::string>> WMI;
    realm::persisted<std::optional<int64_t>> Year;
    
    static constexpr auto schema = realm::schema("Vehicle_VehicleIdentification",
        realm::property<&Vehicle_VehicleIdentification::AcrissCode>("AcrissCode"),
        realm::property<&Vehicle_VehicleIdentification::BodyType>("BodyType"),
        realm::property<&Vehicle_VehicleIdentification::Brand>("Brand"),
        realm::property<&Vehicle_VehicleIdentification::DateVehicleFirstRegistered>("DateVehicleFirstRegistered"),
        realm::property<&Vehicle_VehicleIdentification::KnownVehicleDamages>("KnownVehicleDamages"),
        realm::property<&Vehicle_VehicleIdentification::MeetsEmissionStandard>("MeetsEmissionStandard"),
        realm::property<&Vehicle_VehicleIdentification::Model>("Model"),
        realm::property<&Vehicle_VehicleIdentification::OptionalExtras>("OptionalExtras"),
        realm::property<&Vehicle_VehicleIdentification::Owner>("Owner"),
        realm::property<&Vehicle_VehicleIdentification::ProductionDate>("ProductionDate"),
        realm::property<&Vehicle_VehicleIdentification::PurchaseDate>("PurchaseDate"),
        realm::property<&Vehicle_VehicleIdentification::VIN>("VIN"),
        realm::property<&Vehicle_VehicleIdentification::VehicleConfiguration>("VehicleConfiguration"),
        realm::property<&Vehicle_VehicleIdentification::VehicleInteriorColor>("VehicleInteriorColor"),
        realm::property<&Vehicle_VehicleIdentification::VehicleInteriorType>("VehicleInteriorType"),
        realm::property<&Vehicle_VehicleIdentification::VehicleModelDate>("VehicleModelDate"),
        realm::property<&Vehicle_VehicleIdentification::VehicleSeatingCapacity>("VehicleSeatingCapacity"),
        realm::property<&Vehicle_VehicleIdentification::VehicleSpecialUsage>("VehicleSpecialUsage"),
        realm::property<&Vehicle_VehicleIdentification::WMI>("WMI"),
        realm::property<&Vehicle_VehicleIdentification::Year>("Year")
    );
};

struct Vehicle : realm::object<Vehicle> {
    realm::persisted<std::string> _id;
    realm::persisted<std::optional<Vehicle_CurrentLocation>> CurrentLocation;
    realm::persisted<std::optional<bool>> IsMoving;
    realm::persisted<std::optional<double>> Speed;
    realm::persisted<std::optional<std::string>> StartTime;
    realm::persisted<std::optional<double>> TraveledDistanceSinceStart;
    realm::persisted<std::optional<Vehicle_VehicleIdentification>> VehicleIdentification;
    realm::persisted<std::optional<Battery>> battery;
    realm::persisted<std::vector<Command>> commands;
    realm::persisted<std::vector<Component>> components;
    realm::persisted<std::optional<int64_t>> current;
    realm::persisted<bool> isOn;
    realm::persisted<realm::mixed> mixedTypes;
    realm::persisted<std::string> name;
    realm::persisted<std::string> owner_id;
    
    static constexpr auto schema = realm::schema("Vehicle",
        realm::property<&Vehicle::_id, true>("_id"),
        realm::property<&Vehicle::CurrentLocation>("CurrentLocation"),
        realm::property<&Vehicle::IsMoving>("IsMoving"),
        realm::property<&Vehicle::Speed>("Speed"),
        realm::property<&Vehicle::StartTime>("StartTime"),
        realm::property<&Vehicle::TraveledDistanceSinceStart>("TraveledDistanceSinceStart"),
        realm::property<&Vehicle::VehicleIdentification>("VehicleIdentification"),
        realm::property<&Vehicle::battery>("battery"),
        realm::property<&Vehicle::commands>("commands"),
        realm::property<&Vehicle::components>("components"),
        realm::property<&Vehicle::current>("current"),
        realm::property<&Vehicle::isOn>("isOn"),
        realm::property<&Vehicle::mixedTypes>("mixedTypes"),
        realm::property<&Vehicle::name>("name"),
        realm::property<&Vehicle::owner_id>("owner_id")
    );
};

/**
 Main Program
 */
int main(int argc, const char * argv[]) {
    
    auto app = realm::App(app_id);
    std::cout << "step: app" << std::endl;
    auto user = app.login(realm::App::credentials::anonymous()).get_future().get();
    std::cout << "step: login" << std::endl;
    auto sync_config = user.flexible_sync_configuration();
    std::cout << "step: config" << std::endl;
    
    auto synced_realm_ref = realm::async_open<Vehicle, Vehicle_CurrentLocation,Vehicle_VehicleIdentification, Battery, Command, Component>(sync_config).get_future().get();
    std::cout << "step: realm" << std::endl;
    auto realm = synced_realm_ref.resolve();
    std::cout << "step: resolve" << std::endl;
    auto subscriptions = realm.subscriptions();
    std::cout << "step: sub" << std::endl;

    realm.subscriptions().update([](realm::mutable_sync_subscription_set &subs) {
        if(!subs.find("Vehicle")) {
            subs.add<Vehicle>("Vehicle", [](auto &obj) {
                return obj._id == VIN;
            });
        }
    }).get_future().get();
    
    realm.get_sync_session()->wait_for_download_completion().get_future().get();
    realm.refresh();
    
    auto allVehicles = realm.objects<Vehicle>();
    if (allVehicles.size() == 0) {
        std::cout << "No vehicle found, stopping program!" << std::endl;
        exit(0);
    }
    Vehicle vehicle = allVehicles[0];
    std::cout << "Vehicle found: " << vehicle._id << std::endl;
    
    //  Set up the listener & observe object notifications.
    auto token = vehicle.observe([&](auto&& change) {
        try {
            if (change.error) {
                rethrow_exception(change.error);
            }
            if (change.is_deleted) {
                std::cout << "The object was deleted." << std::endl;
                exit(0);
            } else {
                /*
                 TODO: Nested objects don't trigger notifications yet -> Key path listeners have been implemented in some other SDKs already https://www.mongodb.com/docs/realm/sdk/swift/react-to-changes/#register-a-key-path-change-listener
                for (auto& propertyChange : change.property_changes) {
                    std::cout << "The object's " << propertyChange.name << " property has changed." << std::endl;
                    auto newPropertyValue = std::get<std::string>(*propertyChange.new_value);
                    std::cout << "The new value is " << newPropertyValue << std::endl;
                }*/
            }
        } catch (std::exception const& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "change" << std::endl;
    });

    int counter = 60 * 10; // 10minutes
    
    while(counter > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        realm.refresh();
        counter--;
    }
    
    auto removeSubscriptionSuccess = subscriptions.update([](realm::mutable_sync_subscription_set &subs) {
        subs.remove("Vehicle");
    }).get_future().get();
    
    std::cout << "step: unsubSuccess: " << removeSubscriptionSuccess << std::endl;
    
    token.unregister();
     
    
    return 0;
}
