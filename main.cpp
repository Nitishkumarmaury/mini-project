#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "your-ssid";
const char* password = "your-password";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start web server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  if (server.hasArg("coord1") && server.hasArg("coord2") && server.hasArg("coord3") && server.hasArg("coord4")) {
    String coord1 = server.arg("coord1");
    String coord2 = server.arg("coord2");
    String coord3 = server.arg("coord3");
    String coord4 = server.arg("coord4");
    
    // Split each coordinate into longitude and latitude
    float long1, lat1, long2, lat2, long3, lat3, long4, lat4;
    splitCoordinate(coord1, long1, lat1);
    splitCoordinate(coord2, long2, lat2);
    splitCoordinate(coord3, long3, lat3);
    splitCoordinate(coord4, long4, lat4);
    
    // Print messages with 1-second interval
    printMessage(long1, lat1);
    delay(1000);
    printMessage(long2, lat2);
    delay(1000);
    printMessage(long3, lat3);
    delay(1000);
    printMessage(long4, lat4);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void splitCoordinate(String coord, float& longitude, float& latitude) {
  int commaIndex = coord.indexOf(',');
  if (commaIndex != -1) {
    longitude = coord.substring(0, commaIndex).toFloat();
    latitude = coord.substring(commaIndex + 1).toFloat();
  }
}

void printMessage(float longitude, float latitude) {
  Serial.print("Longitude:");
  Serial.print(longitude, 4);
  Serial.print(", Latitude:");
  Serial.println(latitude, 4);
}