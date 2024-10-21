#include <EEPROM.h>

//----------- Matrix push buttons
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 7;
int pin8 = 8;
//----------- No matrix push button, button *
int pin4 = 10;
int pin9 = 9;
//----------- Electromagnetic bolt
int magnet1 = A1;
//----------- Leds
int positive = 11;
int green = A5;
int orange = A4;
int red = A3;

int keyColumn; 
int keyRaw;
boolean keyDetected = false; 
boolean insideNewPasswordMenu = false;
byte password[] = {1, 1, 1, 2, 2, 2};
byte passwordEepromAddress[] = {1, 2, 3, 4, 5, 6};
byte newPasswordCounter = 0;
byte numberOfDigits = 6; 
const byte C = 4;//Columns
const byte R = 3;//Raws
bool match = false;
int columns[C] = {pin5, pin6, pin7, pin8};
int raws[R] = {pin1, pin2, pin3};
int result[C][R]; 
int mainMenuVariable = HIGH;

void setup() {
  pinMode(positive, OUTPUT);
  analogWrite(positive, 20);
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, LOW);
  pinMode(pin9, INPUT);
  digitalWrite(pin9, HIGH);
  pinMode(magnet1, OUTPUT);
  Serial.begin(9600);
  result[0][0] = 1; result[0][1] = 2; result[0][2] = 3; result[1][0] = 4; result[1][1] = 5;
  result[1][2] = 6; result[2][0] = 7; result[2][1] = 8; result[2][2] = 9; result[3][1] = 0;
  result[3][2] = 11;
  pinSetUp(columns, raws);
  readPasswordInEeprom(numberOfDigits); 
  printPasswordInEeprom(numberOfDigits);
  startingLights();
}
void loop() {
  Serial.println("Main Menu.");
  if (mainMenuVariable == LOW) {
    pinMode(red, OUTPUT);
    Serial.println("Inside new password conditional.");
    mainMenuVariable = HIGH;
    insideNewPasswordMenu = true;
    pinMode(orange, OUTPUT);
    delay(100);
    pinMode(orange, INPUT);
    delay(100);
    pinMode(orange, OUTPUT);
    delay(100);
    pinMode(orange, INPUT);
    delay(100);
    confirmation (password, numberOfDigits, columns, raws);
    if (insideNewPasswordMenu)
      newPassword (password, numberOfDigits, columns, raws);
    pinMode(red, INPUT);
  }
  else {
    confirmation (password, numberOfDigits, columns, raws);
    openClose();
  }
}
