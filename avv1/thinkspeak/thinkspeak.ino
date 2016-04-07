/*
  WriteVoltage

  Reads an analog voltage from pin 0, and writes it to a channel on ThingSpeak every 20 seconds.

  ThingSpeak ( https://www.thingspeak.com ) is a free IoT service for prototyping
  systems that collect, analyze, and react to their environments.

  Copyright 2015, The MathWorks, Inc.

  Documentation for the ThingSpeak Communication Library for Arduino is in the extras/documentation folder where the library was installed.
  See the accompaning licence file for licensing information.
*/

#ifdef SPARK
#include "ThingSpeak/ThingSpeak.h"
#else
#include "ThingSpeak.h"
#endif

/// ***********************************************************************************************************
// This example selects the correct library to use based on the board selected under the Tools menu in the IDE.
// Yun, Wired Ethernet shield, wi-fi shield, esp8266, and Spark are all supported.
// With Uno and Mega, the default is that you're using a wired ethernet shield (http://www.arduino.cc/en/Main/ArduinoEthernetShield)
// If you're using a wi-fi shield (http://www.arduino.cc/en/Main/ArduinoWiFiShield), uncomment the line below
// ***********************************************************************************************************
//#define USE_WIFI_SHIELD
#ifdef ARDUINO_ARCH_AVR

#ifdef ARDUINO_AVR_YUN
#include "YunClient.h"
YunClient client;
#else

#ifdef USE_WIFI_SHIELD
#include <SPI.h>
// ESP8266 USERS -- YOU MUST COMMENT OUT THE LINE BELOW.  There's a bug in the Arduino IDE that causes it to not respect #ifdef when it comes to #includes
// If you get "multiple definition of `WiFi'" -- comment out the line below.
//#include <WiFi.h>
char ssid[] = "iPhone van Maaike (2)";          //  your network SSID (name)
char pass[] = "ww";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;
#else
// Use wired ethernet shield
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;
#endif
#endif
#endif

#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
char ssid[] = "iPhone van Maaike (2)";          //  your network SSID (name)
char pass[] = "ww";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;
#endif

#ifdef SPARK
TCPClient client;
#endif

/*
  *****************************************************************************************
  **** Visit https://www.thingspeak.com to sign up for a free account and create
  **** a channel.  The video tutorial http://community.thingspeak.com/tutorials/thingspeak-channels/
  **** has more information. You need to change this to your channel, and your write API key
  **** IF YOU SHARE YOUR CODE WITH OTHERS, MAKE SURE YOU REMOVE YOUR WRITE API KEY!!
  *****************************************************************************************/
unsigned long myChannelNumber = 105996;
const char * myWriteAPIKey = "ww";

void setup() {
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_ESP8266)
#ifdef ARDUINO_AVR_YUN
  Bridge.begin();
#else
#if defined(USE_WIFI_SHIELD) || defined(ARDUINO_ARCH_ESP8266)
  WiFi.begin(ssid, pass);
#else
  Ethernet.begin(mac);
#endif
#endif
#endif

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
