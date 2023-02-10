#ifndef NETWORKCONTROLLER_HH
#define NETWORKCONTROLLER_HH

#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

class NetworkController {
	private:
		Preferences _preferences;
		String _ssid;
		String _password;

	public:
		NetworkController();

		const char* PARAM_INPUT_2 = "ssid";

		const char* PARAM_INPUT_3 = "pw";

		const char* ap_ssid = "IDS-DeskTracker";
		const char* ap_password = "123456789";

		String getSSID() const { return _ssid; }

		String getPassword() const { return _password; }

		String processor(const String &var);

		void setNetwork(String id, String pw, bool restart);

		void laodNetwork();

		void connectionState(void);

		void serve(AsyncWebServer &server);

		String html = R"rawliteral(
			<!DOCTYPE HTML><html>
			<head>
			<title>Network Settings</title>
			<meta name="viewport" content="width=device-width, initial-scale=1">
			<style>
				html {font-family: Arial; display: inline-block; text-align: center;}
				h2 {font-size: 3.0rem;}
				p {font-size: 3.0rem;}
				body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
				input#ssid, input#pwd { padding: 10px 5px;margin-bottom: 11px;}
			</style>
			</head>
			<body>
			<h2>Network Settings</h2>
			%IPPLACEHOLDER%
			<h4>Mit Wlan verbinden</h4>
			<div style="display: flex; flex-flow: column; align-items: center;">
				<input id="ssid" type="text" placeholder="SSID"></input>  
				<input id="pwd" type="text" placeholder="passwort"></input>  
				<input type="button" value="Speichern" onclick="updateNetwork(this)" style="height:52px; width: 128px; cursor:pointer;" ></input>
			</div>
			<script>

			function updateNetwork(element){
				var ssid = document.querySelector('#ssid');
				var pwd = document.querySelector('#pwd');
				var xhr = new XMLHttpRequest();
				xhr.open("GET", "/update?ssid=" + ssid.value + "&pw=" + pwd.value, true);
				xhr.send();
			}
			</script>
			</body>
			</html>
			)rawliteral";

		const char *index_html PROGMEM = html.c_str();
};

#endif