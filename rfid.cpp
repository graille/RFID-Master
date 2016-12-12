#include "rfid.h"

MFRC522::StatusCode RFID_authenticate(MFRC522 mfrc522)
{
  MFRC522::MIFARE_Key key;

  // Use default key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  MFRC522::StatusCode status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 3, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
      Serial.print(F("PCD_Authenticate() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
  }

  return status;
}

MFRC522::StatusCode RFID_read(MFRC522 mfrc522, byte blockAddr, byte* buffer)
{
  // Size of buffer must be 18
  byte size = 18;//sizeof(buffer);
  MFRC522::StatusCode status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  return status;
}

MFRC522::StatusCode RFID_write(MFRC522 mfrc522, byte blockAddr, byte* buffer)
{
  // Size must be 16
  MFRC522::StatusCode status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Write() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.println();
  return status;
}


void RFID_readName(MFRC522 mfrc522, char* name)
{
  RFID_read(mfrc522, 1, name);
}

void RFID_readAttributes(MFRC522 mfrc522, byte* data)
{
  // data must be 3-bytes long. 
  byte buffer[18];
  RFID_read(mfrc522, 2, buffer);
  *data = buffer[0] & LOCATION_MASK;
  *(++data) = buffer[0] & RIGHTS_MASK;
  *(++data)= buffer[1]; // Current access right
}

