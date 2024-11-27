# Introducción :uk:

This proyect was bornt to give a solution to a job need. I was in the need to protect some valuable goods, and a safe box was the best thing to do so. I was in the right place, in the right moment, when some partners removed from a customer, an old safe box, in order to place a new one. This kind of safe box is programed to delay the openning; this means that even if you have the key and the password, the triggering of the electromagnetic bolt which unlocks the lock, won't happen till the programmed delay is over. This is meant to protect the goods on its inside in case the intruder forces the owner of the safe box to open the box. Since box won't open the door till the delay is over, the intruder has to either wait, and maybe get cuaght while waiting; or he has to leave, leaving goods safe. This box was left in a specific place where the things to be recycled are stored. In addition, the password was unknown.

This box is designed to be fixed to a surface, the lock gets locked by the bolt, because of the gravity force. In other words, if the coil where the bolt is placed, is out of power, the bolt stays on its position because of the gravity force, blocking the action of the key over the lock. When the circuit is powerred, and the password provided is right, the circuit powers de bolt's coil, lifting it, and freeing the lock.


<br>
<br>

## Funcionamiento 🧰

<br>

<p align="center">
 <img src="Images/bolt_work.png" width="576" height="432"/> 
</p>

In the picture above we have the control system. The first thing we can see is the control board, the one implemented by me as replacement of the previous one. We can also see the electromagnetic bolt, the yellowed piece with the "12 Ohms" mark; and finally, the whole lock system. The lock moves left to right according the the key movement. The blue and red arrows show the behavior of the bolt, according to the power supplied to the coild. If the coil, the yellowed rectangle shape piece, is powered, the bolt, the cylinder under / inside the coil, will get attracted to the coil, allowing the free movement of the lock. If the coil is not powered, the bolt falls by gravity attraction, blocking the lock.

The very first thing I had to do was to open the box. Luckily, the key was inside the lock, the main problem was to deal with the bolt. Since it was not fixed to any surface, as soon as I placed the box upside down, the bolt felt inside the coil by gravity force, allowing to open the door. Once the box was opened, I could check each part. 

<br>

### **Original board**:

<br>

<p align="center">
 <img src="Images/main_board.jpg" width="576" height="432"/> 
</p>

<br>

This is the original board. There are few interesting elements:

- Microcontroller TSC80C31, with 32 inputs and outputs, y 128 bytes of RAM memory. 
- EPROM memory M27C64A. This memory is ideal for long programs. Here comes an interesting detail of this memory: the window at the top of the memory is used to erase the saved data. It is done by pointing to it with an ultraviolet light. The following pictures show a closer view, through a microscope, of this window.

<br>

<p align="center">
 <img src="Images/Microscope_images/1.jpg" width="400" height="225"/> 
 <img src="Images/Microscope_images/2.jpg" width="400" height="225"/> 
 <img src="Images/Microscope_images/3.jpg" width="400" height="225"/> 
 <img src="Images/Microscope_images/4.jpg" width="400" height="225"/>
</p>

<br>

### **Electromagnetic bolt**:

<br>

<p align="center">
 <img src="Images/electromagnetic_detailed.jpg" width="410" height="425"/> 
</p>

<br>

We have already talked about this part before. This part is the one locking or freeing the key. The printed vaule is the resistance of the coil, which in this case it is 12 Ohms. This value is the one used to calculate the minimum amount of current needed for the coil to attract the bolt correctly. When the coil is powered through the cables, a magnetic field is created. This magnetic field attracts ferromagnetic elements, in this case, the bolt. When the power is lost, the magnetic field is also lost, freeing the bolt, which falls by the gravity force, blocking the lock.

<br>

### **Keyboard**:

<br>

<p align="center">
 <img src="Images/keyboard_front.jpg" width="740" height="555"/> 
</p>

<br>

