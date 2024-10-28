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
      * Establecemos insideNewPasswordMenu como false. Esta variable se establece
        como true cuando entramos en el menú new password. Si se presiona el botón *
        mientras estamos dentro del menú new password, quiere decir que queremos volver
        al menú principal, y por lo tanto no entramos dentro del condicional "if 
        (insideNewPasswordMenu)" que viene a continuación del método confirmation.
     Por último, rompemos el bucle while principal de este método, abandonando directamente
     todo el método, empezando de nuevo el bucle main del código.
    - Si la condición anterior no se cumple, quiere decir que numberTyped e
      insideNewpasswordMenu son falsos, y por lo tanto aun no se presionó ningún número, 
      y no nos encontramos dentro del menú de nueva contraseña. Por lo tanto, si se presiona
      el botón *, quiere decir que estamos solicitando acceder al menú de nueva contraseña.
      En esta situación, mainMenuVariable mantiene su nuevo valor LOW; se establece cancelled
      como true, para evitar acceder al último condicional que evalúa si la contraseña 
      introducida condicide con la contraseña presente en password[], y se rompe el bucle
      while de este método. De esta forma, el valor de mainMenuVariable se mantiene como LOW
      cuando el bucle principal del programa evalúa si la condición para acceder al menú
      de nueva contraseña es true o false. Dado que esta condición es "if(mainMenuVariable 
      == LOW)", acederemos al interior del mismo.
    Si no se cumple ninguna de estas dos condiciones, entonces llamamos al método 
    "mainKeyCaptation(array1, array2);", que ya fue explicado previamente. Este método
    establecerá keyDetected como true, si se presionó alguna tecla. En este caso, accedemos
    al siguiente condicional, donde se realizarán una serie de acciones. 
    - Se establece numberTyped como true. Desde ahora, si presionamos el botón *, el código
      entenderá que presionamos un botón y que necesitamos cancelar cualquier acción. En
      este caso concreto, nos devolvería al loop principal del codigo, de acuerdo con lo
      explicado en el primer condicional de este método.
    - Establecemos keyDetected de nuevo como false, de esta forma no volveremos a entrar en 
      este condicional de nuevo, hasta que no se vuelva a presionar una tecla.
    - Establecemos el pin del led naranja como salida durante 300 milisegundos y, a continuación,
      volvemos a establecerlo como input. Esto encenderá el LED durante el tiempo el tiempo 
      indicado, mostrandole al usario que se presionó una tecla.
    - Usamos newPasswordCounter para establecer la posición dentro del array inputPassword[],
      donde almacenaremos los valores reportados por getKetPressedValue(). De esta forma, si
      presionamos el botón 4, como tercera posición de nuestra contraseña, se guardará el 
      número 4 en la tercera posición del array. inputPassword[].
    - Por último, incrementamos en una unidad el valor de newPasswordCounter, para obtener
      la posición de la siguiente tecla presionada. Recordemos que esta variable también nos
      sirve para controlar cuando ha de detenerse el bucle while de este método.
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
//Método para grabar en la memoria eeprom la nueva contraseña.
void burnPasswordInEeprom(byte numberOfDigits) {
  /*El bucle for realizará la acción mientras i sea igual a
  numberOfDigits. Se escribirá en la memoria eeprom, cada número de
  la contraseña actual. Para ello, le indicamos al sistema que queremos
  salvar en la dirección de la memoria i, del array passwordEepromAddress,
  el número en la posición i del array "password".

  POR MODIFICAR-----: Comprueba si se puede sustituir el sistema de direción
  passwordEepromAddres, simplemente por el valor de i, guardando en las 
  direcciones 0 <> numberOfDigits - 1.
  */
  for (int i = 0; i < numberOfDigits; i++) {
    EEPROM.write(passwordEepromAddress[i], password[i]);
  }
}
/*Método para establecer los valores del array password cada vez que
se alimenta la placa.
*/
void readPasswordInEeprom(byte numberOfDigits) {
  /*Se establecen los valores del array password, en función de los valores
  almacenados en la memoria. De esta forma, cuando el sistema se inicia, la 
  contraseña password[] es igual a la contraseña guardada anteriormente por 
  el usuario, en lugar de tomar los valores por defecto.
  Se empieza con un bucle for que realiza su acción mientras i = numberOfDigits.
  Salvamos en el array password, los valores guardados en la memoria eeprom, 
  en las posiciones i, donde i son los números almacenados en el array 
  passwordEepromAddress.

  POR MODIFICAR-----: Comprueba si se puede sustituir el sistema de direción
  passwordEepromAddres, simplemente por el valor de i, guardando en las 
  direcciones 0 <> numberOfDigits - 1.
  */
  for (int i = 0; i < numberOfDigits; i++) {
    password[i] = EEPROM.read(passwordEepromAddress[i]);
  }
}
//Método para imprimir en la consola los valores almacenados en la memoria
//eeprom.
void printPasswordInEeprom(byte numberOfDigits) {
  /* Este método no es necesario para que el sistema funcione, pero es útil 
  para el desarrollador para comprobar los valores actuales guardados en la
  memoria.
  Se itera sobre el bucle for mientras i = numberOfDigit. Se imprime en la
  consola serial, los valores de la memoria eeprom, guardados en las 
  direcciones del array passwordEepromAddres[i].
  */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.println(EEPROM.read(passwordEepromAddress[i]));
  }
}
/*Este método se usará para obtener la contraseña ingresada por el usuario.
Será el método que burnPasswordInEeprom llamará para guardar la contraseña.
*/
void newPassword (byte password[], byte numberOfDigits, int array1[], int array2[]) {
  /*Se llama a este método cuando ya se ha pasado por un evento de presionar el
  botón *, sin que se hubiese presionado ningún número previamente. Se rompió el loop
  "confirmation", y se entró en el condicional if principal. Una vez dentro del
  condicional principal, tuvimos que introducir la contraseña actual, dado que fué 
  solicitada por el método confirmation; confirmation establece el valor de match como
  true o false. De cacuerdo al valor de match, se realizarán diferentes acciones en
  este método.
  Primero, se crea la variable "cancelled", y se establece como false. Esta variable
  será la que le permita, o no, al código, a grabar en la memoria, el valor actual de
  password[i]. Si cancelled == false, esto querrá decir que el botón * no fue presionado
  y, tan pronto como el proceso de introducir la nueva contraseña se haya terminado, el
  bloque "if (cancelled == false)" ejecutará su acción.
  */
  Serial.println("Inside new password void");
  boolean cancelled = false;
  if (match) {
    /*Se accede al interior de este condicional, una vez que el usuario introdujo su 
    contraseña actual de forma correcta.
    Se empieza enviando un mensaje al monitor serial, únicamente con motivo de desarrollo.
    A continuación, se enciende el led verde durante 250 milisegundos. Se crea una nueva
    variable llamada newPasswordCounter, para gestional el número de veces que iterará el
    bucle while, y para mantener la cuenta de la cantidad de nuevos números introducidos por 
    el usuario. Después de esto, saltamos al bucle while principal del método.
    Empezamos guardando en mainMenuVariable, el valor de la lectura en el pin del botón *;
    si "if mainMenuVariable" es igual a low, quiere decir que el usuario quiere detener el
    proceso de recogida de números para la nueva contraseña, por lo tanto:
    * Se establece cancelled como true, de esta forma en systema no llamará al método encaegado
    de grabar en la memoria eeprom el valor actual de password[].
    * Se establece mainMenuVaribale como HIGH, para reestablecer la funcionalidad de del botón *.
    * Se establece insideNewPasswordMenu de nuevo como false. Esto evita que el condicional "if 
    ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu))", dentro del método
    "confirmation" reporte un valor true siempre, puesto que de esta forma nunca podríamos 
    entrar en el método newPassword de nuevo. (Se aconseja revisar la información del método
    "confirmation" para recordar cómo funciona el condicional del botón *).
    * Se llama al método readPasswordInEeprom porque, en este punto, algunos de los valores en
    password[] podrían haber sido cambiados. Por lo que, dado que estamos cancelando el proceso
    de cambio de contraseña, necesitamos establecer password[] con los valores que tenía en su
    estado anterior. Esto se logra con este método puesto que, en este punto, aun no se han
    grabado los valores actuales de password[] en la memoria eeprom.
    
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
