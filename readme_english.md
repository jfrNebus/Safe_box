# Introducción :uk:

This project was born to give a solution to a job need. I was in the need to protect some valuable goods, and a safe box was the best option. I was in the right place, at the right moment, when some partners removed an old safe box from a customer, in order to place a new one. This kind of safe box is programmed to delay the opening; this means that even if you have the key and the password, the triggering of the electromagnetic bolt that unlocks the lock, won't happen until the programmed delay is over. This is meant to protect the goods inside, in case the intruder forces the owner of the safe box to open the box. Since the box won't unlock the door until the delay is over, the intruder has to either wait, and maybe get caught while waiting; or leave, leaving the goods safe. This box was left in a specific place where the items to be recycled are stored. In addition, the password was unknown.

This box is designed to be fixed to a surface. The lock is secured by the bolt due to gravitational force. In other words, if the coil holding the bolt is out of power, the bolt stays in its position due to gravitational force, blocking the action of the key over the lock. When the circuit is powered, and the password provided is correct, the circuit powers the bolt's coil, lifting it, and freeing the lock.


<br>
<br>

## Funcionamiento 🧰

<br>

<p align="center">
 <img src="Docs/Images/bolt_work.png" width="576" height="432"/> 
</p>

In the picture above we have the control system. The first thing we can see is the control board, which was implemented by me as a replacement for the previous one. We can also see the electromagnetic bolt, the yellowed piece with the "12 Ohms" mark; and finally, the whole lock system. The lock moves from left to right according to the key's movement. The blue and red arrows show the behavior of the bolt, according to the power supplied to the coil. If the coil, represented by the yellowed rectangular piece, is powered, the bolt, the cylinder under / inside the coil, will be attracted to the coil, allowing the free movement of the lock. If the coil is not powered, the bolt falls due to gravitational force, blocking the lock.

The very first thing I had to do was to open the box. Luckily, the key was inside the lock, the main problem was to deal with the bolt. Since it was not fixed to any surface, as soon as I placed the box upside down, the bolt fell inside the coil by gravitational force, allowing me to open the door. Once the box was opened, I could check each part. 

<br>

### **Original board**:

<br>

<p align="center">
 <img src="Docs/Images/main_board.jpg" width="576" height="432"/> 
</p>

<br>

This is the original board. There are afew interesting elements:

- Microcontroller TSC80C31, with 32 inputs and outputs, and 128 bytes of RAM memory. 
- EPROM memory M27C64A. This memory is ideal for long programs. Here comes an interesting detail of this memory: the window at the top is used to erase the stored data. It is done by pointing ultraviolet light at it. The following pictures show a closer view of this window under a microscope.

<br>

<p align="center">
 <img src="Docs/Images/Microscope_images/1.jpg" width="400" height="225"/> 
 <img src="Docs/Images/Microscope_images/2.jpg" width="400" height="225"/> 
 <img src="Docs/Images/Microscope_images/3.jpg" width="400" height="225"/> 
 <img src="Docs/Images/Microscope_images/4.jpg" width="400" height="225"/>
</p>

<br>

### **Electromagnetic bolt**:

<br>

<p align="center">
 <img src="Docs/Images/electromagnetic_detailed.jpg" width="410" height="425"/> 
</p>

<br>

We have already talked about this part before. This component is the one responsible for locking or freeing the key. The printed value is indicates the resistance of the coil, which in this case it is 12 Ohms. This value is used to calculate the minimum amount of current needed for the coil to attract the bolt correctly. When the coil is powered through the cables, a magnetic field is created. This magnetic field attracts ferromagnetic elements, in this case, the bolt. When the power is lost, the magnetic field is also lost, freeing the bolt, which falls due to gravitational force, blocking the lock.

<br>

### **Keyboard**:

<br>

<p align="center">
 <img src="Docs/Images/keyboard_front.jpg" width="740" height="555"/> 
</p>

<br>

The password is provided through the keyboard, and the board evaluates it. If the password entered matches the one stored on the board, then the bolt will be triggered.

<br>

<p align="center">
 <img src="Docs/Images/keyboard_inside_front.jpg" width="370" height="278"/>
 <img src="Docs/Images/keyboard_inside_back.jpg" width="370" height="278"/>
</p>

It is easy to see that it is matrix keyboard. This keyboard has 12 conductive membrane push buttons. This kind of push button has two parts: the contacts printed on the board, the oval grey parts with a line in the middle; and the layer with the numbers, which is made in rubber with an small conductive surface under each button. When a button is pressed, its conductive part under the rubber layer connects both contacts in the oval part printed in the board, closing the circuit.

<br>

<p align="center">
 <img src="Docs/Schematics/matix_keyboard.png" width="767" height="432"/>
</p>

<br>

In a matrix keyboard, the connections of the buttons are made through columns and rows; each side of each button is connected to a column and a row. In the previous picture we have a matrix keyboard that I made to explain the main concept. The main point is to power one of the sides of the push buttons, and read the voltage value on the other side. We can power the columns, and then we could read the value on each row.

