#include "ThingSpeak.h"

#include <ESP8266WiFi.h>
#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

// Setup the WiFi
char ssid[] = "iPhone van Maaike (2)"; //  your network SSID (name) 
char pass[] = "password"; // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;

EIoTCloudRestApi eiotcloud;

// make some variables
int buttonInput = D0;
int soundInput = A0;
int button;
int sound;

// Thinkspeak channel and api key
long myChannelNumber = 105996; // Set channel number
const char * myWriteAPIKey = "APIKey";

void setup() {
  WiFi.begin(ssid, pass);
  Serial.begin(9600);
  
  ThingSpeak.begin(client);  
  eiotcloud.begin();

  pinMode(buttonInput, INPUT);
}

void loop() {
  // read the pins
  sound = analogRead(soundInput);
  button = digitalRead(buttonInput);
  
  ThingSpeak.setField(1, sound);
  ThingSpeak.setField(2, button);  
  // will only update every 15 seconds, even if we send data more often
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
  
  eiotcloud.sendParameter("Write Key", sound);
  eiotcloud.sendParameter("Write Key", button); 
}
