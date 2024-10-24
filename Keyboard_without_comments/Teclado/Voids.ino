void pinSetUp (int array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    pinMode(array1[i], OUTPUT);
  }
  for (int j = 0; j < 3; j++) {
    pinMode(array2[j], INPUT);
    digitalWrite(array2[j], HIGH);
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

int getKeyPressedValue () {
  return result[keyColumn][keyRaw];
}
void confirmation (byte password[], byte numberOfDigits, int array1[], int array2[]) {
  pinMode(orange, OUTPUT);
  delay(100);
  pinMode(orange, INPUT);
  delay(100);
  pinMode(orange, OUTPUT);
  delay(100);
  pinMode(orange, INPUT);
  delay(100);
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
    }
    else if (mainMenuVariable == LOW) {
      Serial.println("Requesting new password menu.");
      cancelled = true;
      break;
    }
    mainKeyCaptation(array1, array2);
    if (getKeyDetectedState()) {
      numberTyped = true;
      keyDetected = false;
      pinMode(orange, OUTPUT);
      delay(300);
      pinMode(orange, INPUT);
      inputPassword[newPasswordCounter] = getKeyPressedValue();
      newPasswordCounter++;
    }
  }
  if (cancelled == false) {
    Serial.println("Inside Password checking.");
    for (int i = 0; i < numberOfDigits; i++) {
      if (inputPassword[i] == password[i]) {
        Serial.println("Match!");
        match = true;
      }
      else {
        Serial.println("No match!");
        match = false;
        break;
      }
    }
  }
  Serial.println("Leaving confirmation menu.");
}

void burnPasswordInEeprom(byte numberOfDigits) {
  for (int i = 0; i < numberOfDigits; i++) {
    EEPROM.write(passwordEepromAddress[i], password[i]);
  }
}
void readPasswordInEeprom(byte numberOfDigits) {
  for (int i = 0; i < numberOfDigits; i++) {
    password[i] = EEPROM.read(passwordEepromAddress[i]);
  }
}
void printPasswordInEeprom(byte numberOfDigits) {
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.println(EEPROM.read(passwordEepromAddress[i]));
  }
}

void newPassword (byte password[], byte numberOfDigits, int array1[], int array2[]) {
  Serial.println("Inside new password void");
  boolean cancelled = false;
  if (match) {
    Serial.println("New Password Menu.");
    pinMode(green, OUTPUT);
    delay(250);
    pinMode(green, INPUT);
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
        pinMode(orange, OUTPUT);
        delay(1250);
        pinMode(orange, INPUT);
        password[newPasswordCounter] = getKeyPressedValue();
        newPasswordCounter++;
      }
    }
    if (cancelled == false) {
      Serial.println("Burning EEPROM.");
      pinMode(green, OUTPUT);
      delay(1000);
      pinMode(green, INPUT);
      newPasswordCounter = 0;
      burnPasswordInEeprom(numberOfDigits);
    }
  }
  else {
    pinMode(red, OUTPUT);
    delay(100);
    pinMode(red, INPUT);
    delay(100);
    pinMode(red, OUTPUT);
    delay(100);
    pinMode(red, INPUT);
    delay(100);
  }
  match = false;
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
  pinMode(red, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(green, OUTPUT);
  delay(100);
  pinMode(red, INPUT);
  pinMode(orange, INPUT);
  pinMode(green, INPUT);
  delay(100);
  pinMode(red, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(green, OUTPUT);
  delay(100);
  pinMode(red, INPUT);
  pinMode(orange, INPUT);
  pinMode(green, INPUT);
  delay(100);
}
void openClose() {
  if (match) {
    digitalWrite(magnet1, HIGH);
    pinMode(green, OUTPUT);
    delay(2000);
    digitalWrite(magnet1, LOW);
    pinMode(green, INPUT);
  }
  else {
    pinMode(red, OUTPUT);
    delay(100);
    pinMode(red, INPUT);
    delay(100);
    pinMode(red, OUTPUT);
    delay(100);
    pinMode(red, INPUT);
    delay(100);
  }
  match = false;
}
