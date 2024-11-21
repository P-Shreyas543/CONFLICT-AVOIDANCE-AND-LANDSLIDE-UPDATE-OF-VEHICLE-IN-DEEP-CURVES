#include <ESP8266WiFi.h>

void readMacAddress() {
  String mac = WiFi.macAddress();
  Serial.println(mac);
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);  // Set WiFi mode to Station
  WiFi.begin();
  
  Serial.print("[DEFAULT] ESP8266 Board MAC Address: ");
  readMacAddress();

}

void loop() {

  for (int i = 0; i < 1; i++){
    Serial.print("[DEFAULT] ESP8266 Board MAC Address: ");
    readMacAddress();
  }

  delay(1000);
  
}
