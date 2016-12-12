#include <SPI.h>
#include <MFRC522.h>

#define LOCATION_MASK 0
#define RIGHTS_MASK 2

#define OUTSIDE 0
#define INSIDE 1
#define USER 0
#define SUPERVISOR 2

#define AUTHORIZED 1


MFRC522::StatusCode RFID_authenticate(MFRC522 mfrc522);
MFRC522::StatusCode RFID_read(MFRC522 mfrc522, byte blockAddr, byte* buffer);
MFRC522::StatusCode RFID_write(MFRC522 mfrc522, byte blockAddr, byte* buffer);
void RFID_readName(MFRC522 mfrc522, char* name);
void RFID_readAttributes(MFRC522 mfrc522, byte* data);
