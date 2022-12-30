// Proximity Coupling Device (PCD) > RFID reader
// Proximity Integrated Circuit Card (PICC) > RFID card or tag
// Serial Peripheral Interface (SPI)
// Unique Identification Number (UID)

#include <SPI.h>
#include <MFRC522.h>

// pin-layout = https://github.com/miguelbalboa/rfid#pin-layout
#define RST_PIN    22     // slave select pin
#define SS_PIN    21     // reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);              // optional

}

void loop() {
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

  delay(1000)
}
