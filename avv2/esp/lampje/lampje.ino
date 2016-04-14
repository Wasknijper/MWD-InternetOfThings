#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>

char ssid[] = "iPhone van Maaike (2)"; //  your network SSID (name) 
char pass[] = "pw"; // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;

void setup() {
  WiFi.begin(ssid, pass);
  Serial.begin(9600);

  pinMode(D0, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  HTTPClient http;
  http.begin("http://maaikehek.nl/iot/lampje.txt"); 

  int httpCode = http.GET();        
  String payload = http.getString();

  if (payload == "off") {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(D0, LOW);
    Serial.println(payload);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(D0, HIGH);
    Serial.println(payload);
  }
  
//  digitalWrite(LED_BUILTIN, LOW);
//  digitalWrite(D0, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);              // wait for a second
//  digitalWrite(D0, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
}
