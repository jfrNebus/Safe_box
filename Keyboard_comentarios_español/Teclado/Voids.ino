//Este método establece el modo de comportamiento de los pines del teclado.
void pinSetUp (int array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    /*Primero establecemos cada pin del primer array como output. Estos pines serán los
    encargados de enviar el pulso bajo, que será leido por el segundo array.*/
    pinMode(array1[i], OUTPUT);
  }
  for (int j = 0; j < 3; j++) {
    /*Establecemos el segundo array como input, y les asignamos un valor HIGH. Estos pines
    serán los que lean los valores de los pines en el primer array. Se establecen como HIGH,
    cuando establecesmos los del primer array como LOW mientras iteramos sobre ellos y, 
    después, leemos los valores del segundo array, aquellos que muestren un valor LOW en
    lugar de HIGH, serán los que hayan sido presionados. Se aconseja leer el método
    mainKeyCaptation para entender mejor el concepto.
    */ 
    pinMode(array2[j], INPUT);
    digitalWrite(array2[j], HIGH);
  }
}
//Este método establece el modo de comportamiento de los pines del teclado. Commit test
void mainKeyCaptation(int array1[], int array2[]) {
  /*Cambiamos el valor de cada elemento del primer array, de HIGH a LOW, secuencialmente, para 
  evaluar si el valor LOW se lee en alguno de los elementos de array2.
  */
  int variable;
  for (int i = 0; i < 4; i++) {
    digitalWrite(array1[i], LOW);
    /*We store in "variable" the reading of each member in second array, for each member
    of first array.*/
    for (int j = 0; j < 3; j++) {
      variable = digitalRead(array2[j]);
      /*Si "variable" es igual a LOW, quiere decir que se presionó la tecla que conecta ambos
      pines, representados como un miembro de cada array. Un pulso bajo de un pin en el array
      2, es enviado a un pin del array 2. Si esto ocurre, guardamos el número de iteración de
      cada bucle for, cada número será la posición de un elemento en cada array, los pines 
      involucrados, y se establece como true el booleano keyDetected, que nos indica que una 
      tecla fue presionada.
      */
      if (variable == LOW) {
        keyColumn = i;
        keyRow = j;
        keyDetected = true;
        break;
      }
    }
    /*Una vez la iteración actual de array1 se finaliza, se establece el pin actual de nuevo 
    con valor HIGH, dado que es el estado por defecto.
    */
    digitalWrite(array1[i], HIGH);
  }
}
//El método getter de la variable keyDetected.
boolean getKeyDetectedState() {
  return keyDetected;
}
/*Método getter para devolver el valor de la tecla almacenada en el array result, para el valor
actual de keyColumn y keyRow.
*/
int getKeyPressedValue () {
  return result[keyColumn][keyRow];
}
/*Método para comprobar si la contraseña introducida coincide con la contraseña almacenada en la
memoria Eeprom.
*/
void confirmation (byte password[], byte numberOfDigits, int array1[], int array2[]) {
  /*El método empieza encendiendo y apagando el led dos veces para indicar que el código se 
  encuentra actualmente dentro del método confirmation. A continuación, se crean una serie
  de elementos.
  -newPasswordCounter almacenará el número de iteraciones efecturado sobre el bucle principal.
  -inputPassword[numberOfDigits] almacenará el valor numérico de los botones presionados. El tamaño
  del array es numberOfDigits, establecido al inicio del código.
  -numberTyped sirve para poder establecer diferentes estados para que el botón * tenga diferentes
  funciónes.
  -Cancelled será usado como condición para comprobar si la contraseña en la memoria eeprom y la 
  contraseña introducide coinciden. Si el valor de esta variable es false, ambas contraseñas serán
  comparadas; si el valor es true, quiere decir que el botón *, el que se usa para cancelar la
  operación, fue presionado.
  A continuación, entramos en el bucle while principal, que iterará mientras 
  newPasswordCounter is menor que numberOfDigits.
  */
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
    /* Primero almacenamos en mainMenuVariable, el valor de la lectura del 
    pin9 y, dependiendo de su valor, establecemos algunos bloques condicionales.
    - Si mainMenuVariable es igual a low y, al mismo tiempo, alguna de las variables
    numberTyped o insideNewPasswordMenu, son true, entonces se modificará el valor
    de algunas variable con la intención de volver al menú principal, cancelando
    todas las operaciones realizadas, evitando acceder al menú de cambio de 
    contraseña.
      * Se establece el valor de cancelled como true. De esta forma no se accederá
      al último condicional, el cual comprueba si la contraseña introducida coincide
      con la contraseña almacenada en password[]. No es necesario comprobar si coinciden
      porque el botón * se usa para cancelar la acción / la petición de cambio de 
      contraseña.
      * Se establece mainMenuVariable como HIGH de nuevo, para evitar entrar en el menú
      de cambio de contraseña, debido a que depende del condicional if (mainMenuVariable 
      = low).
      * We set insideNewPasswordMenu as false. This variable is set to true when 
        we get in the new password menu, in order to be able to set an scenario where
        the code can know when we are inside new password menu or not. If we are 
        inside new password menú, this variable will be true, so if we press * button
        it means that we want to go back to main menu.
     Finally, we break the main while loop of this void, leaving directly the whole void, and 
     starting again the main loop of the code.
    - If previous conditional is not met, then it means that numberTyped and 
      insideNewPasswordMenu are false, so we still didn't press any number, and we are
      not inside new password menu, so if * key is pressed, it means that we request 
      the code to take us to new password Menu. In this situation we don't change back
      mainMenuVariable's value, we set cancelled as true to avoid getting into the last 
      conditional which checks if the typed password matchs the password 
      stored inside password[], and we break the main while loop of this void. This way,
      mainMenuVariable's value is still LOW once the main loop checks if the new password 
      menu conditional is true or not, and, since this conditional is 
      if (mainMenuVariable == LOW), we will get inside of it.
    If none of these two conditionals is met, then we will call mainKeyCaptation(array1, 
    array2);, which was explained previously, which will set keyDetected as true if a key
    was pressed. After it we will get its vaule and if it is true, we will get inside
    next conditional. Once we are inside next conditional we will perform some actions:
    - We set numberTyped as true so, from now, if we press * key, code will understand that
      we pressed a key and we need to cancel any action performed, so it will take us to 
      main code loop according to the first conditional explained previously.
    - We set keyDetected back to false, this way we won´t get inside this conditional until
      we press another key.
    - We change orang pin to output for 300 milliseconds, and we change it back to input, to 
      light up orange LED for that time showing to the user that a key was pressed.
    - We use newPasswordCounter as the position inside inputPassword[] array, where we will 
      store the value returned by getKeyPressedValue() void. This way, if we pressed the key 
      number 4 as the third number in our password, we will store in the inputPassword[] array
      in the third position the number 4.
    - Finally we newPasswordCounter++ to be able to record the number in the next position of
      the password.
    */
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
  /*Finally, if cancelled is still low once we left the while loop, we will get
    inside the conditional. This conditional will check if all values inside
    inputPassword[i] are equals to all values inside the password[i], which is 
    burnt in EEPROM's memory. Each time both values in same position are equal, 
    match variable will be set as true, and if this for loop ends and match is
    equals to true, we will be able to perform the action that depends on if(match).
    As soon as inputPassword doesn't match a value in password, we won't get inside 
    if conditional, and we will perform what's inside else, which is setting match 
    as false, and breaking the for loop, denying the access to whatever action 
    that depends on a if(match) conditional, and leaving back to main code loop.
   */
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
  /*For loop that will perform the action till i = numberOfDigits. We
  will write in the eeprom memoty, each number of the current password. 
  For that, we will tell the system that we want to save the i number in
  password's array, in the i address of the eeprom bassed in the i 
  number of the passwordEepromAddress array.
   */
  for (int i = 0; i < numberOfDigits; i++) {
    EEPROM.write(passwordEepromAddress[i], password[i]);
  }
}
void readPasswordInEeprom(byte numberOfDigits) {
  /*With this void we set the values of password array as the values of
   of the password stored in the Eeprom. This way, when the system starts,
   password is equal to the previous password save by the user, instead of
   getting the default values when the system turn on. We start with a for
   loop that will perform the action till i = numberOfDigits. We save in 
   password's array, the values saved in the eeprom memory, in the positions
   i, where i are the numbers inside passwordEepromAddress.
   */
  for (int i = 0; i < numberOfDigits; i++) {
    password[i] = EEPROM.read(passwordEepromAddress[i]);
  }
}
void printPasswordInEeprom(byte numberOfDigits) {
  /*This void is not needed for the system to be able to work, but it is useful
   for the developer to check what are the current values stored in the eeprom
   memory. We iterate in a for loop till i = numberOfDigits. We will print in 
   the serial window, the values in the eeprom memory, saved in the address 
   passwordEepromAddress[i].
   */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.println(EEPROM.read(passwordEepromAddress[i]));
  }
}

