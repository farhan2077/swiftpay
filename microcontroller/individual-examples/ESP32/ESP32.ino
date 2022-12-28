#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "secret.h"    // includes wifi credentials & backend api url

//#define ssid "Bufferland"
//#define password "colorcode#0000"
//#define apiUrl "https://happy-plant-backend-production.up.railway.app/api/v1/plants"

const char* ssid = "Kobi's room";
const char* password = "khaba911628";
const char* apiUrl = "https://happy-plant-backend-production.up.railway.app/api/v1/plants";

int timeInterval = 5;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting ESP32...");

  // wifi module setup
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi network successfully.");
}

void loop() {
  static char outputJson[20];

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient client;
    client.begin(apiUrl);
    client.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    doc["reading"] = "1234";
    serializeJson(doc, outputJson);

    int httpCode = client.POST(outputJson);

    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[httpCode]: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String payload = client.getString();
        Serial.print("[payload]: ");
        Serial.println(payload);
      }
    } else {
      Serial.printf("POST failed, error: %s\n", client.errorToString(httpCode).c_str());
    }
    client.end();
    delay(5000);
  } else {
    Serial.println("Problem with WiFi connection");
  }
}
