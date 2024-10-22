#include <EEPROM.h>

//----------- Matriz de pulsadores.
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 7;
int pin8 = 8;
//----------- Pulsador fuera de la matriz, botón *
int pin4 = 10;
int pin9 = 9;
//----------- Perno electromagnético
int magnet1 = A1;
//----------- Leds
int positive = 11;
int green = A5;
int orange = A4;
int red = A3;
/* Los led se encenderán si establecemos pinMode(red, OUTPUT);, debido a que los led son positivo común, 
cuando establecemos su lado negativo como output, dado que output establece su valor a LOW, conectado a 
ground, se cierra el circuito.
*/
int keyColumn; //Establece el valor de la primera dimensión del array bidimensional.
int keyRow; //Establece el valor de la segunda dimensión del array bidimensional.
boolean keyDetected = false; //Boleano que se usará para conocer si se ha presionado alguna tecla.
boolean insideNewPasswordMenu = false; /*Este booleano nos permitirá conocer en que parte del código
se encuentra el proceso de ejecución. Sirve a su vez, para darle más de un uso al botón *. Esto se 
debe a que el botón * se comportará de formas diferentes en función de si esta variable es true o false.
*/
byte password[] = {1, 1, 1, 2, 2, 2}; /*La contraseña por defecto cuando se carga el programa en la placa, 
y el array que será sobrescrito cuando guardemos una nueva password en la memoria Eeprom.
*/
byte passwordEepromAddress[] = {1, 2, 3, 4, 5, 6}; /*Los números de posición en la memoria Eeprom, donde
se guardará cada número de la contraseña. Esto quiere decir que guardaremos un grupo de 6 números, y cada 
uno de esos números se guardará en un "slot", en una dirección de la la memoria Eeprom. Los números en 
este array son las direcciones de estos slots. El primer número de la contraseña se guardará en la dirección
que aparezca en la primera posición del array passwordEepromAddress, la dirección 1; el segundo número de 
la contraseña se guardará en la posición 2; y así consecutivamente.

POR COMPROBAR-----: Elimina este array y en su lugar usa la propia variable del bucle for como dirección en la 
memoria eeprom. De esta forma, la primera posición sería la 0 y la última la 5.
*/
byte newPasswordCounter = 0; //-TOCHECK TOCHECK TOCHECK TOCHECK TOCHECK TOCHECK TOCHECK TOCHECK TOCHECK ESTA LÍNEA FALTA POR DOCUMENTAR