void newPassword (byte password[], byte numberOfDigits, int array1[], int array2[]) {
  /*This void will be the one who will get the new password entered by the user, 
   and the one who will call the burnPasswordInEeprom void to save it in eeprom memory
   When this void is loaded, we have already gone through a * key press with no 
   numbers typed, so we broke the confirmation loop, and we came to main if in the 
   loop of main code. Inside of it, we had to type a password that was requested by
   confirmation void, and this one set match to true or false. Acording to match's 
   value, we will perform different actions in this void. 
   First we create a cancelled variable, and we set it to false. This variable will be
   the one that will allow the code, or not, to burn in memory the actual value of 
   password[i]. if cancelled == false, it will mean that key * was not pressed and, as
   soon as the process of typing new password is over, if (cancelled == false) will
   perform its action.
   */
  Serial.println("Inside new password void");
  boolean cancelled = false;
  if (match) {
    /*Once the user typed the current password correctly, we get inside this conditional. 
     We will start by sending a message to serial monitor, for developing purposes. Then
     green light will light up for 250 milliseconds and will turn off after it. Then we 
     make a new newPasswordCounter variable that will deal with the amount of times that
     while loop will iterate, which will also be the amount of new numbers introduced by
     the user for the new password. After it, we directly jump to the main while loop.
     We will start by saving in mainMenuVariable the value read in the * key pin; then
     if mainMenuVariable is equals to low, it means that the user wants to stop the 
     process of recording new numbers for the password, so:
     - We will set cancelled as true, so the system won't load the part of the code that
       burns in the eeprom the actual value of password[].
     - We set mainMenuVariable back to high, to restart the functionality of * key.
     - We set insideNewPasswordMenu variable back to false to avoid
       "if ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu))" 
       conditional inside confirmation to be always true, since we could never get 
       inside newPassword again, (check confirmation void explanation to recall how
       * key conditionals work).
     - We load readPasswordInEeprom, because at this point, some of the values in 
       password[] might be already changed, so, since we are cancelling the new password
       chage process, we need to set password[] to its previous state. We achieve this 
       with this void since at this point we still didn't burnt actual password[] values 
       in the Eeprom memory.
     - Finally, we break the while loop and the if.
     If the key * was not pressed, the code will keep being executed, and mainKeyCaptation
     will be loaded. This void will record which key was pressed, and will set keyDetected
     as true. If it is true we will get inside "if (getKeyDetectedState())" and the code
     inside will be loaded:
     - We set keyDetected back to false, that way we will get inside this conditional again
       only if another key was pressed.
     - Orange light will light up for 1250 milliseconds. We set this much time in order to 
       force the user to press keys slowly, this is helpfull to avoid missclicks which could 
       lead to burning in eeprom memory undesired and unknown passwords. While the light is 
       on, the code won't key new keys pressed.
     - We save in the position newPasswordCounte in the array password[], the last key 
       pressed.
     - We do newPasswordCounter++ to jump to the next number of the password that must be 
       registered to be saved in password[].
     */
    Serial.println("New Password Menu.");
    pinMode(green, OUTPUT);
    delay(250);
    pinMode(green, INPUT);
    int newPasswordCounter = 0;
    while (newPasswordCounter < numberOfDigits) {
      mainMenuVariable = digitalRead(pin9);
      if (mainMenuVariable == LOW) { 
        cancelled = true;
        mainMenuVariable = HIGH; //Check if this line is needed considering that it is sent in main if conditional in void loop
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
      /*Once the while loop is over, if cancelled is still false, we will get in this 
       conditional. We will send a message to serial monitor, for developing purposes.
       Then, green LED will light up for 1 second to show that the proccess of introducing
       the new password succeded. Then we will set newPasswordCounter back to 0. This is 
       100% not needed since it is a local variable that won't be used again, so this 
       line has no meaning and this void could end and newPasswordCounter would be 
       automatically deleted, but i will leave it here till i can test the code behaviour
       just in case i am missing something.
       Finally, we load burnPasswordInEeprom to burn the actual values of password[] in
       the eeprom memory.
     */
      Serial.println("Burning EEPROM.");
      pinMode(green, OUTPUT);
      delay(1000);
      pinMode(green, INPUT);
      newPasswordCounter = 0;
      burnPasswordInEeprom(numberOfDigits);
    }
  }
  else {
    /*If match is false, it will mean that the user failed on typiing the current 
     password, which means that the user has no access to the change password menu.
     Because of this, if conditional will not be executed, and we will jump directly 
     to this part of the code, were red LED will blink twice.
     */
    pinMode(red, OUTPUT);
    delay(100);
    pinMode(red, INPUT);
    delay(100);
    pinMode(red, OUTPUT);
    delay(100);
    pinMode(red, INPUT);
    delay(100);
  }
  /*Finally, we set match back to false, incase user typed password correctly, 
   to be sure that there's no chance for openClose void to get a false trigger. 
   When we get inside main if conditional, in the main loop of the system, 
   we set insideNewPasswordMenu as true. By doing this we locate ourselves in the
   code, if this variable is equals to true we know we are inside new password 
   menu and newPassword void will be executed; but if we press the key * while
   confirmation is being executed, "if (insideNewPasswordMenu)" will not even start.
   This variable is set as false again at this point, or while the user is introducing
   the new password, because if we don't set this variable back to false 
   "if ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu))" 
   conditional inside confirmation would always be true, so we could never get 
   inside newPassword again, (check confirmation void explanation to recall how
   * key conditionals work).
  
   */
  match = false;
  insideNewPasswordMenu = false;
  Serial.println("Leaving Password Menu.");
}
void getNewPassword() {
    /*This void is not needed for the system to be able to work, but it is useful
   for the developer to check the current values of password[], the actual not in
   eeprom memory password. We load a for loop that will print password[i], till i
   = numberOfDigits. Then the code will wait for 2 seconds.
   */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.print(password[i]);
  }
  delay(2000);
}
void startingLights() {
  /*This code will be executed as soon as the system starts, in the void setup(),
   right before the void loop(). This void is used just as visual indicator for 
   the user. Red, orange and green lights will blink twice, with a delay of 100
   milliseconds.
   */
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
  /*This is the part of the code that deals with opening and closing the door of 
   the safe box. Everything is based in match variable. If match is equals to true
   we will write high signal in the pin called as magnet1, which is pin A1 and
   a green light will light up for 2 seconds. After it, we will write low signal in
   the pin magnet1, and we will turn of the green light. This way we will trigger 
   the electromagnetic bolt for 2 seconds, allowing the user to use the key to open
   the door.
   If match is equal to false, then we won't get inside if(match), and else code will
   be executed, which is blinking red light twice with a delay of 100 milliseconds.
   This will indicate the user that the password typed to open the door was wrong.
   Finally, we will set match as false again to respect match's functionality.
   */
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
