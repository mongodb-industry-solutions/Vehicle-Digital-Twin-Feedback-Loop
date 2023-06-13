#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include "rapidxml-1.13/rapidxml.hpp"
#include <cpprealm/sdk.hpp>

using namespace std;
using namespace rapidxml;

/**
 gps-cpp - Application configuration
 */
const std::string app_id = "<--YOUR APP SERVICES ID-->";   // Must match your Atlas App Services application id!
const std::string VIN = "5UXFE83578L342684";            // Vehicle identifier number must match the vehicle id of other Realm apps
const std::string userID = "demo";                      // Atlas App Services user id
const std::string password = "demopw";                  // Atlas App Services user password
const std::int64_t sleep_ms = 1000;                     // Configure frequency of coordinates update


/**
 Model Section
 
 TODO: 3rd level nesting doesn't compile yet in the C++ SDK -> https://jira.mongodb.org/browse/HELP-46424 ETA: Beta Release
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
 Iterates over GPS coordinates in the XML file
 */
int getChildCount(xml_node<> *n)
{
    int c = 0;
    for (xml_node<> *child = n->first_node(); child != NULL; child = child->next_sibling())
    {
        c++;
    }
    return c;
}

/**
 Main Program
 */
int main(int argc, const char * argv[]) {
    
    auto app = realm::App(app_id);
    cout << "step: app" << endl;
    auto user = app.login(realm::App::credentials::username_password(userID, password))
        .get_future().get();
    cout << "step: login" << endl;
    auto sync_config = user.flexible_sync_configuration();
    cout << "step: config" << endl;
    
    auto synced_realm_ref = realm::async_open<Vehicle, Vehicle_CurrentLocation, Vehicle_VehicleIdentification, Battery, Command, Component>(sync_config).get_future().get();
    cout << "step: realm" << endl;
    auto realm = synced_realm_ref.resolve();
    cout << "step: resolve" << endl;
    auto subscriptions = realm.subscriptions();
    cout << "step: sub" << endl;
    
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
    
    
    // update start time
    auto timeNow = time(nullptr);
    auto timeNowLocal = *localtime(&timeNow);
    
    cout << "now: " << put_time(&timeNowLocal, "%Y-%m-%d %H:%M:%S") << endl;
    
    cout << "now in vehicle: " << **vehicle.StartTime << endl;
    
    xml_document<> doc;
    xml_node<> * root_node;
    
    ifstream theFile ("Location.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);
    root_node = doc.first_node("gpx");
    
    for (xml_node<> * trackNode = root_node->first_node("trkseg"); trackNode; trackNode = trackNode->next_sibling())
    {
        auto numberOfTrackpoints = getChildCount(trackNode);
        cout << "#points: " << numberOfTrackpoints << endl;
        int currentTrackpoint = 0;
        
        for(xml_node<> * trackPointNode = trackNode->first_node("trkpt"); trackPointNode; trackPointNode = trackPointNode->next_sibling())
        {
            std::time_t now = std::time(nullptr);
            currentTrackpoint++;
            
            printf("Location [%i / %i] at %s is %s , %s ",
                   currentTrackpoint, numberOfTrackpoints, std::ctime(&now),
                   trackPointNode->first_attribute("lat")->value(),
                   trackPointNode->first_attribute("lon")->value());
            cout << endl;
            
            auto timeNow = time(nullptr);
            auto timeNowLocal = *localtime(&timeNow);
            ostringstream stringStream;
            stringStream << put_time(&timeNowLocal, "%Y-%m-%d %H:%M:%S");
            
            realm.write([&realm, &vehicle, &trackPointNode, &stringStream] {
                double lat = stod(trackPointNode->first_attribute("lat")->value());
                double lon = stod(trackPointNode->first_attribute("lon")->value());
                Vehicle_CurrentLocation loc = Vehicle_CurrentLocation();
                vehicle.IsMoving = true;
                vehicle.CurrentLocation = loc;
                vehicle.CurrentLocation->Latitude = lat;
                vehicle.CurrentLocation->Longitude = lon;
                vehicle.CurrentLocation->Timestamp = stringStream.str();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
        }
    }
    
    // stop vehicle
    realm.write([&realm, &vehicle] {
        vehicle.IsMoving = false;
    });
    
    auto removeSubscriptionSuccess = subscriptions.update([](realm::mutable_sync_subscription_set &subs) {
        subs.remove("Vehicle");
    }).get_future().get();
    
    cout << "step: unsubSuccess: " << removeSubscriptionSuccess << endl;
    
    return 0;
}


