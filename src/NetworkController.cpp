#include "NetworkController.hh"


NetworkController::NetworkController()
{
	//
}

void NetworkController::setNetwork(String id, String pw, bool restart)
{
	delay(5000);
	Serial.println("++SET NETWORK++");

	_preferences.begin("network", false);
	_preferences.putString("ssid", id);
	_preferences.putString("password", pw);
	_preferences.end();

	if (restart) {
		Serial.println("++RESTART++");
		Serial.println(id);
		Serial.println(pw);
		delay(10000);
		ESP.restart();
	}
}

void NetworkController::laodNetwork()
{
	Serial.println("++LOAD NETWORK++");
	_preferences.begin("network", false);
	_ssid = _preferences.getString("ssid", "Dudopark");
	_password = _preferences.getString("password", "so8riQ59eze7HEsW?yep");
	_preferences.end();

	WiFi.mode(WIFI_MODE_APSTA);
	WiFi.softAP(ap_ssid, ap_password);
	WiFi.begin(getSSID().c_str(), getPassword().c_str());
}

void NetworkController::serve(AsyncWebServer &server)
{
	server.on("/network", HTTP_GET, [&](AsyncWebServerRequest *request)
			  { request->send_P(200, "text/html", index_html, [&](const String &var)
					{
						if (var == "IPPLACEHOLDER")
						{
							String ipText = "SSID:" + _ssid + "<br>Locale IP: ";
							ipText += WiFi.localIP().toString().c_str();
							return ipText;
						}

						return String(); 
					}); 
				});

	server.on("/update", HTTP_GET, [&](AsyncWebServerRequest *request)
			  {
				String inputMessage;
				String inputParam;

				if (request->hasParam(PARAM_INPUT_2))
				{
					Serial.println(request->getParam(PARAM_INPUT_2)->value());
					Serial.println(request->getParam(PARAM_INPUT_3)->value());

					request->send(200, "text/html", "Wird neugestartet");

					setNetwork(request->getParam(PARAM_INPUT_2)->value(), request->getParam(PARAM_INPUT_3)->value(), true);
				}

				request->send(200, "text/html", "OK"); 
			});
}

void NetworkController::connectionState()
{
	if (WiFi.status() != WL_CONNECTED)
	{
		Serial.println("Connecting to WiFi..");
		while (WiFi.status() != WL_CONNECTED)
		{
			delay(3000);
			Serial.print(".");

			if (WiFi.status() == WL_CONNECTED)
			{
				Serial.print("Connected: IP " + WiFi.localIP());
			}
		}
	}
}
