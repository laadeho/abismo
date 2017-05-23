import processing.serial.*;

Serial BT01; // Conexion a bluetooth
int serialCount = 0;
int xpos, ypos; 

void setup() {
  size(256, 256);
  noStroke();

  xpos = width/2;
  ypos = height/2;

  printArray(Serial.list());

  String portName = Serial.list()[3];
  BT01 = new Serial(this, portName, 9600);
}

void draw() {
  background(0);
  fill(255);

  ellipse(xpos, ypos, 20, 20);
}

void serialEvent(Serial myPort) {

  int inByte = myPort.read();
  println(inByte);
  xpos = inByte;
  myPort.clear();
}