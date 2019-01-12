/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: AP-1.ino
 *  small changes by Nicu FLORICA (niq_ro)
 */
 

#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(9600);
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
  delay(3000);
if (WiFi.status() != WL_CONNECTED)  // https://www.reddit.com/r/esp8266/comments/3rnytf/esp8266_arduino_reconnect_on_wifi_loss/
                                    // http://nicuflorica.blogspot.com/2016/12/comanda-led-de-pe-pagina-web-creata-cu.html
    {
      WiFi.disconnect();
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, pass);
         // Wait for connection
  for (int i = 0; i < 25; i++)
  {
    if ( WiFi.status() != WL_CONNECTED ) {
      delay ( 250 );
   //   digitalWrite(errorPin, LOW);
      Serial.print ( "." );
      delay ( 250 );
   //   digitalWrite(errorPin, HIGH);
    }
  }
    }
  
}
