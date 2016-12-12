#include <Arduino.h>
#include "header.h"

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

void blinkLed(byte id)
{
  digitalWrite(id, LOW);
  delay(1500);
  digitalWrite(id, HIGH);
}

