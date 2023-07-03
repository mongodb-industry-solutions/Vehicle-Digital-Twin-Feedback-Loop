# Project Roadmap/TODOs

## Overall Ideas: TODO

- [ ] Add over the air update functionality (Sync with partner SAs / build simple command into mobile app -> updated to v3 -> trigger on the vehicle to download version from internet e.g. github)
- [ ] Add tiered sync for the onboard part and connect the cpp and typescript parts to it
- [ ] Continuously monitor Realm/Atlas roadmap and add/emphasize new features

## Vehicle-TS: TODO

- [ ] Udate data model to better align with VSS through deeper nesting: [HELP-46424](https://jira.mongodb.org/browse/HELP-46424)
- [ ] Extend the application with the upcoming geospatial features: [RPM-338](https://jira.mongodb.org/browse/RPM-338)
- [ ] Look into using asymmetric sync with stream processing [Architecture](https://docs.google.com/presentation/d/1L9Cxd7dfBd7OP4TzxlKzcMUk9Xy3CGnnspsldgQctNU/edit#slide=id.g23cefc6a482_0_7)

## Mobile-Swift: TODO

- [ ] Once the Realm geolocation features are implemented, add automatic location updates to the already added map view and integrate it into the gui.


## Observer-CPP: TODO

- [ ] Udate data model to better align with VSS through deeper nesting: [HELP-46424](https://jira.mongodb.org/browse/HELP-46424)
- [ ] Currently object listeners in the C++ sdk don't react to changes in nested objects. The swift sdk already supports key path listeners: [Key Path Listener](https://www.mongodb.com/docs/realm/sdk/swift/react-to-changes/#register-a-key-path-change-listener)


## GPS-CPP: TODO

- [ ] Udate data model to better align with VSS through deeper nesting: [HELP-46424](https://jira.mongodb.org/browse/HELP-46424)
- [ ] Extend the application with the upcoming geospatial features: [RPM-338](https://jira.mongodb.org/browse/RPM-338)