Let's say that we pressed button 4. We start powering column number 1, so at this point columns 2 and 3 are powerless. Column 1, (columns 1), is connected with side 1 of button 1, with side 1 of button 2, and with side one of button 3 (SW1, SW2 y SW3). Therefore, these 3 buttons are powered on their side 1. Then, the system starts reading the voltage value on each row. It starts by reading the value of row 1. In row 1, we have side 2 of button 1, which was not pressed, meaning that the circuit is not closed and the voltage sent through column 1 doesn’t reach side 2 of the button. This means that the voltage read in row 1 is 0V. This is understood by the board as button 1 not being pressed. Then we keep checking the behaviour of the other buttons in row 1. We meet button 4, which was pressed. Side 1 of button 4 is connected to column 2. This column is off at this point of the analysis, therefore, even if button 4 is pressed in this exact moment, the voltage read in row 1 is still 0. It happens the same with button 7. There is no voltage at all in row 1. It is guaranteed that button 1 was not pressed, because in order for it to be considered as pressed there must be a positive read in the row 1 while the column 1 is being powered.
Once the main working principle of row 1 and its buttons is understood, we can easily go through rows 2 and 3. We keep reading the voltage value in row 2. The column we are working with right now is number 1, since button 2 was not pressed it is in the same situation than button 1, there is no positive read in row 2 when column 1 is powered. It is guaranteed that button 2 was not pressed. Finally, we read row 3. Since button 3 was not pressed, the connection between column 1 and row 3 is not closed, there's no positive read in row 3 when column 1 is powered, therefore, button 3 was not pressed. 

At this point, the readings in all the rows is 0, so the system understands that the pressed button is either in column 2 or column 3. The action performed for column 1 will be performed for column 2. Columns 1 and 3 are set in a power-off state, and column 2 is powered. The reading process starts again. We start by reading the first row when column 2 is powered, the result is a positive voltage reading. The result is positive because in this example, the button pressed was number 4, which is connected to row 1 on its pin 2, and to column 2 on its pin 1. When the button is pressed while the power in column 2 is on, the circuit closes through row 1, generating a positive read in row 1. This is understood by the system as "button pressed", in this case, the one associated to row 1 and column 2. Once there is a button pressed, the analysis process is stopped, and the code keeps running.

It is really important to understand how a matrix keyboard works in order to optimize resources. A 9-button keyboard would usually require at least 9 microcontroller inputs, and all the associated wiring. As we saw in the previous example, for a 9-button matrix keyboard we used just 6 connections and much less wiring. Three of those connections are used as inputs to read the voltage values, and the other 3 connections are used as outputs to send the high level voltage on each column.

<br>

<p align="center">
 <img src="Docs/Schematics/actual_keyboard_layout.jpg"/>
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
 <img src="Docs/Images/custom_front.jpg" width="417" height="313"/> 
 <img src="Docs/Images/custom_back.jpg" width="417" height="313"/> 
</p>

The project is in version two. Same way the code was edited in order to fix some parts and adapt the whole code to follow the best practices, the board has been redesigned to implement LED control through transistors.

<br>

Version one used a MOSFET IRFP150 to control the electromagnetic bolt; it was the first one that I found in my workshop. However, this MOSFET is oversized for the board requirements. Recently, while making version two, I found a TIP31 transistor, whose values are closer to the requirements. The MOSFET's drain-source values are up to 100V for voltage and up to 44A for current, while the TIP31's collector-emitter voltage is up to 40V, and its current is up to 3A.

The LED management was handled by the board through a block of code whose logic was based on bad practices. This logic has been fixed in the new board by implementing 3 transistors. The transistor used for this purpose is the 2N3904, whose max collector-emitter values are 40V and 200mA. These values are more than enough to control a LED, since the LEDs used work in the range of 2V and 20mA.

<br>

### **Resistance calculation :zap:** 

<br>

Below are the operations needed to calculate the base resistance for all transistors on the board.

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

•	No protection factor applied to Ib:

  RBE = (VB - 0.7) / (IC / β) 

  <br>
  <br>
  
•	With protection factor applied to Ib:

  RBE = (VB - 0.7) / 3 * (IC / β)

  The protection factor is applied to increase the base current. This ensures that the transistor enters deep saturation, so it can work as a switch.
  
<hr>

<br>

#### - Base-emitter resistance for TIP31

<br>

Minimum β according to datasheet = 25
<br>
β acording to multimeter = 25

•	No protection factor applied to Ib:
RBE = (5 – 0.7) / (1 / 25) = 107,51

•	With protection factor applied to Ib:
RBE = (5 – 0.7) / 3 * (1 / 25) = 35,8

It was finally used the protection factor formula, with a common 22Ω resistor.

<br>

#### - Base-emitter resistance for 2N3904, and the resistence for LED protection.

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

The final resistance in use is a common 560Ω value. The second closest common value is 470Ω. It is recommended to use a greater value instead of a lower one which could damage the LED in the long term. Nevertheless, the damage caused by using a 470Ω resistor is almost negligible.

<br>

