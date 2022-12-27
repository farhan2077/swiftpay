#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
//  char tempVar[] = "2A 17 6E DC";
  String tempVar = "2A 17 6E DC";
  static char outputJson[40];
  // allocate the JSON document
  StaticJsonDocument<50> doc;
  // add value in the document
  doc["reading"] = "2A 17 6E DC";
  // generate the minified JSON and store it in outputJson
  serializeJson(doc, outputJson);
  delay(1000 * 1);
  Serial.println(outputJson);
}
