#include <ESP8266WiFi.h>

#include <EIoTCloudRestApiConfig.h>
#include <EIoTCloudRestApi.h>

EIoTCloudRestApi eiotcloud;

void setup() {
 Serial.begin(9600);
   eiotcloud.begin();
}

void loop() {
 int light = analogRead(A0);
 Serial.print(light);
 eiotcloud.sendParameter("Sendkey", light);
 delay(100);
}
