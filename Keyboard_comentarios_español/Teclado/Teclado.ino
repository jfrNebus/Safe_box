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
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, LOW);
  pinMode(pin9, INPUT);
  digitalWrite(pin9, HIGH);
  //magnet1 es el pin que activará el pin gate, del transistor mosfet.
  pinMode(magnet1, OUTPUT);
  //Inicializamos el monitor serial, para imprimir los mensajes de reporte de estado de la ejecución del sistema.
  Serial.begin(9600);
  /*Ahora establecemos los valores de cada combinació de pines. De cacuerdo al esquema de conexiones del teclado,
  la conexión entre el pin1 y pin5 corresponde al botón número 1. Dado que los elementos en el array colums son:
  pin5, pin6, pin7 y pin8; y debido a que los elementos en el array filas son: pin1, pin2 y pin3; la conexión 
  entre pin5 y pin1, es igual al valor almacenado en result[posición de pin5 en columns = 0][posición de pin1 en
  rows = 0] => result[0][0] = 1. De la misma forma, de acuerdo al esquema, el botón dos es igual a la conexión
  entre pin5 y pin2, result[posición de pin5 en columns = 0][posición de pin2 en rows = 0] => result[0][0] = 2.
  Se continúa de esta forma. result[3][2] = pin 8 y pin 3, igual al botón #. Dado que estamos trabajando con 
  un array de integers, representamos # como el número 11. No obstante, no se está usando el botón # para nada.*/
  result[0][0] = 1; result[0][1] = 2; result[0][2] = 3; result[1][0] = 4; result[1][1] = 5;
  result[1][2] = 6; result[2][0] = 7; result[2][1] = 8; result[2][2] = 9; result[3][1] = 0;
  result[3][2] = 11;
  pinSetUp(columns, rows); //Llamamos al método pinSetUp, el cual configurará todos los pines. Se aconseja revisar
  //la infocmación comentada en dicho método para una explicación más detallada.
  readPasswordInEeprom(numberOfDigits); /*Leemos los valores almacenados actualmente en la memoria Eeprom. Es necesario
  llamar a este método tan pronto como se alimente el sistema, de lo contrario los valores de la contraseña serían 
  siempre los valores por defecto.
  */
  printPasswordInEeprom(numberOfDigits); //Imprimimos los valores actuales guardados en la Eeprom, en la consola serial.
  startingLights(); //Cargamos la secuencia de luces inicial.
}
void loop() {
  /*El loop principal del sistema se basa en la variable mainMenuVariable. Esta variable es la que nos situa, o no, dentro
  del menú "inside password change". Si el valor de esta variable es low, entonces entramos en el menú de cambio de contraseña,
  de lo contrario, lanzamos los métodos "confirmation" y "openClose".

  POR MODIFICAR-----: Modifica confirmation para devuelva un booleano. Usa este booleano para lanzar o no openClose. Revisa 
  también si este boleano se podría usar en lugar de la siguiente parte de código, dentro del if principal del void loop.
  
  confirmation (password, numberOfDigits, columns, rows);
    if (insideNewPasswordMenu)

  El menú "confirmation" evaluará si la contraseña que se introdujo, es igual al valor actual de la memoria Eeprom. Si ambas 
  contraseñas coinciden, se establecerá la variable match como true. El método openClose enviará un pulso alto al pin gate
  del mosfet y activará el led verde, durante 2 segundos; o bien hará que el led rojo parpadee dos veces, si la contraseña
  introducida es erronea, en función del resultado de la variable "match" reportada por "confirmation".

  Por otro lado, tenemos el menú de contraseña nueva. Si mainMenuVariable es igual a LOW, entramos en este menu. Esto quiere 
  decir que "confirmation" fue lanzado al menos una vez, y detectó que la botón * fue presionado. Dado que * fue presionado,
  mainMenuVariable cambió de tener un valor HIGH a tener un valor LOW. Una vez dentro del condicional, encendemos el led rojo
  de forma constante hasta que abandonemos este menu. Esto le sirve al usario para conocer, en todo momento, qué parte del 
  código se está ejecutando. Depués, enviamos un mensaje al monitor serie, establecemos insideNewPasswordMenú como true, y
  mainMenuVariable como HIGH de nuevo. Hablaremos más profundamente acerca de la variable insideNewPasswordMenu, en el método
  newPassword. 
  Establecemos mainManuVariable de nuevo como HIGH porque de esta forma, si abandonamos el menú new password, no volveremos
  de nuevo a este condicional, volveremos al loop principal. A continuación, el led naranja parapadea dos veces. Sirve como 
  indicativo visual únicamente. Para poder alcanzar el método newPassword, se debe registrar el ingreso de la contraseña de 
  forma correcta, mediante el método confirmation. Este método establecerá match como true o false. Despues de lanzar el 
  método confirmation, si insideNewPasswordMenu sigue siendo true, (su valor puede ser modificado en el interior del método 
  confirmation), cargamos el método newPassword. Una vez este método finaliza, establecemos we el led rojo como input, y
  abandonamos el menú new password.

  POR MODIFICAR-----: Revisa lo de encender o apagar los led no usando digitalWrite, sino estableciendo los pines como 
  inputs u outputs.
  */
  Serial.println("Main Menu.");
  if (mainMenuVariable == LOW) {
    pinMode(red, OUTPUT);
    Serial.println("Inside new password conditional.");
    mainMenuVariable = HIGH; //Check if this line is really needed considering that it is being sent in confirmation.
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
