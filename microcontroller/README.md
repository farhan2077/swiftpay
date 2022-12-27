<h1 align="center">

[SwiftPay](https://github.com/farhan2077/swiftpay) - Microcontroller

</h1>

## Installations & setup

### Prerequisites

- [Git](https://git-scm.com/) `v2.37+`
- [Arduino IDE](https://www.arduino.cc/en/software) `v1.8.19+`
- Required components:
  - Arduino Uno
  - Servo motor
  - NodeMCU ESP8266 WiFi module
  - MFRC-522 RFID Module
  - Others (Eg: breadboard, wires, battery etc)

Install following boards and libraries in Arduino IDE

### Board

| Lirary name | Author            | Version | Link(s)                                                                                                                                     |
| ----------- | ----------------- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| esp8266     | ESP8266 Community | `3.0.1` | [Installation process](https://arduino-esp8266.readthedocs.io/en/latest/installing.html) <br/> [GitHub](https://github.com/esp8266/Arduino) |

NodeMCU

### Llibraries

| Lirary name | Author              | Version  | Link(s)                                            |
| ----------- | ------------------- | -------- | -------------------------------------------------- |
| ArduinoJson | Benoît Blanchon     | `6.19.4` | [GitHub](https://github.com/bblanchon/ArduinoJson) |
| MFRC522     | Miguel André Balboa | `1.4.10` | [GitHub](https://github.com/miguelbalboa/rfid)     |

_Following libraries are already installed after ESP8266 board installation_

| Lirary name       | Link(s)                                                                              |
| ----------------- | ------------------------------------------------------------------------------------ |
| ESP8266WiFi       | [GitHub](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)       |
| ESP8266HTTPClient | [GitHub](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient) |

More:

1. HTTP code references of ESP8266HTTPClient library can be found [here](https://github.com/esp8266/Arduino/blob/137d421fdd27fc612c8a63ec6dda02a14a28771f/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h)