byte numberOfDigits = 6; /*Numero de dígitos de nuestra contraseña. Esta variable establece el número de 
iteraciones para cada loop for. Estos bucles se utilizan a la hora de leer, imprimir o grabar la contraseña
en desde/en la memoria Eeprom.
*/
const byte C = 4;//Número de columnas.
const byte R = 3;//Número de filas.
bool match = false; /*Booleano que permitirá controlar diferentes condicionales en función de si la contraseña
es introducida es correcta
o no.
*/
//Columns y rows almacenan los pines asociados a las columnas y a las filas, de acuerdo al esquema eléctrico.
int columns[C] = {pin5, pin6, pin7, pin8};
int rows[R] = {pin1, pin2, pin3};
int result[C][R]; /* Usaremos el número de columnas y de filas como dimensiones del array bidimensional "result". 
Más tarde le daremos un valor a cada una de las combinaciones. Serán estos valores los que representen cada tecla
del teclado. Explicación breve: si el pin 5 del array columns, se conecta con el pin 2 de filas, obtendremos el
valor "2", que corresponde con la tecla 2 del teclado.
*/
int mainMenuVariable = HIGH; /*En esta variable se guardara la lectura del botón *. El valor por defecto es HIGH.
El botón * tiene varias funciones. Nos ayuda a abandonar el menú de password sin guardar ningún cambio, o a cancelar
la introducción de una secuencia de codigo en caso de que nos hayamos equivocado, o por cualquier razón. Se llega
a estas condiciones cuando mainMenuVariable == LOW.
*/
void setup() {
  /*Leds
  Empezamos estableciendo el pin "positive" como pin de salida. Establecemos un valor valor bajo de alimentación.
  por medio de analogWrite.

  POR COMPROBAR-----: Analiza por qué lanzas analogWrite.
  */
  pinMode(positive, OUTPUT);
  analogWrite(positive, 20);
  /* El botón *, el que no forma parte de la matriz de botones. Establecemos uno de los pines como output low, y
  el otro como input high. La idea es que a través del pin 4 enviamos un pulso con valor LOW, y se lee en el pin 9,
  el cual es high. Se establece el condicional en función del pin 9, si pin9 == low, dado que era high originalmente
  entonces haz X acción.
  */

  //VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ VAS POR AQUÍ 
  
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, LOW);
  pinMode(pin9, INPUT);
  digitalWrite(pin9, HIGH);
  //Magnet this is the pin that will trigger the gate of the mosfet transistor.
  pinMode(magnet1, OUTPUT);
  //We start the serial monitor to print some in proces messages.
  Serial.begin(9600);
  /*Now we set the values for each pin combination. According to the schematic, the conexion between
  pin1 and pin 5 is equal to button number 1. Since columns array's members are pin5, pin6, pin7 and
  pin8; and since rows array's members are pin1, pin2, and pin3; the conexion of pin5 and pin1, is equal
  to the position result[first member in columns array = 0][first member in rows array = 0] = result[0][0]
   = 1. Same way, according to schematic, button 2 is equal to pin2 and pin5, so same way we have that
  result[first member in columns array = 0][second member in rows array = 1] = result[0][1] = 2. And so on.
  result[3][2] = pin8 and pin3 is equal to # button, but, since we are working with int arrays, we represent
  it with number 11. We are not using # key at all tho.
  */
  result[0][0] = 1; result[0][1] = 2; result[0][2] = 3; result[1][0] = 4; result[1][1] = 5;
  result[1][2] = 6; result[2][0] = 7; result[2][1] = 8; result[2][2] = 9; result[3][1] = 0;
  result[3][2] = 11;
  pinSetUp(columns, rows); //We load pinSetUp void, the one that will set up all pins. Check pinStUp void for
  //deeper explanations.
  readPasswordInEeprom(numberOfDigits); /*We read the actual values burnt in Eeprom memory. We need to load this
  void as soon as system turns on because otherwise we password values would always be the defult ones.
  */
  printPasswordInEeprom(numberOfDigits); //We print in serial monitor the Eeprom's current values.
  startingLights(); //We load starting lights.
}
void loop() {
  /*Main loop of the system is based on mainMenuVariable. This variable is the one that sets us inside password change
  menu or not. If this variable is equals to low, then we get in the menu to change password, otherwise we will just
  load the confirmation void, and then the openClose void. Confirmation menu will check if what we typed is equal to
  actual value of Eeprom memory, and if so, it will set match = true. openClose void will either send a high pulse
  through A1 to the gate of mosfet and will trigger a green led for 2 seconds; or it will blink twice red light if
  password typed was wrong.
  In the other hand we have the new password menu. If mainMenuVariable == LOW, we get in this menu. This means that
  confirmation menu was loaded at least once, and it detected that * key was pressed. Since * was pressed,
  mainMenuVariable changed from HIGH to LOW. Once inside this conditional we will start by turning on the red LED constantly
  till we leave this menu to help the user to know which part of the code is being executed all the time. Then we send
  a message to serial monitor, and we set insideNewPasswordMenu as true, and mainMenuVariable to HIGH again. We will talk
  deeply about insideNewPasswordMenu variable, in newPassword void.
  We set mainMenuVariable again to HIGH because that way, if we leave the new password menu, we wont get again
  inside this menu, we will get just in the main loop. Then, orange led blinks 2, visual purpose only.
  New password menu will request the actual password with confirmation void. Confirmation void will set match to true or
  false. After loading confirmation void, and if insideNewPassWord is still true, (it can change during confirmation
  void), we load newPassword void. Once this void is over, we set red LED as input, and we leave new password menu.
  */


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
    confirmation (password, numberOfDigits, columns, rows);
    if (insideNewPasswordMenu)
      newPassword (password, numberOfDigits, columns, rows);
    pinMode(red, INPUT);
  }
  else {
    confirmation (password, numberOfDigits, columns, rows);
    openClose();
  }
}
