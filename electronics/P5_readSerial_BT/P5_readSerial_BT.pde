/*
Buscar si existe algún "flush" para cada determinado tiempo
 limpiar la cola de mensajes de los puertos seriales y así
 tener la información en tiempo real.
 */
import processing.serial.*;

Serial myPort;
Serial myPort2;

int val, val2;

void setup() 
{
  size(400, 200);
  println(Serial.list());
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
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
  println(myPort.available());
  // if ( myPort.available() > 0) {
  val = myPort.read();
  println("Val: "+val );//+", Val2: "+val2);
  //val2 = myPort2.read();
  //}
  // println(val);
  pushStyle();
  background(255);   
  if (val == 3) {   
    fill(0, 255, 0);
  } else {    
    fill(0);
  }
  
  rect(250, 50, 100, 100);
  popStyle();
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
  pushStyle();
  fill(0);
  text("Sensor V: "+val, width/2, height/2);
  fill(255);
  text("Sensor V: "+val, width/2+2, height/2+2);
  popStyle();
}