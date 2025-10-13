#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char* ssid = "AccessPoint";


DNSServer dnsServer;
ESP8266WebServer server(80);

const char* htmlPage = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Captive Portal</title>
    <style>
        #cover{
          top:0;
          left:0;
          right:0;
          bottom:0;
          border:none;
          height:100%;
          width:100%;
          padding:0;
          margin:0;
          position:absolute;
        }
    </style>
</head>
<body>
        <iframe id="cover" src="http://192.168.4.100:8000"></iframe>
</body>
</html>
)";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleNotFound(){
  if(server.hasHeader("Host")){
    server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(),true);
    server.send(302, "text/plain", "");
  } else{
    handleRoot();
  }
}

void setup() {
  Serial.begin(115200);

  // Start in access point mode with the specified SSID and password
  WiFi.softAP(ssid);

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  // Configure DHCP server
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, subnet);

  // Start the web server
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();

  // Initialize EEPROM (optional, only if needed)
  EEPROM.begin(512);

  // DNS server to capture all requests
  dnsServer.start(53, "*", apIP);

  Serial.println("Captive portal with DHCP server and iframe started");
}

void loop() {
  // Handle DNS requests
  dnsServer.processNextRequest();

  // Handle client requests
  server.handleClient();
}
