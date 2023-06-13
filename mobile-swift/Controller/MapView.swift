//
//  MapView.swift
//  Controller
//
//  Created by Felix Reichenbach on 08.06.23.
//

import SwiftUI
import MapKit
import RealmSwift


// UNDER CONSTRUCTION - NOT used in the app for now

struct VehicleLoc: Identifiable {
    let id = UUID()
    let coordinate: CLLocationCoordinate2D
}

struct MapView: View {
    
    //@ObservedRealmObject var vehicle: Vehicle
    
    @State private var userTrackingMode: MapUserTrackingMode = .follow
    @State private var region = MKCoordinateRegion(
        center: CLLocationCoordinate2D(
            latitude: 49.792960,
            longitude: 9.936500
        ),
        span: MKCoordinateSpan(
            latitudeDelta: 1,
            longitudeDelta: 1
        )
    )
    
    var body: some View {
        Map(coordinateRegion: $region, annotationItems: [
            VehicleLoc(coordinate: .init(latitude: /*vehicle.CurrentLocation?.Latitude ??*/ 49.792960, longitude: /*vehicle.CurrentLocation?.Longitude ?? */ 9.936500))
        ]) { vehicleLoc in
            MapAnnotation(
                coordinate: vehicleLoc.coordinate,
                anchorPoint: CGPoint(x: 0.5, y: 0.5)
            ) {
                Circle()
                    .stroke(Color.red, lineWidth: 5)
                    .frame(width: 44, height: 44)
            }
        }
    }
}

struct MapView_Previews: PreviewProvider {
    static var previews: some View {
        MapView()
    }
}

