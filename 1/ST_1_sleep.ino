/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: AP-1.ino
 *  small and "smart" changes by Nicu FLORICA (niq_ro)
 *  http://www.arduinotehniq.com
 *  add sleep mode - https://openhomeautomation.net/esp8266-battery
 */

#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

int contor = 0;

// Time to sleep (in seconds):
const int sleepTimeS = 10;
void setup() {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");  
  Serial.println("ESP8266 in normal mode");
  delay(5);
  WiFi.disconnect();
  delay(5);
  WiFi.mode(WIFI_STA);
  delay(5);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print("Hi, boss!\r"));
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  delay(100);
  Serial.println("----------------");

  digitalWrite(ledPin, HIGH);   // led off
  client.stop();
  
  // Sleep
  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(sleepTimeS * 1000000);
}

void loop() {
// nothing 
}
