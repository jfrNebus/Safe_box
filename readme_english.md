# Introducción :uk:

This project was born to give a solution to a job need. I was in the need to protect some valuable goods, and a safe box was the best thing to do so. I was in the right place, at the right moment, when some partners removed from a customer, an old safe box, in order to place a new one. This kind of safe box is programmed to delay the opening; this means that even if you have the key and the password, the triggering of the electromagnetic bolt which unlocks the lock, won't happen until the programmed delay is over. This is meant to protect the goods inside, in case the intruder forces the owner of the safe box to open the box. Since the box won't open the door until the delay is over, the intruder has to either wait, and maybe get caught while waiting; or leave, leaving the goods safe. This box was left in a specific place where the things to be recycled are stored. In addition, the password was unknown.

This box is designed to be fixed to a surface, the lock gets locked by the bolt, because of the gravitational force. In other words, if the coil where the bolt is placed is out of power, the bolt stays in its position because of the gravitational force, blocking the action of the key over the lock. When the circuit is powered, and the password provided is correct, the circuit powers the bolt's coil, lifting it, and freeing the lock.


<br>
<br>

## Funcionamiento 🧰

<br>

<p align="center">
 <img src="Images/bolt_work.png" width="576" height="432"/> 
</p>

In the picture above we have the control system. The first thing we can see is the control board, the one implemented by me as replacement for the previous one. We can also see the electromagnetic bolt, the yellowed piece with the "12 Ohms" mark; and finally, the whole lock system. The lock moves from left to right according to the the key movement. The blue and red arrows show the behavior of the bolt, according to the power supplied to the coil. If the coil, the yellowed rectangle shape piece, is powered, the bolt, the cylinder under / inside the coil, will get attracted to the coil, allowing the free movement of the lock. If the coil is not powered, the bolt falls by gravitational attraction, blocking the lock.

The very first thing I had to do was to open the box. Luckily, the key was inside the lock, the main problem was to deal with the bolt. Since it was not fixed to any surface, as soon as I placed the box upside down, the bolt fell inside the coil by gravitational force, allowing me to open the door. Once the box was opened, I could check each part. 

<br>

### **Original board**:

<br>

<p align="center">
 <img src="Images/main_board.jpg" width="576" height="432"/> 
</p>

<br>

This is the original board. There are few interesting elements:

- Microcontroller TSC80C31, with 32 inputs and outputs, and 128 bytes of RAM memory. 
- EPROM memory M27C64A. This memory is ideal for long programs. Here comes an interesting detail of this memory: the window at the top of the memory is used to erase the saved data. It is done by pointing ultraviolet light at it. The following pictures show a closer view, through a microscope, of this window.

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

We have already talked about this part before. This part is the one responsible for locking or freeing the key. The printed value is the resistance of the coil, which in this case it is 12 Ohms. This value used to calculate the minimum amount of current needed for the coil to attract the bolt correctly. When the coil is powered through the cables, a magnetic field is created. This magnetic field attracts ferromagnetic elements, in this case, the bolt. When the power is lost, the magnetic field is also lost, freeing the bolt, which falls by the gravitational force, blocking the lock.

<br>

### **Keyboard**:

<br>

<p align="center">
 <img src="Images/keyboard_front.jpg" width="740" height="555"/> 
</p>

<br>

The password is provided through the keyboard, the board will be the one evaluating it. If the password entered matches the one burned on the board, then the bolt will be triggered.
<br>

<p align="center">
 <img src="Images/keyboard_inside_front.jpg" width="370" height="278"/>
 <img src="Images/keyboard_inside_back.jpg" width="370" height="278"/>
</p>

It is easy to see that it is matrix keyboard. This keyboard has 12 conductive membrane push buttons. This kind of push buttons has two parts: the contacts printed on the board, the oval grey parts with a line in the middle; and the layer with the numbers, which is made in rubber with an small conductive surface under each button. When a button is pressed, its conductive part under the rubber layer connects both contacts in the oval part printed in the board, closing the circuit.

<br>

<p align="center">
 <img src="schematics/matix_keyboard.png" width="767" height="432"/>
</p>

<br>

In a matrix keyboard, the connections of the buttons are made through columns and rows; each side of each button is connected to a column and a row. In the previous picture we have a matrix keyboard that i did to explain the main concept. The main point is to power one of the sides of the push buttons, and to read the voltage value on the other side. We can power the columns, and then we could read the value on each row.

