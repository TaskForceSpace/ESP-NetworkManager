// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NetworkController.hh>

// AsyncWebServer object on port 80
AsyncWebServer server(80);
NetworkController nc = NetworkController();

void setup()
{
  Serial.begin(115200);

  nc.laodNetwork();
  Serial.println(nc.getSSID());
  Serial.println(nc.getPassword());

  // Print ESP AP IP Address
  Serial.println(WiFi.softAPIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", "ESP32"); });

  nc.serve(server);

  // Start server
  server.begin();
}

void loop()
{
  // Just show in searial output of connection state
  nc.connectionState();
}
