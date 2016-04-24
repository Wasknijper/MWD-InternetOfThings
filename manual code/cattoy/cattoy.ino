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
#include <Servo.h>

char ssid[] = "iPhone van Maaike (2)";
char pass[] = "pw";
WiFiClient  client;
char* host = "www.maaikehek.nl";
String path = "/iot/eindopdracht/movement.json";
const int httpPort = 80;
Servo myservo; 
int inputPIR = D0;

void setup() {
  myservo.attach(D1);  
  Serial.begin(9600);
  
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
}
void loop() {
  HTTPClient http;
  http.begin("http://maaikehek.nl/iot/eindopdracht/servo.txt"); 
  int httpCode = http.GET();        
  String payload = http.getString();
  int pos = payload.toInt();
  Serial.println("servo position " + payload);
  myservo.write(payload.toInt());

 String data;
 String pir;
 pir = String(digitalRead(D0));
 data = "pir=" + pir;
 //POST code inspired by Leander van Baekel
 if (client.connect(host, httpPort)) {
   //make the POST headers and add the data string to it
   client.println("POST /iot/eindopdracht/index.php HTTP/1.1");
   client.println("Host: www.maaikehek.nl:80");
   client.println("Content-Type: application/x-www-form-urlencoded");
   client.println("Connection: close");
   client.print("Content-Length: ");
   client.println(data.length());
   client.println();
   client.print(data);
   client.println();
   Serial.println(data);
   Serial.println("Data send");
 } else {
   Serial.println("Something went wrong");
 }
     
  // wait .5s to reloop this loop
  delay(500);
  
}
