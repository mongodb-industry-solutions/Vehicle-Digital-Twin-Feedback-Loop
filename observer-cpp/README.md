# Observer-CPP

A simple C++ application using the Realm C++ SDK to connect to the Atlas backend. If it finds a vehicle document with the configured VIN, it will start listening for changes and print out to console. The functionality is currently very simplistic and rather considered a foundation to add more specific functionality in the future.

## TODO

- [ ] Udate data model to better align with VSS through deeper nesting: [HELP-46424](https://jira.mongodb.org/browse/HELP-46424)
- [ ] Currently object listeners in the C++ sdk don't react to changes in nested objects. The swift sdk already supports key path listeners: [Key Path Listener](https://www.mongodb.com/docs/realm/sdk/swift/react-to-changes/#register-a-key-path-change-listener)