The password is provided through the keyboard, the board will be the one evaluating it. If the password entered matches the one burnt on the board, then the bolt will be triggered.
<br>

<p align="center">
 <img src="Images/keyboard_inside_front.jpg" width="370" height="278"/>
 <img src="Images/keyboard_inside_back.jpg" width="370" height="278"/>
</p>

It is easy to see that it is matrix keyboard. This keyboard has 12 conductive membrane push buttons. This kind of push buttons have two parts: the contacts printed int the board, the oval grey parts with a line in the middle; and the layer with the numbers, which is made in rubber with an small conductive surface under each button. When a button is pressed, its conductive part under the rubber layer connects both contacts in the oval part printed in the board, closing the circuit.

<br>

<p align="center">
 <img src="schematics/matix_keyboard.png" width="767" height="432"/>
</p>

<br>

In a matrix keyboard, the connections of the buttons are made through columns and rows; each side of each button is connected to a column and a row. In the previous picture we have a matrix keyboard that i did to explain the main concept. The main point is to power one of the sides of push buttons, and to read the voltage value on the other side. We can power the columns, and then we could read the value on each row.

Let's say that we pressed the button 4. We start powering the column number 1, so at this point the columns 2 and 3 are powerless. The column 1, (columns 1), is connected with the side 1 of button 1, with the side 1 of button 2, and with the side one of button 3, (SW1, SW2 y SW3). Therefore, these 3 buttons are set as powered on their side 1. Then, the system starts reading the voltage value on each row. It starts by reading the value of row 1. In the row 1 we have the side 2 of button 1, which was not pressed, which means that the circuit is not closed and the voltage sent through column 1 doesn’t reach the side 2 of the button. This means that the voltage read in the row 1 is 0V. This is understood by the board like the button 1 was not pressed. Then we keep checking the behaviour of the other buttons in the row 1. We meet the button 4, which was pressed. The side 1 of the button 4 is connected to column 2. This column is off at this point of the analysis, therefor, even if the button 4 is pressed in this exact moment, the voltage read in the row 1 is still 0. It happens the same with the button 7. There is no voltage at all in the row 1. It is guaranteed that the button 1 was not pressed, because in order for it to be considered as pressed there must be a positive read in the row 1 while the column 1 is being powered.
Once the main working principle of row 1 and its buttons is understood, we can easily go through the rows 2 and 3. We keep reading the voltage value in the row 2. The column we are working with right now is the number 1, since the button 2 was not pressed it is in the same situation than the button 1, there is not a positive read in the row 2 when the column 1 is powered. It is guaranteed that the button 2 was not pressed. Finally, we read the row 3. Since the button 3 was not pressed, the connection between column 1 and row 3 is not closed, there's no positive read in the row 3 when the column 1 is powered, therefor, the button 3 was not pressed. 

At this point, the read in all the rows is 0, so the system understands that the pressed button is either in column 2 or column 3. The action performed for the column 1 will be performed for the column 2. Columns 1 and 3 are set in a power off state, and the column 2 is powered. The reading process starts again. We start by reading the first row when the column 2 is powered, the result is a positive voltage read. The result is positive because in this example, the button pressed was the number 4, which is connected to the row 1 on its pin number 2, and to the column 2 on its pin number 1. When the button is pressed while the power in the column 2 is on, the circuit gets closed through the row 1, generating a positive read in the row 1. This is understood by the system as "button pressed", in this case, the one associated to row 1 and column 2. Once there is a button pressed, the analysis process is stopped, and the code keeps running.

It is really important to understand how a matrix keyboard works in order to optimize resources. A 9 buttons keyboard would, usually, require at least 9 microcontroller inputs, and all the associated wiring. As we could see in the previous example, for a 9 buttons matrix keyboard we used just 6 connections and way less wiring. Tree of those connections are used as inputs to read the voltage values, and the other 3 contacts are used as outputs to send the high level voltage on each column.

<br>

