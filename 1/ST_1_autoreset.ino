/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: AP-1.ino
 *  small changes by Nicu FLORICA (niq_ro)
 */
 

#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

byte ledPin = 2;
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

int contor = 0;

void setup() {
  ESP.wdtDisable();
  delay(500);
  Serial.begin(9600);
  delay(500);
  ESP.wdtEnable(WDTO_4S);
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
  Serial.println("From the AP: " + answer);
  client.flush();
  digitalWrite(ledPin, HIGH);
  client.stop();
  Serial.print("Counter = ");
  Serial.println(contor);
  contor = contor +1;
  delay(3000);
if (WiFi.status() != WL_CONNECTED)  // https://www.reddit.com/r/esp8266/comments/3rnytf/esp8266_arduino_reconnect_on_wifi_loss/
                                    // http://nicuflorica.blogspot.com/2016/12/comanda-led-de-pe-pagina-web-creata-cu.html 
{                                    //   https://techtutorialsx.com/2017/12/29/esp8266-arduino-software-restart/
    Serial.println("Reset..");
    ESP.restart();
}
}
