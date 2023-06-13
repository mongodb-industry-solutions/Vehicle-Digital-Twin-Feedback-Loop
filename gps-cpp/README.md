# GPS-CPP

A simple C++ application using the Realm C++ SDK to connect to the Atlas backend. If it finds a vehicle document with the configured VIN, it will update it will continuously update it with the GPC coordinates out of the included XML file. You can update the frequency of updates and other options in the main.cpp file.

## TODO

- [ ] Udate data model to better align with VSS through deeper nesting: [HELP-46424](https://jira.mongodb.org/browse/HELP-46424)
- [ ] Extend the application with the upcoming geospatial features: [RPM-338](https://jira.mongodb.org/browse/RPM-338)