<p align="center">
 <img src="schematics/actual_keyboard_layout.jpg"/>
</p>

<br>

Now that we know what a matrix keyboard is, and how it works, we can see in the previous picture that the keyboard in our safe box is also a matrix keyboard. In the picture we can see two schematics, both of them quite more complex than the first example. Both of them represent the real connections in the keyboard. In the left schematic we see all the push buttons, set in 2 rows, and vertically oriented, close to the 3 LED lights. Some tracks have parts coloured in blue, those blue parts represent the tracks printed in the back face of the board; the wine colour tracks are the front face tracks. The tracks are drawn as they are in the real board, with light changes. The right schematic keeps the real connections between push buttons and pins, but I organized them in a different way, for everyone to easily understand the connections between rows and columns through the push buttons. The yellow tracks represent the columns, the green ones represent the rows. The button * is connected to two independent pins, just because that's how the board developer wanted it to be.
Once everything about the hardware has been understood, the comments in the arduino files can be read in order to understand how the software part works.

<br>

<p align="center">
    <a href="Keyboard_english_V2/Teclado/Teclado.ino"><img src="https://img.shields.io/badge/Keyboard%20File-773dd2?style=plastic"/></a>
    <a href="Keyboard_english_V2/Teclado/Voids.ino"><img src="https://img.shields.io/badge/Voids%20File-44cb11?style=plastic"/></a>
</p>

<br>
<br>

## Board developement :electron:

<br>


<p align="center"> 
 <img src="Images/custom_front.jpg" width="417" height="313"/> 
 <img src="Images/custom_back.jpg" width="417" height="313"/> 
</p>

The project is in the version two. As well as the code was edited in order to fix some parts to fit the whole code to the best practices, the board has been redesigned to implement the LED control through transistors.

<br>

The version one used a mosfet IRFP150 to control the electromagnetic bolt


POR AQUI 


para el control del perno electromagnético, porque era lo que tenía más a mano en mi taller, no obstante este mosfet esta sobredimensionado para este circuito. Recientemente, a la hora de rediseñar la placa, encontré un transistor TIP31 en el taller, el cual es más acorde a las necesidades del circuito. Donde el mosfet aguanta valores en drain-source de hasta 100V de tensión y 44A de corriente, el tip31 aguanta en colector-emisor de hasta 40V de tensión y 3A de corriente.

En la versión uno del circuito, la gestión de los led se lograba por medio de un tipo de lógica de programación erronea; actualmente esa lógica se ha corregido y se han implementado 3 transistores para el control de los led. El transistor usado es el 2N3904, cuyos valores máximos en colector-emisor son 40V y 200mA, valores de sobra para controlar leds que trabajan en torno a los 2V y 20 miliamperios.

<br>

### **Calculo de resistencias** 

<br>

A continuación, se muestran todos los cálculos necesarios para el cálculo de resistencias en base de los transistores de la placa.

<hr>

RBE = VB / IB
β = IC / IB  >> IB = IC / β

