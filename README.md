# abismo // próximo 
Proyecto multimedia en torno a la proximidad y el reconocimiento humano.

## PENDIENTES CUATRIMESTRE
Eduardo H. Obieta:
* Continuar el desarrollo de programación de herramientas de vídeo (Processing).
* Continuar con el desarrollo visual de la pieza.
* Diseño de mobiliario.
* Hacer pruebas de los sensores construido.

Aimée Theriot 
* Continuar con la difusión de la página en medios digitales
* Continuar el desarrollo de programación de herramientas de audio (SuperCollider)
* Continuar con el diseño sonoro
* Hacer pruebas de los sensores construidos

Diego Montesinos
* Programación y mantenimiento de sitio web
* Programación para comunicación con aplicación de audio y video
* Hacer pruebas de los sensores construidos

### Metas por cuatrimestre:

* 1 Aplicación en SuperCollider para transformar los datos en sonido
* 1 Aplicación en Processing para transformar los datos en vídeo
* Conexión entre aplicaciones y el sitio web

## /////////////

#### Sensaciones
1. Entendimiento / Tranquilidad 0:00 - 1:29 Funcionamiento de la pieza.

2. Expectativa 1:30 - 2:59 Futuro, esperanza, cautela, posibilidad...

3. Miedo 3:00 - 4:29 Adrenalina y amenaza, miedo a lo desconocido, peligro, salir de zona de confort.

4. Asombro 4:30 - 5:59 Introspección, que recuerden lo pequeño que es el ser humano en relación a las cosas, la naturaleza. Lo extraordinario e inesperado. Sorpresa, “El asombro puede provocarse por un acontecimiento positivo (agradable), pero también por un hecho negativo (dañino o doloroso).”

5. Euforia 6:00 - 7:29 Momento de éxtasis, excitación; bombardeo de imágenes y sonidos a una velocidad mayor al ritmo cardíaco del visitante, y analizar si lo podemos acelerar ligeramente.

6. Tristeza 7:30 - 8:59
Será muy contrastante a la parte anterior, se notarán mucho los cambios en tempo, volumen y texturas.

7. Abismo 9:00 -  10:29
Esta será una parte climática e introspectiva. Palabras clave: Incomprensible, profundidad, pensamiento, alma, muerte, incertidumbre...

8. Felicidad 10:30 - 11:59
Conceptos que generen sensaciones de satisfacción, felicidad, plenitud

9. Reconocimiento 12:00 - 13:29
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

### etiquetas de los mensajes OSC:
//Estos valores son *Relative*
- /alpha
- /beta
- /gamma
- /delta
- /theta

Artifacts
- /blink (solo cuando parpadea)
- /jawClench (solo cuando tensas la mandíbula)

Accelerometer
- /accX
- /accY
- /accZ

Gyroscope
- /gyroX
- /gyroY
- /gyroZ

Is Good (Revisa que los sensores estén bien colocados)
- /eeg1
- /eeg2
- /eeg3
- /eeg4
- /auxLeft
- /auxRight

Battery %
- /battery

### ToDo List
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

## Interfaz envío OSC

![alt tag](https://github.com/laadeho/abismo/blob/master/website/images/UI_200417.png?raw=true)