#include <EEPROM.h>

//----------- Matrix push buttons
int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int pin4 = 9;  //No matrix push button, button *
int pin5 = 8;
int pin6 = 7;
int pin7 = 6;
int pin8 = 5;
int pin9 = 4;  //No matrix push button, button *
//----------- Electromagnetic bolt
int magnet1 = A5;
//----------- Leds
int green = A4;
int orange = A3;
int red = A2;

int keyColumn;
int keyRaw;
boolean keyDetected = false;
boolean insideNewPasswordMenu = false;
byte password[] = { 1, 1, 1, 2, 2, 2 };
byte passwordEepromAddress[] = { 1, 2, 3, 4, 5, 6 };
byte newPasswordCounter = 0;
byte numberOfDigits = 6;
const byte C = 4;  //Columns
const byte R = 3;  //Raws
bool match = false;
int columns[C] = { pin5, pin6, pin7, pin8 };
int raws[R] = { pin1, pin2, pin3 };
int result[C][R];
int mainMenuVariable = HIGH;

void setup() {
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, LOW);
  pinMode(pin9, INPUT);
  digitalWrite(pin9, HIGH);
  Serial.begin(9600);
  result[0][0] = 1;
  result[0][1] = 2;
  result[0][2] = 3;
  result[1][0] = 4;
  result[1][1] = 5;
  result[1][2] = 6;
  result[2][0] = 7;
  result[2][1] = 8;
  result[2][2] = 9;
  result[3][1] = 0;
  result[3][2] = 11;
  pinSetUp(columns, raws);
  readPasswordInEeprom(numberOfDigits);
  printPasswordInEeprom(numberOfDigits);
  startingLights();
  Serial.println("Setup");
}
void loop() {
  Serial.println("Main Menu.");
  if (mainMenuVariable == LOW) {
    analogWrite(red, 255);
    Serial.println("Inside new password conditional.");
    mainMenuVariable = HIGH;
    insideNewPasswordMenu = true;
    analogWrite(orange, 255);
    delay(100);
    analogWrite(orange, 0);
    delay(100);
    analogWrite(orange, 255);
    delay(1000);
    analogWrite(orange, 0);
    confirmation(password, numberOfDigits, columns, raws);
    if (insideNewPasswordMenu)
      newPassword(password, numberOfDigits, columns, raws);
    analogWrite(red, 0);
  } else {
    Serial.println("Inside Else");
    confirmation(password, numberOfDigits, columns, raws);
    openClose();
  }
}
