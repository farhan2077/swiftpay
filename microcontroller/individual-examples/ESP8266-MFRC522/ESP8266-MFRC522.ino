#include <MFRC522.h>
#include <SPI.h>

// following pins are for ESP32
#define SS_PIN    21    // slave select pin
#define RST_PIN   22    // reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);              // optional
}

void loop() {
  Serial.println("-----START-----");
  delay(1000);
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }    

  Serial.print("UID tag :");
  String uid = "";

  // read uid
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    uid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println(uid);
}
