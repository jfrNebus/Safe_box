//Este método establece el modo de comportamiento de los pines del teclado.
void pinSetUp(int array1[], int array2[]) {
  for (int i = 0; i < 4; i++) {
    /*Primero establecemos cada pin del primer array como output. Estos pines serán los
    encargados de enviar el pulso bajo que será leido por el segundo array.*/
    pinMode(array1[i], OUTPUT);
  }
  for (int j = 0; j < 3; j++) {
    /*Establecemos cada pin en el segundo array como INPUT_PULLUP, esto establece cada pin en 
    un estado HIGH. Estos pines serán los encargados de leer los valores enviados a traves de
    de los pines del primer array. Los pines en el segundo array tienen un valor HIGH, cuando
    establecemos uno de los pines como low en el primer array mientras iteramos sobre ellos y,
    a continuación, leemos los valores en el segundo array, el que tenga un valor LOW en lugar
    de HIGH, corresponderá con el botón presionado. Se recomienda leer "mainKeyCaptation" para
    entender el funcionamiento más claramente.

    Conexionado de las entradas de tipo INPUT_PULLUP:
    * Vcc = la conexión interna de vcc en el arduino..
    * ~~ = la resistencia interna del arduino conectada al pin de tipo INPUT_PULLUP.
    * | = el pin en el array2 establecido como INPUT_PULLUP.
    * || = el pin en el array1 establecido como output.
    * __ = la conexión interna entre elementos dentro del arduino.
    * _._._._ = la conexión externa de elementos.
    * // = el pulsador del teclado.

    Esquema completo del conexionado:

    VCC___~~___|_._._._//_._._._||___GND

    Cuando se presiona un pulsador en el teclado matricial, el pin establecido como INPUT_PULLUP, el
    cual está en estado HIGH, se connecta con un pin establecido como output, el cual está connectado a
    GND. En este escenario, se cierra el circuito y la lectura en el pin INPUT_PULLUP es LOW.
    */
    pinMode(array2[j], INPUT_PULLUP);
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
int getKeyPressedValue() {
  return result[keyColumn][keyRow];
}
/*Método para comprobar si la contraseña introducida coincide con la contraseña almacenada en la
memoria Eeprom.
*/
void confirmation(byte password[], byte numberOfDigits, int array1[], int array2[]) {
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
      insideNewpasswordMenu son falsos, aun no se presionó ningún número, y no nos encontramos
      dentro del menú de nueva contraseña. Por lo tanto, si se presiona
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
    - Alimentamos el pin del transistor del led naranja durante 300 milisegundos. Esto le 
      muestra al usario que se presionó una tecla.
    - Usamos newPasswordCounter para establecer la posición dentro del array inputPassword[],
      donde almacenaremos los valores reportados por getKetPressedValue(). De esta forma, si
      presionamos el botón 4, como tercera posición de nuestra contraseña, se guardará el 
      número 4 en la tercera posición del array inputPassword[].
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
  /*Por último, si el valor de canceled sigue siendo false tras haber dejado 
  el bucle loop, entraremos dentro del siguiente condicional. Este condicional 
  evaluará si todos los elementos dentro de inputPassword[i], son iguales a 
  todos los valores dentro de password[i]. Cada vez que ambos valores en la
  misma posición son iguales, la variable "match" se establecerá como true. Si 
  al finalizar el bucle for, "match" sigue siendo igual a true, se ejecutará
  cualquier acción que dependa del condicional "if(match)". Tan pronto como 
  un valor en inputPassword no coincida con un valor de password[], no se
  accederá al condicional if, y se ejecutará la acción del bloque else. En
  este caso, se establecerá match como false. Se detendrá el bucle for, 
  impidiendo el acceso a la acción de "if(match)", y volviendo al void loop.
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
//Método para grabar en la memoria eeprom la nueva contraseña.
void burnPasswordInEeprom(byte numberOfDigits) {
  /*El bucle for realizará la acción mientras i sea igual a
  numberOfDigits. Se escribirá en la memoria eeprom, cada número de
  la contraseña actual. Para ello, le indicamos al sistema que queremos
  salvar en la dirección de la memoria i el número en la posición i 
  del array "password".
  */
  Serial.println("Burning in eeprom the values of password[]");
  for (int i = 0; i < numberOfDigits; i++) {
    EEPROM.write(i, password[i]);
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
  en las posiciones i.
  */
  Serial.println("Setting eeprom values as password[] values.");
  for (int i = 0; i < numberOfDigits; i++) {
    password[i] = EEPROM.read(i);
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
  direcciones i.
  */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.println("i = " + String(i) + "; " + EEPROM.read(i));
  }
}
/*Este método comprueba el estado de la memoria EEPROM. Se necesita comprobar el estado de la
la memoria porque cuando se carga el programa en arduino por primera vez, las bloques de memoria
pueden contener su valor por defecto, el cual es 255, o algún otro valor. Este método grabará en
la memoria, la contraseña por defecto si alguno de sus valores es mayor de 9. Dado que cada
bloque en la memoria corresponde con un dígito de la contraseña, estos han de estar en el rango de
0 and 9.*/
void checkEepromState(byte numberOfDigits) {
  /*
  Se itera sobre los valores presentes en la eeprom. Si alguno de estos valores es mayor que 9, se
  llamará al método burnPasswordInEeprom y se detendrá el bucle for. Si el bucle for llega a su última
  iteración, numberOfDigits - 1, quiere decir que todos los valores en la memoria son menor que 9, lo 
  que implica que todos valores son válidos. En este caso, se llama al método readPasswordInEeprom 
  para grabar en la memoria los valores de password[].
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
/*Este método se usará para obtener la contraseña ingresada por el usuario.
Será el método que burnPasswordInEeprom llamará para guardar la contraseña.
*/
void newPassword(byte password[], byte numberOfDigits, int array1[], int array2[]) {
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
    * Por último, detenemos la iteración del bucle while.
    Si el botón * no fue presionado, el código se seguirá ejecutando, y se llamará a 
    mainKeyCaptation. Este método captará qué tecla fue presionada, y establecerá keyDetected
    como true. Si keyDetected es true, entraremos dentro del condicional "if (getKeyDetectedState())"
    y se ejecutará el código en su interior.
    * Se establece keyDetected como false, de esta forma accederemos de nuevo a este condicional
      si se vuelve a presionar un  nuevo botón.
    * El LED naranja se encenderá durante 1250 milisegundos. Se establece esta cantidad de tiempo, 
      para forzar al usario a presionar los botones de forma pausada. Esto ayudará a evitar que se 
      presionen botones por error, lo cual podría ocasionar que se grabase en la memoria eeprom
      números desconocidos o no deseados. Mientras el LED está encendido, el código no seguirá
      ejecutandose.
    * Se guarda en la posición newPasswordCounter, en el array password[], el último botón 
      presionado.
    * Incrementamos en una unidad el valor de newPasswordCounter, para saltar al siguiente registro
      de nnúmero que tiene que ser guardado en password[].
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
      /*Una vez que el bucle while ha finalizado, si "cancelled" sigue siendo false,
      accederemos a este condicional. Se enviará un mensaje al monitor serial, únicamente 
      con motivo de desarrollo. Se enciende el LED verde durante un segundo, para indicar
      que el proceso de introducir una nueva contraseña ha finalizado correctamente.
      Finalmente, llamamos al método burnPasswordInEeprom para grabar los valores actuales
      de password[] en la memoria eeprom.
      */
      Serial.println("Burning EEPROM.");
      analogWrite(green, 255);
      delay(1000);
      analogWrite(green, 0);
      burnPasswordInEeprom(numberOfDigits);
    }
    match = false;
  } else {
    /*Si "match" es igual a false, quiere decir que el usuario no ingresó la 
    contraseña de forma correcta, lo que quiere decir que el usuario no tiene acceso
    al menú de cambio de contraseña. Debido a esto, el condicional if no será ejecutado, 
    y se saltará directamente a esta parte del código, donde el led rojo parpadeará dos 
    veces.
    */
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
    delay(100);
    analogWrite(red, 255);
    delay(100);
    analogWrite(red, 0);
  }
  /*Por último, establecemos "match" como false. Se establece insideNewPasswordMenu 
  como false. Cuando entramos en el condicional if del bloque void loop, establecemos
  insideNewPasswordMenu como true. Al hacer esto nos situamos dentro del código, si
  esta variable es igual a true, sabemos que nos encontramos dentro del menu new password, 
  y que se llamará al método newPassword.
  El problema aparece cuando el programa se está ejecutando de forma normal, y el 
  usuario necesita cambiar la contraseña. En este caso, el usuario presiona el botón
  * con la intención de entrar en el condicional "if (mainMenuVariable == LOW) {", 
  dentro del void loop. Si el valor de la variable "insideNewPasswordMenu" no es igual
  a false una vez este método ha concluido, la siguiente vez que el usuario quiera 
  entrar en el menú de nueva contraseña, cuando se presione el botón *, el condicional
  "if ((mainMenuVariable == LOW) && (numberTyped || insideNewPasswordMenu))" será igual
  a true, y por lo tanto, se ejecutará las acciones asociadas al mismo. Esto quiere decir
  que "if (mainMenuVariable == LOW) {" será siempre falso. (Se aconseja revisar el método
  "confirmation" para recordar como funciona el condicional del botón *).
  */

  insideNewPasswordMenu = false;
  Serial.println("Leaving Password Menu.");
}
//Método usado para imprimir la contraseña actual no guardada en la memoria eeprom.
void getNewPassword() {
  /*Este método no es necesario para el funcionamiento del sistema. Sirve únicamente para
    propositos de desarrollo. Implementamos un bucle for que imprimirá "password[i]", hasta
    que i sea igual a numberOfDigits. Entonces el código esperará 2 segundos.
   */
  for (int i = 0; i < numberOfDigits; i++) {
    Serial.print(password[i]);
  }
}
//Método usado para indicar el inicio del sistema.
void startingLights() {
  /*Este método será ejecutado tan pronto como se inicialice el sistema, en  el void setup(),
  justo antes del void loop(). Este método se usa como indicador visual para el usuario. Los
  LEDs rojo, naranja y verde, parpadearán dos veces, con un delay de 100 milisegundos.
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
//Método para gestionar la activación del perno electromagnético.
void openClose() {
  /*Todo está basado en la variable "match". Si la variable "match" es igual a true
  enviaremos una señal HIGH por el pin llamado "bolt", el pin A5, y el led verde
  se encenderá, ambos durante 2 segundos. Después, enviaremos una señal LOW por ambos
  pines. De esta forma, activaremos el perno electromagnético por 2 segundos, permitiendo 
  al usuario usar la llave para abrir la puerta. Por último, reestablecemos el valor de 
  match como false para llevar al sistema a su modo default.
  Si "match" es igual a false, entonces no accederemos al condiconal "if(match), y 
  se ejecutará el código del bloque else. El LED rojo parpadeara dos veces con un 
  delay de 100 milisegundos. Esto le indicará al usuario que la contraseña
  introducida es erronea.
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
