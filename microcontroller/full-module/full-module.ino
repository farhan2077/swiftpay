#include <ArduinoJson.h>
#include <MFRC522.h>
#include <SPI.h>
#include <HTTPClient.h>
#include "NewPing.h"
#include <ESP32Servo.h>

#include "secret.h"

// following pins are for ESP32
#define SS_PIN 21        // slave select pin
#define RST_PIN 22       // reset pin
#define TRIGGER_PIN 2    // ESP32 pin GIOP26 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 4       // ESP32 pin GIOP25 connected to Ultrasonic Sensor's ECHO pin
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters).

int servoPos = 0;  // servo
int servoPin = 12; // servo
float distance;    // ultrasonic sensor
String initialUid = "empty";

Servo servo;
MFRC522 mfrc522(SS_PIN, RST_PIN);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  Serial.begin(115200);
  SPI.begin();

  // rfid
  mfrc522.PCD_Init();
  delay(4);

  // ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // servo
  servo.attach(servoPin);

  // wifi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
}

void loop()
{
  Serial.println("-----START-----");

  delay(100);

  // start to read rfid
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String uid = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    uid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  uid = uid.substring(1);

  static char outputJson[40];
  StaticJsonDocument<50> doc;
  doc["vehicleId"] = uid;
  serializeJson(doc, outputJson);

  delay(500);

  if (WiFi.status() == WL_CONNECTED)
  {
    if ((initialUid == "empty") & (uid == ""))
    {
      // NO PASS
      initialUid = uid;
      Serial.println("NO PASS");
    }
    else
    {
      // NEW/SAME vehicle
      HTTPClient client;

      Serial.println(uid);
      Serial.println(outputJson);

      // POST - add transaction
      client.begin(apiUrlAddTransaction);
      client.addHeader("Content-Type", "application/json");
      int httpCode = client.POST(outputJson);

      if (httpCode > 0) // positive - ADD TRANSACTION
      {
        Serial.printf("[httpCode: POST]: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK) // 200 - ADD TRANSACTION
        {
          client.end();

          delay(1000);

          // PATCH - update Balcnce
          client.begin(apiUrlUpdateBalance);
          client.addHeader("Content-Type", "application/json");
          int httpCode = client.PATCH(outputJson);

          if (httpCode > 0) // positive - UPDATE BALANCE
          {
            Serial.printf("[httpCode: PATCH]: %d\n", httpCode);

            if (httpCode == HTTP_CODE_OK) // 200 - UPDATE BALANCE
            {
              // allow pass but check first if the vehicle is still there
              client.end();
              Serial.println("PASS");
              Serial.println("Gate is opening");

              // replace delay and put servo angle 0 to 60
              for (servoPos = 0; servoPos <= 90; servoPos += 1)
              {
                servo.write(servoPos);
                delay(15);
              }

              Serial.println("Gate is OPEN");
              Serial.print("Waiting for vehicle to pass");

              distance = sonar.ping_cm();

              while (distance < 10) // if vehicle is within 15 cm or nearer, check again to see if vehicle has passed
              {
                delay(500);
                distance = sonar.ping_cm();
                Serial.print(".");
              }

              delay(5000);

              // vehicle has passed, close gate
              // replace delay and put servo angle 60 to
              for (servoPos = 90; servoPos >= 0; servoPos -= 1)
              {
                servo.write(servoPos);
                delay(15);
              }
              Serial.println("Gate is CLOSED");
            }
          }
          else // negative - UPDATE BALANCE
          {
            Serial.printf("PATCH failed, error: %s\n", client.errorToString(httpCode).c_str());
            // start again after some delay
            delay(5000);
          }
        }
        else if (httpCode == HTTP_CODE_NOT_FOUND) // 404 - ADD TRANSACTION
        {
          Serial.println("NO PASS");
          Serial.println("Reason: vehicle not registered");
          // start again after some delay
          delay(5000);
        }
        else if (httpCode == HTTP_CODE_BAD_REQUEST) // 400 - ADD TRANSACTION
        {
          Serial.println("NO PASS");
          Serial.println("Reason: low balance of user");
          // start again after some delay
          delay(5000);
        }
        else // positive - ADD TRANSACTION - other respionse from server
        {
          Serial.println("NO PASS");
          Serial.println("There was an error, checking again");
          // start again after some delay
          delay(5000);
        }
      }
      else // negative - ADD TRANSACTION
      {
        Serial.printf("POST failed, error: %s\n", client.errorToString(httpCode).c_str());
        // start again after some delay
        delay(5000);
      }
    }
  }
  else
  {
    Serial.println("Problem with WiFi connection");
  }
}
