//This method sets the behaviour of each keyboard pin.
void pinSetUp(int array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    /*We set each pin in first array as output. These pins will be the ones sending
    the low signal that will be read by the second array.
    */
    pinMode(array1[i], OUTPUT);
  }
  for (int j = 0; j < 3; j++) {
    /*We set each pin in the second array as INPUT_PULLUP, this will set each pin in a
    HIGH state. These pins will be the ones reading the values from pins in first array. 
    They are HIGH, when we set the ones in first array as low while iterating over them, 
    and later we read values in second array, the one low instead of high, will be our 
    pressed key. It is highly recommended to read "mainKeyCaptation" for a better understanding.

    Pullup resistor connection:
    * Vcc = internal arduino power connection to vcc.
    * ~~ = internal arduino resistance connected to the pin.
    * | = the pin in array2 set as INPUT_PULLUP.
    * || = the pin in array1 set as output.
    * __ = The internal connection between elements
    * _._._._ = External connection between elements.
    * // = push button.
    

    VCC___~~___|_._._._//_._._._||___GND

    When the push button in the matrix keyboard is pressed, the pin set as INPUT_PULLUP, which is
    in a HIGH state, gets connected to the pin set as output, which is connected to GND. This way
    the circuit is closed and the state read in the pin INPUT_PULLUP is LOW.
    */
    pinMode(array2[j], INPUT_PULLUP);
  }
}
//This method checks for a key pressed.
void mainKeyCaptation(int array1[], int array2[]) {
  /*We change each value of first array from HIGH to LOW, sequentially, to check if this
  LOW value is read in any of the members of array2.
  */
  int variable;
  for (int i = 0; i < 4; i++) {
    digitalWrite(array1[i], LOW);
    /*We store in "variable" the reading of each member in second array, for each member
    of first array.*/
    for (int j = 0; j < 3; j++) {
      variable = digitalRead(array2[j]);
      /*If "variable" is equals to LOW, it means we pressed the key that connect both pins,
      represented as a member in each array. A low pulse from pin in array number one
      is sent to pin in array number 2. If this happens we store the number of the iteration 
      for each for loop, which actually are the positions in the array, the pins involved, and 
      we set as true the boolean "keyDetected", that tell us that a key was pressed.
      */
      if (variable == LOW) {
        keyColumn = i;
        keyRow = j;
        keyDetected = true;
        break;
      }
    }
    /*Once the actual array1 iteration is over, we set the current pin in array1 as HIGH again,
    since that's the default behaviour.
    */
    digitalWrite(array1[i], HIGH);
  }
}
//keyDetected getter.
boolean getKeyDetectedState() {
  return keyDetected;
}
//Getter to return the key value for the current keyColumn and keyRow.
int getKeyPressedValue() {
  return result[keyColumn][keyRow];
}
//Method to check if the password entered match the one in Eeprom memory.
void confirmation(byte password[], byte numberOfDigits, int array1[], int array2[]) {
  /*This void will check if the password entered matches the one in Eeprom memory.
  First, orange led blinks twice to indicate that we are currently inside confirmation 
  void. Then we create a few variables/arrays.
  -newPasswordCounter will store the amount of iterations done over the main loop.
  -inputPassword[numberOfDigits] will store the numbers given by the buttoms pressed.
   Its size will be numberOfDigits, set at begging of code.
  -numberTyped will help us to set diferent states for the * button to operate.
  -Cancelled will be used as condition to face the password in the Eeprom memory against
  the entered password. If its value is equals to false, both passwords will be compared; 
  if its value is true, it means that the * button, which is used to cancel, was pressed.
  Then we get into main While loop, which will iterate while newPasswordCounter is lower
  than numberOfDigits, which is one of the parameters of this void. 
  */
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
    /*First we store in mainMenuVariable the value of reading pin9 and, 
    according to its value, we set some conditionals:
    - If mainMenuVariable is equals to low, and at the same time, variable
      numberTyped or insideNewPasswordMenu are True, then we will change the
      value of some variables with the purpose of going back to main menu, 
      cancelling all performed actions, while avoiding getting into password
      change menu.
      * We set cancelled as true. This way we won't get into the last 
        conditional, which checks if the entered password matchs the password 
        stored inside password[]. We don't need it to be checked because *
        button is used as cancel action / password change menu request.
      * We set mainMenuVariable as HIGH again to avoid getting into password
        change menu, since it depends on a conditional if (mainMenuVariable = low).
      * We set insideNewPasswordMenu as false. This variable is set to true when 
        we get in the new password menu. If we press * button while being in the 
        new password menu, it means that we want to go back to main menu, and therefor
        we skip the "if (insideNewPasswordMenu)" conditional that comes next to
        confirmation.
      Finally, we break the main while loop of this void, leaving directly the whole void, 
      and starting again the main loop of the code.
    - If previous conditional is not met, then it means that numberTyped and 
      insideNewPasswordMenu are false, so we still didn't press any number, and we are
      not inside new password menu. So, if * key is pressed, it means that we request 
      the code to take us to new password Menu. In this situation, mainMenuVariable keeps 
      its new low value, we set cancelled as true to avoid getting in the last conditional
      which checks if the typed password matches the password stored inside password[], and we 
      break the main while loop of this void. This way, mainMenuVariable's value is still 
      LOW once the main loop checks if the new password menu conditional is true or not. 
      Since this conditional is if (mainMenuVariable == LOW), we will get inside of it.
    If none of these two conditionals is met, then we will call mainKeyCaptation(array1, 
    array2);, which was explained previously. This method will set keyDetected as true, if a
    key was pressed. In case keyDetected is equals to true, we will get inside
    next conditional, where some actions will be performed:
    - We set numberTyped as true. From now on, if we press * key, code will understand that
      we pressed a key and we need to cancel any action performed. In such stage, it will take 
      us to main code loop according to the first conditional explained previously.
    - We set keyDetected back to false, this way we won´t get inside this conditional until
      we press another key.
    - Orang pin is turned on for 300 milliseconds, and then it is set back to off state. This
      will turn on the LED for that time, showing to the user that a key was pressed.
    - We use newPasswordCounter as the position inside inputPassword[] array, where we will 
      store the value returned by getKeyPressedValue() void. This way, if we pressed the key 
      number 4 as the third number in our password, we will store in the inputPassword[] array
      in the third position the number 4.
    - Finally we newPasswordCounter++ to be able to record the number in the next position of
      the password. Let's keep in mind that this variable is also used to control when the 
      while loop of this method must stop.
    */
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
      newPasswordCounter++;
    }
  }
  /*Finally, if cancelled is still false once we left the while loop, we will get
    inside the conditional. This conditional will check if all values inside
    inputPassword[i], are equals to all values inside the password[i]. Each time 
    both values in same position are equal, "match" variable will be set as true. 
    If this for loop ends, and match is equals to true, we will be able to 
    perform any action depending on "if(match)". As soon as inputPassword 
    doesn't match a value in password[], we won't get inside if conditional, and
    we will perform what's inside else, which is setting match as false, and 
    breaking the for loop, denying the access to whatever action that depends
    on a if(match) conditional, and leaving back to main code loop.
   */
  if (cancelled == false) {
    Serial.println("Inside Password checking.");
    for (int i = 0; i < numberOfDigits; i++) {
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
//Method to burn in the eeprom the new password.
void burnPasswordInEeprom(byte numberOfDigits) {
  /*The next for loop will perform its action while i < numberOfDigits. We
  will write in the eeprom memory, each number of the current password. 
  For that, we will tell the system that we want to save the i number in
  password's array, in the i address of the eeprom.
   */
  Serial.println("Burning in eeprom the values of password[]");
  for (int i = 0; i < numberOfDigits; i++) {
    EEPROM.write(i, password[i]);
  }
}
//Method to set de values of password on each power on.
void readPasswordInEeprom(byte numberOfDigits) {
  /*The values of password array are set according to the values stored in the
  eeprom memory. This way, when the system starts, password is equal to the 
  previous password save by the user, instead of getting the default values 
  when the system turn on. We start with a for loop that will perform the action
  while i < numberOfDigits. We save in password's array, the values saved in the 
  eeprom memory, in the positions i.
   */
  Serial.println("Setting eeprom values as password[] values.");
  for (int i = 0; i < numberOfDigits; i++) {
    password[i] = EEPROM.read(i);
  }
}
void printPasswordInEeprom(byte numberOfDigits) {
  /*This void is not needed for the system to work, but it is useful for the developer 
   to check which are the current values stored in the eeprom memory. We iterate over
  the for loop till i = numberOfDigits. We will print in the serial console, the values
  in the eeprom memory, saved in the address i.
   */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.println("i = " + String(i) + "; " + EEPROM.read(i));
  }
}
/*This method checks the EEPROM memory state. This is needed because when the program is loaded 
for the first time in the arduino board, the memory slots may have 255 as values, or any other 
random values. This method will burn the default password in the memory if any eeprom value is 
greater than 9, since each slot is a number of the password and they have to be a number between
0 and 9.*/
void checkEepromState(byte numberOfDigits) {
  /*
  We iterate over the eeprom values. If one this values is greater than 9, the method burnPasswordInEeprom
  will be called, and the for loop void will get broken. If the for loop reaches the last stage, the
  numberOfDigits - 1, it means that all the eeprom values are lower than 9, which means that they all
  are right values. In such case, readPasswordInEeprom is called to set the Eeprom values as the password[]
  values.
  */
  for (int i = 0; i < numberOfDigits; i++) {
    if (EEPROM.read(i) > 9) {
      Serial.println("A value over 9 has been detected in the memory position: " + String(i) + ".");
      burnPasswordInEeprom(numberOfDigits);
      break;
    } else if (i = numberOfDigits - 1) {
      readPasswordInEeprom(numberOfDigits);
    }
  }
}
/*This method will be called to get the keyboard typed by the user. It will be 
the ona called by burnPasswordInEeprom, to save the password.
*/
void newPassword(byte password[], byte numberOfDigits, int array1[], int array2[]) {
  /*When this void is loaded, we have already gone through a * key press event, with no 
   numbers typed. We broke the confirmation loop, and we came to the main conditional
   in the void loop. Once inside the main conditional, we had to enter the current 
   password, sicne it was requested by confirmation void; this one set match to true or 
   false. Acording to match's value, we will perform different actions in this void. 
   First we create a cancelled variable, and we set it to false. This variable will
   be the one that will allow, or not, the code to burn in memory, the actual value of 
   password[i]. If cancelled == false, it will mean that key * was not pressed and, as 
   soon as the process of entering the new password is over, "if (cancelled == false)"
   will perform its action.
   */
  Serial.println("Inside new password void");
  boolean cancelled = false;
  if (match) {
    /*Once the user entered the current password correctly, we get inside this conditional. 
     We will start by sending a message to serial monitor, for developing purposes. Then
     green LED will light for 250 milliseconds. Then, a newPasswordCounter variable is
     created, to deal with the amount of times that while loop will iterate, which will 
     also be the amount of new numbers introduced by the user for the new password. 
     After it, we directly jump to the main while loop.
     We will start by saving in mainMenuVariable, the value read in the * key pin; then
     "if mainMenuVariable" is equals to low, it means that the user wants to stop the 
     of new numbers for the password gathering, so:
     * We will set cancelled as true, so the system won't load the part of the code that
       burns in the eeprom the actual value of password[].
     * We set mainMenuVariable back to high, to restart the functionality of * key.
     * We set insideNewPasswordMenu variable back to false to avoid
       "if ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu))" 
       conditional, inside the method "confirmation", to be always true, since we could 
       never get inside newPassword again, (check confirmation void explanation to recall
       how * key conditionals work).
     * We call readPasswordInEeprom, because at this point, some of the values in 
       password[] might be already changed. So, since we are cancelling the new password
       chage process, we need to set password[] to its previous state. We achieve this 
       with this void, since at this point we still didn't burnt actual password[] values 
       in the Eeprom memory.
     * Finally, we break the while loop.
     If the key * was not pressed, the code will keep being executed, and mainKeyCaptation
     will be loaded. This void will record which key was pressed, and will set keyDetected
     as true. If it is true we will get inside "if (getKeyDetectedState())" and the code
     inside will be loaded:
     * We set keyDetected back to false, that way we will get inside this conditional again
       only if another key was pressed.
     * Orange LED will light for 1250 milliseconds. We set this much time in order to 
       force the user to press keys slowly. This is helpfull to avoid missclicks, which could 
       lead to burning in eeprom memory, undesired and unknown passwords. While the light is 
       on, the code won't keep running.
     * We save in the position newPasswordCounter in the array password[], the last key 
       pressed.
     * We do newPasswordCounter++ to jump to the next number of the password that must be 
       registered to be saved in password[].
     Finally, before leaving this conditional, if(match), we set match back to false.
     */
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
      /*Once the while loop is over, if "cancelled" is still false, we will get in this 
       conditional. We will send a message to serial monitor, for developing purposes.
       Then, green LED will light for 1 second to show that the proccess of introducing
       the new password succeded. Finally, we call burnPasswordInEeprom to burn the 
       actual values of password[] in the eeprom memory.
     */
      Serial.println("Burning EEPROM.");
      analogWrite(green, 255);
      delay(1000);
      analogWrite(green, 0);
      burnPasswordInEeprom(numberOfDigits);
    }
    match = false;
  } else {
    /*If "match" is false, it means that the user failed on entering the current 
     password, which means that the user has no access to the change password menu.
     Because of this, the conditional will not be executed, and we will jump directly 
     to this part of the code, were red LED will blink twice.
     */
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
    delay(100);
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
  }
  /*Finally, we set "match" back to false, in case user typed password correctly, 
   to be sure that there's no chance for openClose void to get a false trigger. 
   We set insideNewPasswordMenu back to false too. When we get inside the if 
   conditional, inside the void loop, we set insideNewPasswordMenu as true. By doing 
   this we locate ourselves in the code, if this variable is equals to true we know 
   we are inside new password menu, and newPassword void will be executed. The problem 
   comes when the program is executing the void loop normaly, and the user wants to 
   change the password. In this case the user presses the * button in order to to get 
   inside the conditional "if (mainMenuVariable == LOW) {", inside void loop. If 
   "insideNewPasswordMenu" is not equals to false once this void is over, next time 
   the user wants to get inside the new password menu, once * is triggered, the
   conditional "if ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu))"
   will be true, and therefor, the action on its inside will be perfomed. This means that
   "if (mainMenuVariable == LOW) {" will always be false. (check confirmation void 
   explanation to recall how * key conditionals work).
   */
  insideNewPasswordMenu = false;
  Serial.println("Leaving Password Menu.");
}
//Void used to print the actual password not burnt in the eeprom memory.
void getNewPassword() {
  /*This void is not needed for the system to be able to work. It is just for developing
    purposes. We load a for loop that will print password[i], till i = numberOfDigits.
   */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.print(password[i]);
  }
}
//Method used to show the system initialization.
void startingLights() {
  /*This void will be executed as soon as the system starts, in the void setup(),
   right before the void loop(). This void is used just as visual indicator for 
   the user. Red, orange and green LEDs will blink twice, with a delay of 100
   milliseconds.
   */
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
//Void to deal with the electromagnetic bolt triggering.
void openClose() {
  /*Everything is based in "match" variable. If "match" is equals to true we will write
   HIGH signal in the pin called as "bolt", which is pin A5, and the green LED will 
   light, both of them for 2 seconds. After it, we will write LOW signal in
   the pin "bolt", and we will turn of the green LED. This way we will trigger 
   the electromagnetic bolt for 2 seconds, allowing the user to use the key to open
   the door.
   If "match" is equal to false, then we won't get inside "if(match)", and "else" code 
   will be executed. The red LED will blink twice with a delay of 100 milliseconds.
   This will indicate the user that the password entered was wrong.
   Finally, we will set "match" as false again to take the system to its default mode.
   */
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
