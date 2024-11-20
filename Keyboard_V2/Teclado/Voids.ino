void pinSetUp(int array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    pinMode(array1[i], OUTPUT);
  }
  for (int j = 0; j < 3; j++) {
    pinMode(array2[j], INPUT_PULLUP);
  }
}
void mainKeyCaptation(int array1[], int array2[]) {
  int variable;
  for (int i = 0; i < 4; i++) {
    digitalWrite(array1[i], LOW);
    for (int j = 0; j < 3; j++) {
      variable = digitalRead(array2[j]);
      if (variable == LOW) {
        keyColumn = i;
        keyRaw = j;
        keyDetected = true;
        break;
      }
    }
    digitalWrite(array1[i], HIGH);
  }
}
boolean getKeyDetectedState() {
  return keyDetected;
}
int getKeyPressedValue() {
  return result[keyColumn][keyRaw];
}
void confirmation(byte password[], byte numberOfDigits, int array1[], int array2[]) {
  analogWrite(orange, 255);
  delay(100);
  analogWrite(orange, 0);
  delay(100);
  analogWrite(orange, 255);
  delay(100);
  analogWrite(orange, 0);
  int newPasswordCounter = 0;
  int inputPassword[numberOfDigits];
  boolean numberTyped = false;
  boolean cancelled = false;
  while (newPasswordCounter < numberOfDigits) {
    mainMenuVariable = digitalRead(pin9);
    if ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu)) {
      Serial.println("Password confirmation cancelled.");
      cancelled = true;
      mainMenuVariable = HIGH;
      insideNewPasswordMenu = false;
      break;
    } else if (mainMenuVariable == LOW) {
      Serial.println("Requesting new password menu.");
      cancelled = true;
      break;
    }
    mainKeyCaptation(array1, array2);
    if (getKeyDetectedState()) {
      numberTyped = true;
      keyDetected = false;
      analogWrite(orange, 255);
      delay(300);
      analogWrite(orange, 0);
      inputPassword[newPasswordCounter] = getKeyPressedValue();
      Serial.println("Pressed key = " + String(inputPassword[newPasswordCounter]));
      newPasswordCounter++;
    }
  }
  if (cancelled == false) {
    Serial.println("Inside Password checking.");
    for (int i = 0; i < numberOfDigits; i++) {
      Serial.println("Input = " + String(inputPassword[i]) + "; password = " + String(password[i]));
      if (inputPassword[i] == password[i]) {
        Serial.println("Match!");
        match = true;
      } else {
        Serial.println("No match!");
        match = false;
        break;
      }
    }
  }
  Serial.println("Leaving confirmation menu.");
}
void burnPasswordInEeprom(byte numberOfDigits) {
  for (int i = 100; i < numberOfDigits; i++) {
    EEPROM.write(i, password[i-100]);
  }
}
void readPasswordInEeprom(byte numberOfDigits) {
  for (int i = 0; i < numberOfDigits; i++) {
    password[i] = EEPROM.read(i);
  }
}
void printPasswordInEeprom(byte numberOfDigits) {
  for (int i = 100; i < numberOfDigits; i++) {
    Serial.println("i = " + String(i) + "; " + EEPROM.read(i));
  }
}
void checkEepromState(byte numberOfDigits) {
  for (int i = 100; i < numberOfDigits; i++) {
    if(EEPROM.read(i) != password[i-100]){
      Serial.println("Inside");
      Serial.println(i);
      burnPasswordInEeprom(numberOfDigits);
      break;
    }
  }
}


void newPassword(byte password[], byte numberOfDigits, int array1[], int array2[]) {
  Serial.println("Inside new password void");
  boolean cancelled = false;
  if (match) {
    Serial.println("New Password Menu.");
    analogWrite(green, 255);
    delay(250);
    analogWrite(green, 0);
    int newPasswordCounter = 0;
    while (newPasswordCounter < numberOfDigits) {
      mainMenuVariable = digitalRead(pin9);
      if (mainMenuVariable == LOW) {
        cancelled = true;
        mainMenuVariable = HIGH;
        insideNewPasswordMenu = false;
        readPasswordInEeprom(numberOfDigits);
        break;
      }
      mainKeyCaptation(array1, array2);
      if (getKeyDetectedState()) {
        keyDetected = false;
        analogWrite(orange, 255);
        delay(1250);
        analogWrite(orange, 0);
        password[newPasswordCounter] = getKeyPressedValue();
        newPasswordCounter++;
      }
    }
    if (cancelled == false) {
      Serial.println("Burning EEPROM.");
      analogWrite(green, 255);
      delay(1000);
      analogWrite(green, 0);
      burnPasswordInEeprom(numberOfDigits);
    }
    match = false;
  } else {
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
    delay(100);
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
  }
  insideNewPasswordMenu = false;
  Serial.println("Leaving Password Menu.");
}
void getNewPassword() {
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.print(password[i]);
  }
  delay(2000);
}
void startingLights() {
  analogWrite(red, 255);
  analogWrite(orange, 255);
  analogWrite(green, 255);
  delay(100);
  analogWrite(red, 0);
  analogWrite(orange, 0);
  analogWrite(green, 0);
  delay(100);
  analogWrite(red, 255);
  analogWrite(orange, 255);
  analogWrite(green, 255);
  delay(100);
  analogWrite(red, 0);
  analogWrite(orange, 0);
  analogWrite(green, 0);
}
void openClose() {
  if (match) {
    analogWrite(bolt, 255);
    analogWrite(green, 255);
    delay(2000);
    analogWrite(bolt, 0);
    analogWrite(green, 0);
    match = false;
  } else {
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
    delay(100);
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
  }
}
