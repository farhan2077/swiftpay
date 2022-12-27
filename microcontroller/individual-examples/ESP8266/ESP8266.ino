#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define ssid "Bufferland"
#define password "colorcode#0000"
#define apiUrl "https://happy-plant-backend-production.up.railway.app/api/v1/plants"

//const char* ssid = "Bufferland";
//const char* password = "colorcode#0000";
//const char* apiUrl = "https://happy-plant-backend-production.up.railway.app/api/v1/plants";

int timeInterval = 5;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting ESP8266...");

  // wifi module setup
  WiFi.begin(ssid, password);
  Serial.println("Connecting with WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  delay(1000);
  Serial.println("Connected with wifi successfully.");
}

void loop() {
  // id = "2A 17 6E DC"
  //  static char idReading[] = "1234";
  static char outputJson[20];

  // allocate the JSON document
  StaticJsonDocument<200> doc;
  //  add value in the document
  doc["reading"] = "1234";
  // generate the minified JSON and store it in outputJson
  serializeJson(doc, outputJson);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    http.begin(client, apiUrl);
    http.addHeader("Content-Type", "application/json");
    Serial.println("-------------");

    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST(outputJson);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String payload = http.getString();
        Serial.println("Received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(1000 * timeInterval);
  } else {
    Serial.println("Problem with WiFi connection");
  }
}
