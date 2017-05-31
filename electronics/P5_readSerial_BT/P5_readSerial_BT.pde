/*
Buscar si existe algún "flush" para cada determinado tiempo
 limpiar la cola de mensajes de los puertos seriales y así
 tener la información en tiempo real.
 */
import processing.serial.*;

Serial myPort;
Serial myPort2;

int val, val2;
boolean sensor1 = false;
boolean sensor2 = false;
// Dos/Cero // 50/48
boolean esDos = false;
boolean esCero = false;

boolean esUno = false;
boolean esCinco = false;

int valGSR = 0;
int pX, pY, ppX, ppY, ppX2, ppY2;
int thressGSR = 30;
boolean debug = false;

int valPulso;

void setup() 
{
  background(0); 
  size(400, 600);
  println(Serial.list());
  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 9600);
  myPort.clear(); 

  /*
  String portName2 = Serial.list()[4];
   myPort2 = new Serial(this, portName2, 9600);
   */
  println(portName);
  // println(portName2);
  textAlign(CENTER);
}

void draw()
{
  if (debug)
    println(myPort.available());
  if ( myPort.available() > 0) {
    val = myPort.read();
    if (debug)
      println(val);

    if (val == 'A') { // 65 Sensor1
      sensor1 = true;
      //println("Sensor 1");
    }    
    if (val == 'B') { // 66 Sensor2
      sensor2 = true;
      //if (debug)
        //println("Sensor 2");
    }
    if (sensor1) { // 20 GSR
      // COMPROBAR SI ES 20 DEL GSR
      if (val == 50) // 2
        esDos = true;
      /*if (esDos && val == 48) { // 0
       esCero = true;
       } */
      if (esDos && val!=50 && val != 44) {
        if (val>thressGSR)
          valGSR = val;
        if (debug)
          println("Val GSR: "+valGSR );
      }
    }
    if (sensor2) {
      //////////////////////////
      // COMPROBAR SI ES 15 DEL SENSOR DE PULSO
      if (val == 49) // 1
        esUno = true;
      /*if (esUno && val == 53) { // 5
       esCinco = true;
       }*/
      if (esUno && val!=49 && val != 44) {
        valPulso = val;
        if (debug)
          println("Pulso: "+val );
      } else 
      valPulso = 0;
    }

    if (val == 44 && sensor1) {
      sensor1 = false;
      esDos = false;
      esCero = false;
    }
    if (val == 44 && sensor2) {
      sensor2 = false;
      esUno = false;
      // esCinco = false;
    }
  }
  //println( myPort.available());
  if ( myPort.available() > 100) {
    myPort.clear();
    if (debug)
      println("////////////////////////////////// myPort CLEAR");
  }

  pX++;
  pX=pX%width;
  pY = valGSR; 

  strokeWeight(1);
  if (pX%width != 0) {
    stroke(255);

    line(pX, 200+pY, ppX, 200+ppY);
    stroke(255, 0, 0);

    line(pX, 100+valPulso, ppX, 100+ppY2);
  } else  
  background(0);

  ppX = pX; 
  ppY = pY;  
  ppY2 = valPulso;



  /*
  pushStyle();
   if (val == 3) {   
   fill(0, 255, 0);
   } else {    
   fill(0);
   }
   
   rect(250, 50, 100, 100);
   popStyle();
   */


  /*
  pushStyle();
   if (val2 == 0) { 
   fill(255, 0, 0);
   } else {
   fill(0);
   }
   rect(50, 50, 100, 100);
   
   popStyle();
   */
  /*
  pushStyle();
   fill(0);
   text("Sensor V: "+val, width/2, height/2);
   fill(255);
   text("Sensor V: "+val, width/2+2, height/2+2);
   popStyle();
   */
}

void serialEvent(Serial p) {
  // int valor = p.read();
  //println(valor);
}
void exit() {
  myPort.clear(); 
  myPort.stop();
}