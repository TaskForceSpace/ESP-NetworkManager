# ESP Network and Server Manager
After init, an AccesPoint to the ESP is opened and connects in parallel to a stored wifi.

Under IP/network you can configure the wlan data

## Imports in main
```C
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NetworkController.hh>
```

## Before Setup
```C
AsyncWebServer server(80);
NetworkController nc = NetworkController();
```
## Setup
```C
void setup()
{
nc.laodNetwork();
nc.serve(server);

...
other server.on(...) methods
...

server.begin();
}
```

## Loop Optional
```C
void loop()
{
nc.connectionState();
}
```