import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.*; 
import controlP5.*; 
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

/*
PENDIENTES 
 - Conectar dos sensores
 - Enviar a OFX y a SC
 */



ControlP5 cp5;
CheckBox checkbox;


Serial myPort;
Serial myPort2;



OscP5 oscP5;
NetAddress puerto7000, puerto57120;

int val1, val2;
// Mensajes de los diferentes sensores
boolean sensorPulso1, sensorPulso2;
boolean sensorGSR1, sensorGSR2;
// Comprueba cuando es H o I
boolean esH1, esH2;
boolean esI1, esI2;
// Variables de los sensores GSR Y Pulso
int valGSR1, valGSR2;
int valPulso1, valPulso2;

int pX, posGSRy1, posGSRy2;

int ppX_1, ppY_1, ppX2_1, ppY2_1;
int ppX_2, ppY_2, ppX2_2, ppY2_2;

int thressGSR = 30;
boolean debug = false;

public void setup() 
{
  frame.setTitle("abismo // proximo _ PULSE & GSR");
  background(0); 
  

  cp5 = new ControlP5(this);

  checkbox = cp5.addCheckBox("checkBox")
    .setPosition(50, height-50)
    .setSize(20, 20)
    .setItemsPerRow(2)
    .setSpacingColumn(150)
    .setSpacingRow(20)
    .addItem("OSC to 57120", 0)
    .addItem("OSC to 7000", 0)
    ;

  println(Serial.list());
  String portName = Serial.list()[2];
  String portName2 = Serial.list()[4];

  myPort = new Serial(this, portName, 9600);
  myPort2 = new Serial(this, portName2, 9600);
  myPort.clear(); 
  myPort2.clear(); 
  println(portName+", "+portName2);

  oscP5 = new OscP5(this, 12000);
  puerto7000 = new NetAddress("127.0.0.1", 7000);
  puerto57120 = new NetAddress("127.0.0.1", 57120);

  textAlign(CENTER);
}

public void draw()
{

  if (debug) {
    println("Port 1: "+myPort.available());
    println("Port 2: "+myPort2.available());
  }

  pushStyle();
  fill(0);
  noStroke();
  rect(0, 0, width, 100);
  fill(255);
  textSize(18);
  text("abismo // pr\u00f3ximo", width/2, 50);
  popStyle();

  grafica(1, 0, 75);
  grafica(2, 0, 425);
}

public void grafica(int numSerial, int posX, int posY) {
  pX++;
  pX=pX%width;

  if (numSerial == 1) {
    if ( myPort.available() > 0) {
      val1 = myPort.read();

      if (val1 == 'A') { // 65 sensorPulso
        sensorPulso1 = true;
      }
      if (sensorPulso1) { // COMPROBAR SI ES 15 DEL SENSOR DE PULSO
        if (val1 == 'H') { // 72
          esH1 = true;
        }

        if (esH1 && val1 != 'H' && val1 != ',') {
          valPulso1 = val1;

          OscMessage myMessage = new OscMessage("/pulse");
          myMessage.add(numSerial);
          myMessage.add(val1);
          oscP5.send(myMessage, puerto7000);
          oscP5.send(myMessage, puerto57120);
        } else 
        valPulso1 = 0;
      }

      if (val1 == 'B') { // 66 sensorGSR
        sensorGSR1 = true;
      }
      if (sensorGSR1) { // 20 GSR
        // COMPROBAR SI ES 20 DEL GSR
        if (val1 == 'I') { // 2
          esI1 = true;
        }

        if (esI1 && val1 != 'I' && val1 != ',') {
          if (val1<255-thressGSR) {
            valGSR1 = val1;

            OscMessage myMessage = new OscMessage("/gsr");
            myMessage.add(numSerial);
            myMessage.add(valGSR1);
            oscP5.send(myMessage, puerto7000);
            oscP5.send(myMessage, puerto57120);
          }
        }
      }
      if (val1 == ',' && sensorPulso1) {
        sensorPulso1 = false;
        esH1 = false;
      }
      if (val1 == ',' && sensorGSR1) {
        sensorGSR1 = false;
        esI1 = false;
      }
    }

    if ( myPort.available() > 100) {
      myPort.clear();
    }

    posGSRy1 = valGSR1; 

    strokeWeight(1);
    if (pX%width != 0) {
      stroke(255, 0, 0);
      line(posX+pX, posY+100+valPulso1, posX+ppX_1, posY+100+ppY2_1);

      stroke(255);
      line(posX+pX, posY+250+posGSRy1, posX+ppX_1, posY+250+ppY_1);
    } else  
    background(0, 20);
  } else  if (numSerial == 2) {/////////////////////////////////////////////////////////
    if ( myPort2.available() > 0) {
      val2 = myPort2.read();

      if (val2 == 'A') { // 65 sensorPulso
        sensorPulso2 = true;
      }
      if (sensorPulso2) { // COMPROBAR SI ES 15 DEL SENSOR DE PULSO
        if (val2 == 'H') { // 72
          esH2 = true;
        }
        if (esH2 && val2!='H' && val2!= ',') {
          valPulso2 = val2;

          OscMessage myMessage = new OscMessage("/pulse");
          myMessage.add(numSerial);
          myMessage.add(val2);
          oscP5.send(myMessage, puerto7000);
          oscP5.send(myMessage, puerto57120);
        } else {
          valPulso2 = 0;
        }
      }

      if (val2 == 'B') { // 66 sensorGSR
        sensorGSR2 = true;
      }
      if (sensorGSR2) { 
        if (val2 == 'I') {
          esI2 = true;
        }

        if (esI2 && val2 != 'I' && val2 != ',') {
          //println(val);
          if (val2<255-thressGSR) {
            valGSR2 = val2;

            OscMessage myMessage = new OscMessage("/gsr");
            myMessage.add(numSerial);
            myMessage.add(valGSR2);
            oscP5.send(myMessage, puerto7000);
            oscP5.send(myMessage, puerto57120);
          }
        }
      }
      if (val2 == ',' && sensorPulso2) {
        sensorPulso2 = false;
        esH2 = false;
      }
      if (val2 == ',' && sensorGSR2) {
        sensorGSR2 = false;
        esI2 = false;
      }
    }
    if ( myPort2.available() > 100) {
      myPort2.clear();
    }

    posGSRy2 = valGSR2; 

    strokeWeight(1);
    if (pX%width != 0) {
      stroke(255, 0, 0);
      line(posX+pX, posY+100+valPulso2, posX+ppX_2, posY+100+ppY2_2);

      stroke(255);
      line(posX+pX, posY+250+posGSRy2, posX+ppX_2, posY+250+ppY_2);
    } else  
    background(0, 20);
  }

  ppX_1 = pX; 
  ppY_1 = posGSRy1;  
  ppY2_1 = valPulso1;

  ppX_2 = pX; 
  ppY_2 = posGSRy2;  
  ppY2_2 = valPulso2;
}
public void exit() {
  myPort.clear(); 
  myPort.stop();
}

public void keyPressed() {
  if (key == 'd')
    debug =! debug;
}
  public void settings() {  size(400, 900); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "P5_readSerial_BT_OSCsend" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
