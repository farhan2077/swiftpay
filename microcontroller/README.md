<h1 align="center">

[SwiftPay](https://github.com/farhan2077/swiftpay) - Microcontroller

</h1>

## Prerequisites

- [Git](https://git-scm.com/) `v2.37+`
- [Arduino IDE](https://www.arduino.cc/en/software) `v1.8.19+`
- Required components:
  - Arduino Uno
  - Servo motor
  - NodeMCU ESP8266 WiFi module
  - MFRC-522 RFID Module
  - Others (Eg: breadboard, wires, battery etc)

## Installations & setup

1. Add `secret.h` similar to `secret.h.example` where `secret.h.example` is situated (Associated with ESP32 module)
2. Install following board and libraries in Arduino IDE

### Board

| Board name | Author            | Version | Link(s)                                                                                                                                                        |
| ---------- | ----------------- | ------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ESP32      | ESP8266 Community | `2.0.6` | [Installation process](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) <br/> [GitHub](https://github.com/espressif/arduino-esp32) |

Other instructions for ESP32 Board

- Board selection: ESP32 Dev Module
- Code uploading procedure
  1. Press and hold **BOOT** button
  2. Click **EN** button
  3. Click **Upload** button in IDE
  4. Release **BOOT** button when "Connecting..." is displayed in console

### Llibraries

| Lirary name | Author              | Version  | Link(s)                                            |
| ----------- | ------------------- | -------- | -------------------------------------------------- |
| ArduinoJson | Benoît Blanchon     | `6.19.4` | [GitHub](https://github.com/bblanchon/ArduinoJson) |
| MFRC522     | Miguel André Balboa | `1.4.10` | [GitHub](https://github.com/miguelbalboa/rfid)     |

<!-- _Following libraries are already installed after ESP8266 board installation_

| Lirary name       | Link(s)                                                                              |
| ----------------- | ------------------------------------------------------------------------------------ |
| ESP8266WiFi       | [GitHub](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)       |
| ESP8266HTTPClient | [GitHub](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient) |

More:

- HTTP code references of ESP8266HTTPClient library can be found [here](https://github.com/esp8266/Arduino/blob/137d421fdd27fc612c8a63ec6dda02a14a28771f/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h) -->
