#include <WiFi.h>
#include <WebServer.h>

/* SSID & Password */
const char* ssid = "Relay";
const char* password = "test";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t relayPin = 15;
bool relayStatus = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/relayon", handle_relayon);
  server.on("/relayoff", handle_relayoff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if(relayStatus) {
  digitalWrite(relayPin, HIGH);
  }
  else {
  digitalWrite(relayPin, LOW);
  }
}
void handle_OnConnect() {
  relayStatus = LOW;
  Serial.println("GPIO-15 Status: OFF");
  server.send(200, "text/html", SendHTML(relayStatus)); 
}

void handle_relayon() {
  relayStatus = HIGH;
  Serial.println("GPIO-15 Status: ON");
  server.send(200, "text/html", SendHTML(true,relayStatus)); 
}

void handle_relayoff() {
  relayStatus = LOW;
  Serial.println("GPIO-15 Status: OFF");
  server.send(200, "text/html", SendHTML(relayStatus,true)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found /:");
}

String SendHTML(uint8_t relaystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(relaystat)
  {ptr +="<p>Relay Status: ON</p><a class=\"button button-off\" href=\"/relayoff\">OFF</a>\n";}
  else
  {ptr +="<p>Relay Status: OFF</p><a class=\"button button-on\" href=\"/relayon\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
