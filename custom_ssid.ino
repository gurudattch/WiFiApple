#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 64
#define SSID_ADDR   0

char apSSID[33] = "AccessPoint";

DNSServer dnsServer;
ESP8266WebServer server(80);

/* ================== HTML ================== */

const char* portalPage = R"(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Captive Portal</title>
<style>
html,body,iframe{margin:0;padding:0;height:100%;width:100%;border:none;}
</style>
</head>
<body>
<iframe src="http://192.168.4.100:8000"></iframe>
</body>
</html>
)";

const char* ssidPage = R"(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Change SSID</title>
</head>
<body>
<h2>Change Access Point SSID</h2>
<form method="POST" action="/ssid">
<input type="text" name="ssid" maxlength="32" required>
<br><br>
<button type="submit">Update SSID</button>
</form>
</body>
</html>
)";

/* ================== EEPROM ================== */

void loadSSID() {
  EEPROM.get(SSID_ADDR, apSSID);
  if (apSSID[0] == 0xFF || strlen(apSSID) == 0) {
    strcpy(apSSID, "AccessPoint");
  }
}

void saveSSID(const String& newSSID) {
  memset(apSSID, 0, sizeof(apSSID));
  newSSID.toCharArray(apSSID, sizeof(apSSID));
  EEPROM.put(SSID_ADDR, apSSID);
  EEPROM.commit();
}

/* ================== HANDLERS ================== */

void handleRoot() {
  server.send(200, "text/html", portalPage);
}

void handleSSIDPage() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("ssid")) {
      String newSSID = server.arg("ssid");
      saveSSID(newSSID);

      server.send(200, "text/html",
        "<h3>SSID Updated. Rebooting...</h3>");
      delay(1500);

      WiFi.softAPdisconnect(true);
      WiFi.softAP(apSSID);
    }
  } else {
    server.send(200, "text/html", ssidPage);
  }
}

void handleNotFound() {
  if (server.hasHeader("Host")) {
    server.sendHeader(
      "Location",
      String("http://") + WiFi.softAPIP().toString(),
      true
    );
    server.send(302, "text/plain", "");
  } else {
    handleRoot();
  }
}

/* ================== SETUP ================== */

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  loadSSID();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSSID);

  IPAddress apIP = WiFi.softAPIP();
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, subnet);

  dnsServer.start(53, "*", apIP);

  server.on("/", handleRoot);
  server.on("/ssid", handleSSIDPage);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.print("AP SSID: ");
  Serial.println(apSSID);
  Serial.print("AP IP: ");
  Serial.println(apIP);
}

/* ================== LOOP ================== */

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