**Base-emitter resistance**

β according to datasheet = 100
<br>
β acording to multimeter = 151

•	β according to datasheet: 
  RBE = (5-0.7) / (3*(0.02/100)) = 4,3 / (3 * 0.0002) = 4,3 / 0.0006  = 7166,66

It was used a common 5,6kΩ value resistance.

<br>

### **Desarrollo del PCB :mechanic:**

Below is the electrical schematic, the PCB design, and the 3D model.

<br>
<br>

<p align="center"> 
 <img src="Docs/Schematics/board_schematic.jpg"/>
</p>

<br>

In this [link](Docs/Images/V1_schematic.png), you can find the electrical schematic for the first board. The code for this board was written by pairing the board pins and the keyboard pins, according to their numerical order. That is, the first keyboard pin connected to the first board pin, and so on. This is the reason why the cables between pins are crossed. This has been fixed through code, which makes a cleaner board. Additionally, the new board includes the connection block for the transistors, to control the LED.

I had to make a new element, the 13 pin female connector. I could not find it in any library, so I made a new one from a 4 pin one that I found in the library.

<br>

<p align="center"> 
 <img src="Docs/Images/female_header_13pin_device.png"/>
 <img src="Docs/Images/female_header_13pin_footprint.png"/>
</p>

<br>

From left to right: top layer, components placement; bottom layer, routing; drill layer.

<br>

<p align="center"> 
 <img src="Docs/Schematics/pcb_design_1.jpg" width="289" height="360"/>
 &nbsp;
 <img src="Docs/Schematics/pcb_design_2.jpg" width="289" height="360"/>
 &nbsp;
 <img src="Docs/Schematics/pcb_design_3.jpg" width="289" height="360"/>
</p>

<br>

From left to right: top layer, mixed layer, bottom layer.

<p align="center"> 
 <img src="Docs/Images/3D_PCB_front_view.png" width="432" height="524"/>
 &nbsp;
 <img src="Docs/Images/3D_PCB_mixed_view.png" width="432" height="524"/>
 &nbsp;
 <img src="Docs/Images/3D_PCB_back_view.png" width="432" height="549"/>
</p>

**Note:** The 3D design of the arduino shows an element out of place. That's not something I can fix.

Some of the components used don't have a 3D design. I didn't pay attention to the components in the library; I just needed the right drill hole sizes for each component, since the PCB was going to be ordered without the components.

<br>

### **Resultado final :magic_wand:**

The board was sent to be produced on November 24th, and it was received on December 4th. The minimum order placed was 5 PCBs, components not included, which priece is 4.29€. The shipping method used was the cheapest one, "Global Standard Direct Line" for 1.69€, which shipping time is about 12 to 16 days. Additionally, it was charged 1.25€ as taxes and customs, and 0.5€ as extra payment for paying using paypal as method. The final priece, everything included, is 7.73€ for 5 PCBs without components.

<br>

<p align="center"> 
 <img src="Docs/Images/no_arduino.jpg" width="386" height="351"/>
 &nbsp;
 <img src="Docs/Images/arduino.jpg" width="323" height="405"/>
 &nbsp;
 <img src="Docs/Images/tracks.jpg" width="371" height="467"/>
</p>

As always, the final result is absolutely perfect. There's no production error in the board. No faults of manufacturing are found on the board. However, there are design mistakes.
* The board is missing the polarity marks in the ink layer, close to both of screw terminal blocks. The lack of polarity marks can lead to problems when the PCB is connected to a power supply, or when the electromagnetic bolt is connected to the terminal (the bolt has a diode in parallel, if it is not connected correctly it could damage the TIP31 transistor).
* The fastening holes on the bottom are misplaced. There measurements, taken using a vernier caliper, were not set correctly, while the PCB design process.
* The analysis followed to design and to code the led control block, was wrong, and therefore, the PCB and the code had to be modified. The first version, [V1_schematic](Docs/Images/V1_schematic.png), shows the green LED cathode junction with the pin 10 in the connector, and the red LED cathode juntion with the pin 12. This is wrong, as it occurs in reverse. During the testing process for the new PCB, the red LED was performing the actions associated to the green LED, and the other way arround. This problem WAS fixed by reassigning the green and red LEDs variables to the A2 and A4 outputs. Additionally, the names of the transistors which control each LED, as well as the names of those nets associated to these LEDs, were changed.
* Some of the elements were not soldered correctly. The top left screw terminal block and TIP31 are slightly tilted. Also, the welds are in good shape, but they are dirty. They must be cleaned them with isopropyl alcohol.

<br>

## **Conclusion :thinking:**

Version 2 of the PCB has been a considerable improvement over version 1. The code and the hardware have been fixed. ADditionally, the professional result obtained thanks to producing the PCB with a professional company, has replaced the production of the PCB with perforated breadboard.
Despite all these improvements, the version 2 can still be improved. The version 3 will fix the above mentioned mistakes. Furthermore, I am currently waiting for some microcontrollers that ordered, I will try to replace the Arduino board. This way, version 3 could be more compact.
