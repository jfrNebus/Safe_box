# Safe box, by jfrNebus
 
> [!IMPORTANT]
> Finalicé este proyecto hace bastante tiempo. No obstante, ahora quiero revisarlo. Quiero orregir aquellas
> partes que no sigan unas _buenas prácticas_, optimizarlo etc. Adicionalmente, ahora trabajo con un productor
> de placas electrónicas, por ello, quiero rediseñar el circuito, seleccionar un nuevo transistor, y enviar a
> producir la placa para obtener un resultado profesional.
> 
> I finished this project long ago, nevertheless, now I want to review it. I want to fix those parts that don't
> follow the _best practices_ code, I want to optimize everything etc. In addition, now I work with a electronics
> board producer, so I want to design a new circuit, to change the transistor, and to get the new board professionally
> produced.
>
> For english speakers [click here](#intro) 🇬🇧

<br>

<hr> 
Este proyecto nace cuando, por necesidades laborales, se necesitó una caja fuerte donde poder almacenar una serie de bienes de valor. En un momento determinado, un departamento de mi empresa retiró, por sustitución, un modelo específico de caja fuerte de un cliente. Este modelo específico tiene asociado un retardo a la apertura de la puerta; es decir, aunque dispongas de la llave y la contraseña, la activación del perno electromagnético que libera la cerradura, no se producirá hasta pasado un determinado tiempo. Esto garantiza que, en caso de que el intruso intente coaccionar al responsable de la caja, esta no se abra hasta que el tiempo de retardo haya finalizado, lo que lo obliga a permanecer más tiempo en la instalación, arriesgándose a ser capturado. Esta caja fuerte fue depositada en el apartado de desechos para reciclar, era un modelo antiguo no óptimo para dicho cliente, y se desconocía la contraseña, es por ello que la rescaté.

Estas cajas están pensadas para ser fijadas a una superficie debido a que el perno actúa por gravedad. Es decir, si la bobina del perno no tiene alimentación, el perno permanece en su posición por la acción de la gravedad, bloqueando la acción de la llave sobre la cerradura. Cuando se alimenta el circuito y se introduce la contraseña de forma correcta, el circuito alimenta la bobina del perno, atrayéndolo, liberando la acción de la llave.

<p align="center">
 <img src="Images/bolt_work.png" width="576" height="432"/> 
</p>

En la imagen anterior tenemos el interior del sistema de control. Lo primero que se observa es la placa de control implementada por mi; el perno electromagnético, la pieza de color amarillento en la que está escrito “12 Ohms”; y por último, el cierre y la cara interior de la cerradura. El cierre se mueve de izquierda a derecha en función de la acción de la llave. Las flechas dibujadas muestran el comportamiento del cierre y del perno en función de la alimentación que reciba la bobina. Si la bobina, la pieza rectangular amarillenta en la que está escrito “12 Ohms” recibe alimentación, el perno, la pieza cilíndrica ubicada justo debajo de la bobina, se verá atraída hacia la bobina, permitiendo el libre movimiento del cierre. Si la bobina no recibe alimentación, el perno cae por su propio peso, bloqueando el movimiento del cierre, impidiendo la acción de la llave.

Lo primero que hice fue descubrir la forma de abrir la caja. Por suerte la llave estaba puesta en la cerradura, el problema era ver cómo sortear el perno electromagnético. Al no estar fijada a ninguna superficie, en cuanto le di la vuelta a la caja, el perno cayó por gravedad al interior de la bobina, liberando la cerradura. Una vez abierta la caja, la desmonté por completo y analicé cada parte.

<br>

**Placa original**: 

<br>

<p align="center">
 <img src="Images/main_board.jpg" width="576" height="432"/> 
</p>

<br>

Esta es la placa original de la caja. Se observan un par de elementos de interés:

- Microcontrolador TSC80C31, con 32 entradas y salidas, y 128 bytes de RAM. 
- Memoria EPROM M27C64A. Esta memoria es ideal para programas largos. Como curiosidad, cabe destacar la ventana que se observa en el medio de la memoria, la cual sirve para borrar su contenido apuntando a la misma con un haz de luz ultravioleta. A continuación, se muestran unas imágenes del interior de dicha ventana al microscopio.

<br>

<p align="center">
 <img src="Images/Microscope_images/1.jpg" width="400" height="225"/> 
 <img src="Images/Microscope_images/2.jpg" width="400" height="225"/> 
 <img src="Images/Microscope_images/3.jpg" width="400" height="225"/> 
 <img src="Images/Microscope_images/4.jpg" width="400" height="225"/>
</p>

<br>

**Perno electromagnético**

<br>

<p align="center">
 <img src="Images/electromagnetic_detailed.jpg" width="410" height="425"/> 
</p>

<br>

Ya hemos hablado de esta parte anteriormente, es el encargado de bloquear o liberar la acción de la llave. El valor impreso en el cuerpo de la bobina es el valor de la resistencia de la misma, en este caso 12 ohmios. Este valor es el que se toma a la hora de hacer cálculos para conocer la intensidad de corriente mínima que ha de proveer la fuente de alimentación para hacer que la bobina atraiga correctamente al perno. Cuando se alimenta la bobina por medio de los cables, se genera un campo magnético que atrae a todos los cuerpos ferromagnéticos, en este caso, el perno. Cuando la alimentación se pierde, se pierde a su vez el campo magnético, ocasionando que el perno caiga por su propio peso bloqueando el cierre.

**Teclado**

<br>

<p align="center">
 <img src="Images/keyboard_front.jpg" width="740" height="555"/> 
</p>

<br>

A través del teclado se introduce la clave de acceso que será recogida por la placa para su evaluación. Si la clave es correcta, el perno electromagnético se activa. Resulta facil darse cuenta de que se trata de un teclado matricial en cuanto se observa la placa del teclado.

<br>

<p align="center">
 <img src="Images/keyboard_inside_front.jpg" width="370" height="278"/>
 <img src="Images/keyboard_inside_back.jpg" width="370" height="278"/>
 <img src="Images/matix_keyboard.png" width="305" height="192"/>
 <img src="Images/actual_keyboard_layout.jpg"/>
</p>

<br>












