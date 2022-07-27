#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#ifdef ESP8266 
       #include <ESP8266WiFi.h>
#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "A1521"    
#define WIFI_PASS         "netmegant"
#define APP_KEY           "a9a05382-bf7e-4e81-8c55-cc546db648f2"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "9657df99-15db-4816-a0ab-cab9063e795a-7c43492d-d444-4ade-a1aa-c8375403428d"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "6135a1ba2c014831f8246ca4"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         9600                // Change baudrate to your need

#define RELAY_PIN         13                  // Pin where the relay is connected (D5 = GPIO 14 on ESP8266)

bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN, ! state);             // set pin state
  return true;                                // request handled properly
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);                 // set relay-pin to output mode
  WiFi.begin(WIFI_SSID, WIFI_PASS);           // start wifi

  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];   // create new switch device
  mySwitch.onPowerState(onPowerState);                // apply onPowerState callback
  SinricPro.begin(APP_KEY, APP_SECRET);               // start SinricPro
}

void loop() {
  SinricPro.handle();                         // handle SinricPro commands
}
