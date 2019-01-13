/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: AP-1.ino
 *  small changes by Nicu FLORICA (niq_ro)
 */
 

#include <ESP8266WiFi.h>
/*
extern "C" {
  #include "user_interface.h"
}
*/
byte ledPin = 2;
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

int contor = 0;

void setup() {
  pinMode(D6, OUTPUT); digitalWrite(D6, HIGH);  // hard reset - https://github.com/esp8266/Arduino/issues/1622
 // ESP.wdtDisable();
  delay(500);
  Serial.begin(9600);
  delay(500);
//  ESP.wdtEnable(WDTO_4S);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("ST_1.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
}

void loop() {
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print("Hi, boss!\r"));
  String answer = client.readStringUntil('\r');
  Serial.print("From the AP: " + answer);
 // int result = answer.toInt();
  int i, len;  // https://circuits4you.com/2018/03/09/how-to-convert-int-to-string-on-arduino/
  int result=0; 
  len = answer.length();
/*
  for(i=0; i<len; i++)
  {
    result = result * 10 + ( answer[i] - '0' );
  }
  Serial.print("/");
  Serial.print(result);
*/
  Serial.print("/");
  Serial.println(len);

  client.flush();
  digitalWrite(ledPin, HIGH);
  client.stop();
  Serial.println();
  Serial.print("Counter = ");
  Serial.println(contor);
  contor = contor +1;
  delay(3000);
 
if (WiFi.status() != WL_CONNECTED) 
{
  Serial.println("disconect from wifi - reset");
  digitalWrite(D6, LOW); delay(100); //After than reset no need to delay but I put it for fun :)
 }


if (len < 1)
  {                                   //   https://techtutorialsx.com/2017/12/29/esp8266-arduino-software-restart/
   Serial.println("lost communications - reset");
  digitalWrite(D6, LOW); delay(100); //After than reset no need to delay but I put it for fun :) 
  } 
 
 
if (contor > 500)
  { 
    Serial.println("obercount - reset");
digitalWrite(D6, LOW); delay(100); //After than reset no need to delay but I put it for fun :)
}
}  // https://github.com/esp8266/Arduino/issues/1622
