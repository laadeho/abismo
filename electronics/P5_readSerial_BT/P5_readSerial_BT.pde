import processing.serial.*;

Serial myPort;
Serial myPort2;

int val, val2;
boolean sensorPulso = false;
boolean sensorGSR = false;
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
  String portName = Serial.list()[2];
  //String portName2 = Serial.list()[7];
  myPort = new Serial(this, portName, 9600);
  //myPort2 = new Serial(this, portName, 9600);
  myPort.clear(); 
  //myPort2.clear(); 
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

    if (val == 'A') { // 65 sensorPulso
      sensorPulso = true;
      //println("Sensor 1 con val: "+val);
    }
    if (sensorPulso) { // COMPROBAR SI ES 15 DEL SENSOR DE PULSO
      if (val == 'H') { // 72
        esUno = true;
        //println("sPulso y val: "+val);
      }

      /*if (esUno && val == 53) { // 5
       esCinco = true;
       }*/
      if (esUno && val!='H' && val != ',') {
        valPulso = val;
        /*if (debug)
         println("Pulso: "+val );
         */
      } else 
      valPulso = 0;
    }

    if (val == 'B') { // 66 sensorGSR
      sensorGSR = true;
      //println("Sensor 2");
    }
    if (sensorGSR) { // 20 GSR
      // COMPROBAR SI ES 20 DEL GSR
      if (val == 'I') { // 2
        esDos = true;
        //println("sGSR y val: "+val);
      }
      /*if (esDos && val == 48) { // 0
       esCero = true;
       } */
      if (esDos && val!='I' && val != ',') {
        if (val>thressGSR)
          valGSR = val;
       // if (debug)
          //println("Val GSR: "+valGSR );
      }
    }
    if (val == ',' && sensorPulso) {
      sensorPulso = false;
      esUno = false;
      //esCero = false;
    }
    if (val == ',' && sensorGSR) {
      sensorGSR = false;
      esDos = false;
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
    stroke(255, 0, 0);
    line(pX, 100+valPulso, ppX, 100+ppY2);

    stroke(255);
    line(pX, 200+pY, ppX, 200+ppY);
  } else  
  background(0, 20);

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

//void serialEvent(Serial p) {
// int valor = p.read();
//println(valor);
//}
void exit() {
  myPort.clear(); 
  myPort.stop();
}

void keyPressed() {
  if (key == 'd')
    debug =! debug;
}