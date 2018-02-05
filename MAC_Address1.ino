/*
 * Start ESP-32 WiFi and print the MAC address to Serial
 */

#include <WiFi.h>

byte mac[6];

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.print("Program starting...");

    WiFi.begin();
    Serial.println("WiFi starting...");
    WiFi.macAddress(mac);
  
}

void loop(){
      Serial.print("MAC Address: ");
      
      for (int i = 0; i < 6; i++) {
        if (i) Serial.write(':');
        if (mac[i] < 16) Serial.write('0');
        Serial.print(mac[i], HEX);
    }
    
    delay(3000);
    Serial.print("\n");
}
