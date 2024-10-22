# Safe box, by jfrNebus
 
> [!IMPORTANT]
> Finalicé este proyecto hace bastante tiempo. No obstante, ahora quiero revisarlo. Quiero corregir aquellas partes que no sigan unas _buenas prácticas_, optimizarlo etc. He detectado, durante la realización de la presente documentación, varios fallos fruto que cometí cuando era más novato. Adicionalmente, ahora trabajo con un productor de placas electrónicas, por ello, quiero rediseñar el circuito, seleccionar un nuevo transistor, y enviar a producir la placa para obtener un resultado profesional.
> 
> I finished this project long ago, nevertheless, now I want to review it. I want to fix those parts that don't follow the _best practices_ code, I want to optimize everything etc. While writting the project's documentation, I could get some mistakes I did when I was more unexperienced. In addition, now I work with a electronics board producer, so I want to design a new circuit, to change the transistor, and to get the new board professionally produced.
>
> For english speakers [click here](#intro) 🇬🇧

<br>

<hr> 

<br>

### Introducción

Este proyecto nace cuando, por necesidades laborales, se necesitó una caja fuerte donde poder almacenar una serie de bienes de valor. En un momento determinado, un departamento de mi empresa retiró, por sustitución, un modelo específico de caja fuerte de un cliente. Este modelo específico tiene asociado un retardo a la apertura de la puerta; es decir, aunque dispongas de la llave y la contraseña, la activación del perno electromagnético que libera la cerradura no se producirá, hasta pasado un determinado tiempo. Esto garantiza que, en caso de que el intruso intente coaccionar al responsable de la caja, esta no se abra hasta que el tiempo de retardo haya finalizado, lo que lo obliga a permanecer más tiempo en la instalación, arriesgándose a ser capturado. Esta caja fuerte fue depositada en el apartado de desechos para reciclar, era un modelo antiguo no óptimo para dicho cliente. Adicionalmente, se desconocía la contraseña.

Estas cajas están pensadas para ser fijadas a una superficie debido a que el perno actúa por gravedad. Es decir, si la bobina del perno no tiene alimentación, el perno permanece en su posición por la acción de la gravedad, bloqueando la acción de la llave sobre la cerradura. Cuando se alimenta el circuito y se introduce la contraseña de forma correcta, el circuito alimenta la bobina del perno, atrayéndolo, liberando la acción de la llave.


<p align="center">
 <img src="Images/bolt_work.png" width="576" height="432"/> 
</p>

En la imagen anterior tenemos el interior del sistema de control. Lo primero que se observa es la placa de control implementada por mi; el perno electromagnético, la pieza de color amarillento en la que está escrito “12 Ohms”; y por último, el cierre y la cara interior de la cerradura. El cierre se mueve de izquierda a derecha en función de la acción de la llave. Las flechas dibujadas muestran el comportamiento del cierre y del perno en función de la alimentación que reciba la bobina. Si la bobina, la pieza rectangular amarillenta recibe alimentación, el perno, la pieza cilíndrica ubicada justo debajo de la bobina, se verá atraída hacia la bobina, permitiendo el libre movimiento del cierre. Si la bobina no recibe alimentación, el perno cae por su propio peso, bloqueando el movimiento del cierre, impidiendo la acción de la llave.

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

Ya hemos hablado de esta parte anteriormente. Es el encargado de bloquear o liberar la acción de la llave. El valor impreso en el cuerpo es el valor de la resistencia de la bobina, en este caso 12 ohmios. Este valor es el que se toma a la hora de hacer cálculos para conocer la intensidad de corriente mínima que ha de proveer la fuente de alimentación para hacer que la bobina atraiga correctamente al perno. Cuando se alimenta la bobina por medio de los cables, se genera un campo magnético que atrae a todos los cuerpos ferromagnéticos, en este caso, el perno. Cuando la alimentación se pierde, se pierde a su vez el campo magnético, ocasionando que el perno caiga por su propio peso bloqueando el cierre.

<br>

**Teclado**

<br>

<p align="center">
 <img src="Images/keyboard_front.jpg" width="740" height="555"/> 
</p>

<br>

A través del teclado se introduce la clave de acceso, que será recogida por la placa para su evaluación. Si la clave es correcta, el perno electromagnético se activa. 

<br>

<p align="center">
 <img src="Images/keyboard_inside_front.jpg" width="370" height="278"/>
 <img src="Images/keyboard_inside_back.jpg" width="370" height="278"/>
</p>

Resulta facil darse cuenta de que se trata de un teclado matricial en cuanto se observa la placa sin la capa de los números. Este teclado está compuesto por un total de 12 pulsadores de membrana conductiva. Este tipo de pulsadores están formados por dos partes: la parte de los contactos impresos en la placa, las partes ovaladas con una línea en el medio; y la capa de números, una superficie de goma con un material conductor debajo de cada botón. Cuando se presiona dicho botón de silicona, la parte conductora debajo del mismo toca los dos lados del óvalo impreso en la placa, cerrando el circuito.

<br>

<p align="center">
 <img src="Images/matix_keyboard.png" width="767" height="432"/>
</p>

<br>

En un teclado matricial, el conexionado de los botones se realiza mediante filas y columnas; cada lado de cada botón esta conectado a una fila y a una columna. En la imagen anterior tenemos un modelo que he creado para explicar el concepto. El principio de funcionamiento se basa en alimentar uno de los lados de los pulsadores, y leer el valor de voltaje en el otro lado. Es decir, podemos alimentar con un voltaje las columnas, por ejemplo, y realizar la lectura de voltaje presente en las filas.

Supongamos que hemos pulsado el botón 4. Empezamos alimentando con voltaje solo la columna 1, dejando sin voltaje las columnas 2 y 3. La columna 1, (columns 1), se conecta con el lado 1 del botón 1, con el lado 1 del botón 2 y con el lado 1 del botón 3, (SW1, SW2 y SW3). Por lo tanto, estos tres botones pasan tener alimentación en su lado 1. Acto seguido, le indicamos al sistema que lea el valor de voltaje presente en las filas, (rows). Empieza leyendo el valor de la fila 1. En la fila 1 tenemos el lado 2 del botón 1, que no ha sido presionado, por lo tanto el circuito no se cierra y la tensión, el voltaje, enviado por la columna 1 no llega al lado 2 del botón, con lo que la lectura en la fila 1 es 0V. Esto es interpretado por el sistema como que el botón 1 no ha sido presionado. A continuación, seguimos leyendo los pulsadores de la fila 1 y nos encontramos el botón 4, que si que fué presionado. El el lado 1 del botón 4, se conecta con la columna 2, columna que no está siendo alimentada en esta fase del análisis, luego aunque se cierre el circuito al presionar el botón, la lectura en la fila 1 sigue siendo 0. Lo mismo ocurre con el botón 7. Esto quiere decir que por la fila 1 no existe voltaje alguno. En este punto se garantiza que no se ha pulsado el botón 1, porque para que dicho botón se considere pulsado, tendría que existir una lectura positiva de voltaje en la fila 1 mientras la columna 1 esta siendo alimentada.

Habiendo entendido el análisis completo del comportamiento de la fila 1 y de cada uno de los botones asociados a ella, podemos resumir el análisis de las filas 2 y 3. Continuamos leyendo el valor de voltaje en la fila 2. La columna que nos interesa es la 1, dado que el botón 2 no ha sido presionado, ocurre lo mismo que con el botón 1, no existe lectura positiva en la fila 2 cuando la columna 1 está siendo alimentada, lo que garantiza que el botón 2 no ha sido presionado. Seguimos leyendo el valor de la fila 3. El botón 3 no se presionó, no se cierra el circuito, no hay lectura de voltaje positiva en la fila 3 cuando la columna 1 está siendo alimentada, por lo que se garantiza que el botón 3 no ha sido presionado.

En este punto, habiendo recibido lectura negativa en las tres filas, el sistema entiende que el botón presionado es alguno de los asociados a las columnas 2 y 3, por lo que se repite la misma actuación. Se retira la alimentación de la columna 1, se alimenta la columna 2, y se mantiene sin alimentación la columna 3. En este punto, se inicia un nuevo proceso de lectura de filas. Empezamos leyendo el valor de la fila uno, que en este caso es un valor positivo. El valor de la fila 1 es positivo porque el botón presionado es el 4, que está asociado a la fila 1 por su lado 2, y a la columna 2 por su lado número 1. Cuando se presiona el botón 4 mientras existe alimentación en la columna 2, se cierra el circuito con la fila 1, generando un valor de lectura positivo en la fila 1. Esto es interpretado por el sistema, el valor de lectura de voltaje positivo, como que dicho botón, el botón asociado a las fila 1 y columna 2, ha sido presionado. En este momento se detiene el análisis y se realiza la operación pertinente. 

Entender el funcionamiento de un teclado matricial es vital para la optimización de recursos, cuando se trabaja con un teclado. Un teclado con 9 botones supondría, habitualmente, si no se usa un teclado matricial, el uso de 9 entradas en un microcontrolador, además de todo el cableado asociado a los mismos. Como hemos visto en el ejemplo anterior, para un teclado de 9 botones, hemos usado 6 contactos del microcontrolador. De esos 6 contactos, 3 se usan como entradas para recibir la lectura de las filas, y 3 como salidas para establecer el pulso alto de voltaje para cada columna.

<br>

<p align="center">
 <img src="Images/actual_keyboard_layout.jpg"/>
</p>

<br>

Teniendo claro qué es, y cómo funciona un teclado matricial, podemos observar, en la imagen anterior, que el teclado de la caja fuerte también es un teclado matricial. En la imagen se observan dos figuras bastante más complejas que la del primer ejemplo. Ambas figuras representan el conexionado real del teclado. En la figura de la izquierda vemos una serie de pulsadores, colocados en dos filas y orientados de forma vertical, junto a los tres diodos LED de colores. Algunas de los tramos de ciertas pistas de conexión son de color azul, representan las partes de las pistas que están impresas por la cara trasera de la placa; las pistas de color vino, representan las pistas impresas en la cara frontal de la placa. El recorrido de algunas de las pistas varía ligeramente respecto a las pistas impresas en la placa, no obstante es una representación clara. La figura de la derecha mantiene el conexionado real entre pulsadores y pines, pero he organizado todo de forma que resulte más fácil percibir la union de las columnas y las filas, con los pulsadores. Las pistas de color amarillo representan las columnas, y las pistas de color verde representan las filas. El boton * se conecta a dos pines de forma independiente, porque así lo creyó oportuno el desarrollador que diseñó la placa del circuito.



<br>
<br>

Teniendo claro todo lo explicado anteriormente, solo queda leerse las comentarios escritos en el propio código para entender el funcionamiento completo del sistema.