Let's say that we pressed button 4. We start powering column number 1, so at this point columns 2 and 3 are powerless. Column 1, (columns 1), is connected with side 1 of button 1, with side 1 of button 2, and with side one of button 3 (SW1, SW2 y SW3). Therefore, these 3 buttons are set as powered on their side 1. Then, the system starts reading the voltage value on each row. It starts by reading the value of row 1. In row 1 we have side 2 of button 1, which was not pressed, which means that the circuit is not closed and the voltage sent through column 1 doesn’t reach side 2 of the button. This means that the voltage read in row 1 is 0V. This is understood by the board like button 1 was not pressed. Then we keep checking the behaviour of the other buttons in row 1. We meet button 4, which was pressed. Side 1 of button 4 is connected to column 2. This column is off at this point of the analysis, therefor, even if button 4 is pressed in this exact moment, the voltage read in row 1 is still 0. It happens the same with button 7. There is no voltage at all in row 1. It is guaranteed that button 1 was not pressed, because in order for it to be considered as pressed there must be a positive read in the row 1 while the column 1 is being powered.
Once the main working principle of row 1 and its buttons is understood, we can easily go through rows 2 and 3. We keep reading the voltage value in row 2. The column we are working with right now is number 1, since button 2 was not pressed it is in the same situation than button 1, there is not a positive read in row 2 when column 1 is powered. It is guaranteed that button 2 was not pressed. Finally, we read row 3. Since button 3 was not pressed, the connection between column 1 and row 3 is not closed, there's no positive read in row 3 when column 1 is powered, therefor, button 3 was not pressed. 

vas por aquí vas por aquí vas por aqui

At this point, the readings in all the rows is 0, so the system understands that the pressed button is either in column 2 or column 3. The action performed for column 1 will be performed for column 2. Columns 1 and 3 are set in a power-off state, and column 2 is powered. The reading process starts again. We start by reading the first row when column 2 is powered, the result is a positive voltage read. The result is positive because in this example, the button pressed was number 4, which is connected to row 1 on its pin 2, and to column 2 on its pin 1. When the button is pressed while the power in column 2 is on, the circuit closes through row 1, generating a positive read in row 1. This is understood by the system as "button pressed", in this case, the one associated to row 1 and column 2. Once there is a button pressed, the analysis process is stopped, and the code keeps running.

It is really important to understand how a matrix keyboard works in order to optimize resources. A 9-button keyboard would, usually, require at least 9 microcontroller inputs, and all the associated wiring. As we saw in the previous example, for a 9-button matrix keyboard we used just 6 connections and much less wiring. Three of those connections are used as inputs to read the voltage values, and the other 3 connections are used as outputs to send the high level voltage on each column.

<br>

<p align="center">
 <img src="schematics/actual_keyboard_layout.jpg"/>
</p>

<br>

Now that we know what a matrix keyboard is, and how it works, we can see in the previous picture that the keyboard in our safe box is also a matrix keyboard. In the picture we can see two schematics, both of them much more complex than the first example. Both of them represent the real connections in the keyboard. In the left-hand schematic we see all the push buttons, set in 2 rows, and vertically oriented, close to the 3 LED lights. Some tracks have parts colored in blue, those blue parts represent the tracks printed in the back face of the board; the wine-color tracks are the front face tracks. The tracks are drawn as they are in the real board, with light changes. The right-hand schematic keeps the real connections between push buttons and pins, but it is organized differently to make it easier for everyone to understand the connections between rows and columns through the push buttons. The yellow tracks represent the columns, the green ones represent the rows. The button * is connected to two independent pins, just because that's how the board developer wanted it to be.
Once everything about the hardware has been understood, the comments in the Arduino files can be read in order to understand how the software part works.

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

Sigue por aquí sigue por aquí

The project is in the version two. As well as the code was edited in order to fix some parts to fit the whole code to the best practices, the board has been redesigned to implement the LED control through transistors.

<br>

The version one used a mosfet IRFP150 to control the electromagnetic bolt, it was the first one that I found in my workshop, however, this mosfest is oversized for the board requirements. Recently, while making the version two, I found a TIP31 transistor, which values are closer to the required. The mosfet's drain-source values are up to 100V for voltage and up to 44A for current, while the TIP31's collector-emitter voltage is up to 40V, and up to 3A for current.

The LED management was dealt by the board through a bloc of code which logic was based in bad practices; this logic has been fixed for the new board by implementing 3 transistors. The transistor used for this purpose is the 2N3904, which max collector-emitter values are 40V and 200mAh. This values are more than enough to control a LED, since the LEDs used work in the range of 2V and 20mAh.

