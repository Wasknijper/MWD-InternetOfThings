/*
  Based on the WriteVoltage example from the ThingSpeak Library
*/

#include "ThingSpeak.h"

char ssid[] = "iPhone van Maaike (2)";          //  your network SSID (name)
char pass[] = "password";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;
unsigned long myChannelNumber = 105996;
const char * myWriteAPIKey = "APIKey";

void setup() {
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  Serial.begin (9600);
  
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  //float value = sensorValue;

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 1, sensorValue, myWriteAPIKey);
  Serial.println (sensorValue);
  delay(15000); // ThingSpeak will only accept updates every 15 seconds.
}
