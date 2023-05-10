#if !defined(ARDUINO_ESP32_DEV) // ESP32
#error Use this example with the ESP32
#endif

#include "rn2xx3.h"

#include <HardwareSerial.h>
HardwareSerial LoRaSerial(2);
#define RXD2 16
#define TXD2 17

#define RESET 32

rn2xx3 lorawan(LoRaSerial);

void setup() {
  Serial.begin(115200);
  Serial.println(F("--- rn2xx3 Bridge ---"));

  LoRaSerial.begin(57600, SERIAL_8N1, RXD2, TXD2);

  delay(1000);

  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, LOW);
  delay(100);
  digitalWrite(RESET, HIGH);

  lorawan.autobaud();
}

void loop() {
  if(LoRaSerial.available()){
    Serial.write(LoRaSerial.read());
  }

  if(Serial.available()){
    LoRaSerial.write(Serial.read());
  }  
}