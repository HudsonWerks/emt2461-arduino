/**
 * Helloworld style, connect an ESP32 to IBM's Watson IoT Platform
 * 
 * Author: Anthony Elder
 * License: Apache License v2
 * 
 * modifactions by Charles A. Hamilton
 */
#include <SPI.h>
#include "WiFi.h"
#include <PubSubClient.h>

//-------- Customise these values -----------
const char* ssid = "wifi_network";
const char* password = "wifi_password";

#define ORG "quickstart" // your organization or "quickstart"
//#define ORG "EMT2461" // your organization or "quickstart"

#define DEVICE_TYPE "esp32" // use this default for quickstart or customize to your registered device type

//#define DEVICE_ID "test1" // use this default for quickstart or customize to your registered device id
#define DEVICE_ID "your_custom_device_name" // customize to your registered device id

#define TOKEN "<yourDeviceToken>" // your device token or not used with "quickstart"

//-------- Customise the above values --------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);

void setup() {
 Serial.begin(115200); delay(1); Serial.println();

 initWiFi();
}

void loop() {

 if (!!!client.connected()) {
   Serial.print("Reconnecting client to "); Serial.println(server);
   while (!!!client.connect(clientId, authMethod, token)) {
     Serial.print(".");
     delay(500);
   }
   Serial.println();
 }

 String payload = "{ \"d\" : {\"counter\":";
 payload += millis()/1000;
 payload += "}}";
 
 Serial.print("Sending payload: "); Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
   Serial.println("Publish ok");
 } else {
   Serial.println("Publish failed");
 }

 delay(3000);
}

void initWiFi() {
 Serial.print("Connecting to "); Serial.print(ssid);
 if (strcmp (WiFi.SSID().c_str(), ssid) != 0) {
   WiFi.begin(ssid, password);
 }
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 } 
 Serial.println(""); Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());
}