<br>

### **Resistance calculation :zap:** 

<br>

Below are the operations needed to calculate the base resistance for all transistors in the board.

<hr>
RBE = base-emitter resistance.
<br>
VB = Base voltage.
<br>
IB = Base current.
<br>
β = current gain for the transistor (also known as hFE).
<br>
IC = collector current.

<br>
<br>

RBE = VB / IB
<br>
β = IC / IB  >> IB = IC / β
<br>
0.7 = voltage drop across the base-emitter junction of the transistor.

<br>
<br>

•	No protection factor applied over Ib:

  RBE = (VB - 0.7) / (IC / β) 

  <br>
  <br>
  
•	With protection factor applied over Ib:

  RBE = (VB - 0.7) / 3 * (IC / β)

  The protection factor is applied to increase the base current. This ensures that the transistor goes into deep saturation, so it can work as a switch.
  
<hr>

<br>

#### - Base-emitter resistance for TIP31

<br>

Minimum β according to datasheet = 25
<br>
β acording to multimeter = 25

•	No protection factor applied over Ib:
RBE = (5 – 0.7) / (1 / 25) = 107,51

•	With protection factor applied over Ib:
RBE = (5 – 0.7) / 3 * (1 / 25) = 35,8

It was finally used the protection factor formula, with a common 22Ω value resistance.

<br>

#### - Base-emisor resistance for 2N3904, and the resistences for the leds protection.

<br>

**LED resistance**

3 led de 3mm.
<br>
•	Red: 20mA, 1.9-2.1V.
<br>
•	Yellow: 20mA, 2V.
<br>
•	Green: 20mA, 2.2-2.4V

Series resistance calculation:

R = (Vsource – VLED) / I

•	Red and yellow:
<br>
R = (12 – 1.9) / 0.02 = 505 Ohms
<br>
•	Green:
<br>
R = (12 – 2.2) / 0.02 = 490 Ohms

The final resistance in use is a common 560Ω value. The second closest common value is 470Ω. It is recommended to use a greater value instead of a lower one which could damage the LED in the long term. Nevertheless, the damage done in case using a 470Ω resistance is almost null.

<br>

**Base-emitter resistance**

β according to datasheet = 100
<br>
β acording to multimeter = 151

•	β according to datasheet: 
  RBE = (5-0.7) / (3*(0.02/100)) = 4,3 / (3 * 0.0002) = 4,3 / 0.0006  = 7166,66

It was used a common 5,6kΩ value resistance.

<br>

### **Board developement :electric_plug:**

Below is the electrical schematic, the PCB design, and the 3D model.

<br>
<br>

<p align="center"> 
 <img src="schematics/board_schematic.jpg"/>
</p>

<br>

In this [link](Images/Esquema_electrónico.png), you can find the electrical schematic for the first board. The code for this board was written pairing the board pins and the keyboard pins, according to their numerical order. That is, the first keyboard pin connected to the first board pin, and so on. This is the reasson why the cables between pins are crossed. This has been fixed through code, which makes a cleaner board. Additionally, the new board includes the connection bloc for the transistors, to control the LED.

I had to make a new element, the 13 pin female connector. I could not find it in any library, so I made a new one from a 4 pin one that I found in the library.

<br>

<p align="center"> 
 <img src="Images/female_header_13pin_device.png"/>
 <img src="Images/female_header_13pin_footprint.png"/>
</p>

<br>

From left to right: top level layer, components placement; bottom layer, routing; drilling layer.

<br>

<p align="center"> 
 <img src="schematics/pcb_design_1.jpg" width="289" height="360"/>
 &nbsp;
 <img src="schematics/pcb_design_2.jpg" width="289" height="360"/>
 &nbsp;
 <img src="schematics/pcb_design_3.jpg" width="289" height="360"/>
</p>

<br>

From left to right: top layer, mixed layer, bottom layer.

<p align="center"> 
 <img src="Images/3D_PCB_front_view.png" width="432" height="524"/>
 &nbsp;
 <img src="Images/3D_PCB_mixed_view.png" width="432" height="524"/>
 &nbsp;
 <img src="Images/3D_PCB_back_view.png" width="432" height="549"/>
</p>

**Note:** The 3D design of the arduino shows an element out of place. That's not something I can fix.

Some of the components used don't have a 3D design. I didn't pay attention to the components in the library; I just needed the right drill hole sizes for each component, since the PCB was going to be ordered without the components.














