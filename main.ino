//Display lcd
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

//Fingerprint
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial serial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&serial);

//Variabili
int fingerId;
String nameId = "";

void setup() {
  //Debug
  Serial.begin(9600);
  
  //Display
  lcd.begin(16, 2);
  WriteOnLcd(0, 0, "Benvenuto");

  //Fingerprint
  finger.begin(57600);
  if(finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor");
  } else {
    Serial.println("Fingerprint sensor not found :/");
    ClearScreenLcd();
    WriteOnLcd(0, 0, "Error");
    while(1) { delay(1); }
  }
}

void loop() {
  fingerId = ReadFinger();
  switch(fingerId) {
    case 1:
      nameId = "Andrea Piergiovanni";
      break;
    case 2:
      nameId = "Matteo Coccia";
      break;
    default:
      nameId = "Sconosciuto";
      break;
  }
  Serial.println(nameId);
  ClearScreenLcd();
  WriteOnLcd(0, 0, "Benvenuto");
  WriteOnLcd(1, 0, nameId);
  delay(100);
}

int ReadFinger() {
  uint8_t p = finger.getImage();
  if(p != FINGERPRINT_OK) { return -1; }
  p = finger.image2Tz();
  if(p != FINGERPRINT_OK) { return -1; }
  p = finger.fingerFastSearch();
  if(p != FINGERPRINT_OK) { return -1; }
  return finger.fingerID;
}

void ClearScreenLcd() {
  lcd.clear();
}

void WriteOnLcd(int row, int col, String text) {
  lcd.setCursor(col, row);
  lcd.print(text);
}
