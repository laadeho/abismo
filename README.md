# abismo // próximo 
Proyecto multimedia en torno a la proximidad y el reconocimiento humano.

#### Sensaciones
0. Entendimiento / Tranquilidad 0:00 - 1:29
Espacio en el que se pretende que el participante entienda el funcionamiento de la pieza, representando de manera clara e incluso literal los valores recibidos por los diversos sensores

1. Expectativa 1:30 - 2:59
En este momento los participantes estarán atentos y a la expectativa de lo que sucede a continuación, será un momento de entendimiento con la pieza. Palabras clave: futuro, esperanza, cautela, posibilidad...

2. Miedo 3:00 - 4:29
Adrenalina y amenaza, miedo a lo desconocido, sonidos e imágenes que sacan de la zona de confort, y que evocan peligro. Sonidos e imágenes que provoquen a los participantes el sentimiento de querer huir o esconderse. 

3. Asombro 4:30 - 5:59
Sonidos e imágenes que evoquen la introspección, que recuerden lo pequeño que es el ser humano en relación a las cosas, la naturaleza. Lo extraordinario e inesperado. Sorpresa, “El asombro puede provocarse por un acontecimiento positivo (agradable), pero también por un hecho negativo (dañino o doloroso).”

4. Euforia 6:00 - 7:29
Momento de éxtasis, excitación; bombardeo de imágenes y sonidos a una velocidad mayor al ritmo cardíaco del visitante, y analizar si lo podemos acelerar ligeramente.

5. Tristeza 7:30 - 8:59
Será muy contrastante a la parte anterior, se notarán mucho los cambios en tempo, volumen y texturas.

6. Abismo 9:00 -  10:29
Esta será una parte climática e introspectiva. Palabras clave: Incomprensible, profundidad, pensamiento, alma, muerte, incertidumbre...

7. Felicidad 10:30 - 11:59
Conceptos que generen sensaciones de satisfacción, felicidad, plenitud

8. Reconocimiento 12:00 - 13:29
Gradualmente se incita a la reflexión, paz; introspección que da pié al reconocimiento entre los participantes.
- Proximidad
Terminan mediciones, se retiran sensores y continúa la etapa de “reconocimiento” entre usuarios; platican, se conocen y hacemos una breve entrevista, cerrando la experiencia.

## Estructura de repositorio.
#### Jerarquía de archivos
abismo
- /website
- /electronics
- /grafica
- /sonido
- /herramientas

#### ToDo List
* website
** Rediseño para lanzamiento 2017 (30 Abril)
** Diseño de sistema de registro y programación
* electronics
** Sensor Resistencia Galvánica / parches electroestimuladores
* grafica
** Crear los 8 ambientes que se presentarán en la pieza
* sonido
** 8 ambientes sonoros que respondan a los diversos estímulos de 2 usuarios (2Muse, 2Sensor Pulso Cardiaco, 2Sensor Resistencia Galvánica)
* herramientas (GettingData)
** Conexión Muse<-OSC->Grafica/Sonido

#### Tecnologías utilizadas:
* website; HTML, CSS, JavaScript, 
* electronics; C/C++, Arduino, Fritzing
* grafica; C++, OpenFrameworks
* sonido; SCLang, SuperCollider
* herramientas; C++, lubMuse for Windows, oscPack

#### Desarrolladores
* website: Eduardo H. Obieta.
* electronics. Eduardo H. Obieta
* grafica. Eduardo H. Obieta
* sonido. Aimée Theriot
* herramientas. Eduardo H. Obieta, Rodrigo Torres (Xumo)

En el archivo .gitignore esta la carpeta /audio/samples/ para evitar la subida de archivos innecesarios.

![alt tag](http://abismo.cc/images/agradecimiento_coverFB.png)

Interfaz envío OSC
![alt tag](https://github.com/laadeho/abismo/blob/master/website/images/UIosc.png?raw=true)

// Learn Git
https://try.github.io/levels/1/challenges/1