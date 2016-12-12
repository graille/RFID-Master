#include "header.h"

//TODO: flush lcd after a delay

MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN);
LiquidCrystal_I2C lcd(0x27,16,2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

unsigned int people_inside=0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
}


void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Number of person inside: ");
  Serial.println(people_inside);
  Serial.println("Authenticating...");
  RFID_authenticate(mfrc522);

  Serial.println("Reading attributes...");
  byte attributes[3]; // Location, status, access
  RFID_readAttributes(mfrc522, attributes);

  if (attributes[1] == SUPERVISOR)
  {
    Serial.println("Admin detected.");
    //lcd.setCursor(2,0);
    lcd.print("People: ");
    lcd.print(people_inside);
  }

  if (attributes[2] == AUTHORIZED)
  {
    blinkLed(GREEN_LED);
    if (attributes[0] == INSIDE)
    {
      // Write on tag: user now outside
      Serial.println("User was inside.");
      people_inside--;
    }
    else
    {
      // Write on tag: user now inside
      Serial.println("User was outside.");
      people_inside++;
    }
    
    // Display name on lcd
    char name[18];
    RFID_readName(mfrc522, name);
    lcd.setCursor(0,0);
    lcd.print("Hi ");
    lcd.print(name);
  }
  else
  {
    blinkLed(RED_LED);
    Serial.println("User not authorized.");
  }

  Serial.println();
}