•	Sin aplicar el factor de protección sobre Ib:
  RBE = (Voltaje en base - 0.7) / (IC / β (También conocido como hFE) 

•	Con factor de protección sobre Ib:
  RBE = (Voltaje en base - 0.7) / 3 * (IC / β (También conocido como hFE))
  
  Este factor se usa para incrementar la intensidad en base, esto garantiza que el transistor entre en saturación profunda y funcione como un interruptor.

<hr>

<br>

#### - Resistencia base-emisor TIP31

<br>

β mínima según datasheet = 25
β mínima según polímetro = 25

•	Sin aplicar el factor de protección sobre Ib:
RBE = (5 – 0.7) / (1 / 25) = 107,51

•	Con factor de protección sobre Ib:
RBE = (5 – 0.7) / 3 * (1 / 25) = 35,8

Al final se usa el cálculo con factor de protección para garantizar la saturación del transistor en su uso como interruptor. Se usa un valor de resistencia común de 22Ω.

<br>

#### - Resistencia base-emisor 2N3904 y resistencias de protección para los led.

<br>

**Resistencias de protección para los LEDs**

Se trata de 3 led de 3mm.
<br>
•	Rojo: 20mA, 1.9-2.1V.
<br>
•	Amarillo: 20mA, 2V.
<br>
•	Verde: 20mA, 2.2-2.4V

Calculo de la resistencia en serie para proteger el led:

R = (Vfuente – VLED) / I

•	Rojo y amarillo:
R = (12 – 1.9) / 0.02 = 505 Ohms
•	Verde:
R = (12 – 2.2) / 0.02 = 490 Ohms

Finalmente se usan resistencias de 560Ω. Esto es debido a que el otro valor estándar inmediato es de 470Ω. Es preferible exceder el valor, antes que quedarse corto y forzar los leds. No obstante, el daño ocasionado por una resistencia de 470Ω sería prácticamente nulo.

<br>

**Resistencias base-emisor**

β según data sheet = 100
<br>
β según multímetro = 151

•	β según data sheet: 
  RBE = (5-0.7) / (3*(0.02/100)) = 4,3 / (3 * 0.0002) = 4,3 / 0.0006  = 7166,66

Se usa un valor de resistencia común de 5,6k.

<br>

### **Desarrollo de la placa**

A continuación se muestra el esquema eléctrico, el diseño de la PCB, y el modelo 3D de la misma.

<br>
<br>

<p align="center"> 
 <img src="schematics/board_schematic.jpg"/>
</p>

<br>

Haciendo clic en el siguiente [enlace](Images/Esquema_electrónico.png), podemos acceder al esquema electrónico de la primera versión de la placa. En un origen se escribió el código estableciendo el conexionado entre los pines del teclado y los pines del aruino, siguiendo la correlación numérica, es decir, el pin 1 del conector del teclado con el pin 1 de la placa etc. Esto generaba que, por la ubicación del conector del teclado y la posición del arduino, el cableado entre pines se cruzase. Esto ha sido corregido en código, generando un conexionado mucho más limpio. Adicionalmente, el esquema de la versión 2 incluye el bloque de conexiones de los transistores de control para el manejo de los led.

Para este proyecto tuve que crear un nuevo elemento, el conector hembra de 13 pines. O bien no lo encontré entre las librerías pero existe, o bien no existe. Para su creación tomé como referencia uno de menor número de pines.

<br>

<p align="center"> 
 <img src="Images/female_header_13pin_device.png"/>
 <img src="Images/female_header_13pin_footprint.png"/>
</p>

<br>


De izquierda a derecha: capa superior, ubicación de los elementos; capa inferior, routeo de los elementos; capa de drill, mapa de perforación de los pad de los elementos.

<br>

<p align="center"> 
 <img src="schematics/pcb_design_1.jpg" width="289" height="360"/>
 &nbsp;
 <img src="schematics/pcb_design_2.jpg" width="289" height="360"/>
 &nbsp;
 <img src="schematics/pcb_design_3.jpg" width="289" height="360"/>
</p>

<br>

De izquierda a derecha: capa superior, capa mixta, capa inferior.

<p align="center"> 
 <img src="Images/3D_PCB_front_view.png" width="432" height="524"/>
 &nbsp;
 <img src="Images/3D_PCB_mixed_view.png" width="432" height="524"/>
 &nbsp;
 <img src="Images/3D_PCB_back_view.png" width="432" height="549"/>
</p>

**Nota:** El diseño 3D del arduino seleccionado presenta un error, se observa un integrado atravesando el arduino. 

Algunos de los elementos seleccionados no tienen archivo 3D. En este proyecto no se ha prestado atención al elemento concreto seleccionado en la librería. La placa se solicitó sin los elementos incluidos ya que se iban a usar elementos própios.














