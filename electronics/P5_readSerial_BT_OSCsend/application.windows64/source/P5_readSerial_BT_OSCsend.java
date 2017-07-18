import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import oscP5.*; 
import netP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class P5_readSerial_BT_OSCsend extends PApplet {



Serial myPort;
Serial myPort2;



OscP5 oscP5;
NetAddress myRemoteLocation;

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

public void setup() 
{
  background(0); 
  
  println(Serial.list());
  String portName = Serial.list()[2];
  //String portName2 = Serial.list()[7];
  myPort = new Serial(this, portName, 9600);
  //myPort2 = new Serial(this, portName, 9600);
  myPort.clear(); 
  println(portName);
  //myPort2.clear(); 
  /*
  String portName2 = Serial.list()[4];
   myPort2 = new Serial(this, portName2, 9600);
   */
  oscP5 = new OscP5(this, 12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 7000);


  // println(portName2);
  textAlign(CENTER);
}

public void draw()
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
        OscMessage myMessage = new OscMessage("/pulse");
        myMessage.add(val);
        oscP5.send(myMessage, myRemoteLocation);
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
        //println(val);
        if (val<255-thressGSR) {
          valGSR = val;
          // if (debug)
          //println("Val GSR: "+valGSR );
          OscMessage myMessage = new OscMessage("/gsr");
          myMessage.add(valGSR);
          oscP5.send(myMessage, myRemoteLocation);
        }
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
public void exit() {
  myPort.clear(); 
  myPort.stop();
}

public void keyPressed() {
  if (key == 'd')
    debug =! debug;
}
  public void settings() {  size(400, 600); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "P5_readSerial_BT_OSCsend" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
