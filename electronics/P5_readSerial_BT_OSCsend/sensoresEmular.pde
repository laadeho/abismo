void emularSensores() {
  emulaOnda("/alpha", 1, 0.00015);
  emulaOnda("/beta", 1, 0.00031);
  emulaOnda("/gamma", 1, 0.00012);
  emulaOnda("/delta", 1, 0.0001);
  emulaOnda("/theta", 1, 0.00022);
  emulaOnda("/theta", 1, 0.00022);
  emulaOndaB("/gyro", 1, 0.002, true);
  emulaOndaB("/accelerometer", 1, 0.0008, false);
  emulaOndaC("/artifacts", 1, 0.02, false);

  emulaOnda("/alpha", 2, 0.00025);
  emulaOnda("/beta", 2, 0.00038);
  emulaOnda("/gamma", 2, 0.00005);
  emulaOnda("/delta", 2, 0.00025);
  emulaOnda("/theta", 2, 0.00028);
  emulaOndaB("/gyro", 2, 0.00035, true);
  emulaOndaB("/accelerometer", 2, 0.0006, false);
  emulaOndaC("/artifacts", 2, 0.00052, false);
}

void emulaOnda(String etiqueta, int sensor, float multi) {
  OscMessage myMessage = new OscMessage(etiqueta);
  myMessage.add(sensor);
  myMessage.add(noise(millis()*multi));
  oscP5.send(myMessage, puerto7000);
  oscP5.send(myMessage, puerto57120);
}

void emulaOndaB(String etiqueta, int sensor, float multi, boolean giroCompleto) {
  double v1, v2, v3;
  v1 =  noise(millis()*multi);
  v2 =  noise(millis()*multi*.5);
  v3 =  noise(millis()*multi*.35);
  if (giroCompleto) {
    v1 *=360;
    v2 *=360;
    v3 *=360;
  } 
  OscMessage myMessage = new OscMessage(etiqueta);
  myMessage.add(sensor);
  myMessage.add(v1);
  myMessage.add(v2);
  myMessage.add(v3);
  oscP5.send(myMessage, puerto7000);
  oscP5.send(myMessage, puerto57120);
}

void emulaOndaC(String etiqueta, int sensor, float multi, boolean giroCompleto) {
  double enc = 1, blink, jawClench;
  if (frameCount%160 == 0 || frameCount%220 == 0) {
    blink = 1;
  } else
    blink = 0;

  if (frameCount%360 == 0 || frameCount%1220 == 0) {
    jawClench = 1;
  } else
    jawClench = 0;

  OscMessage myMessage = new OscMessage(etiqueta);
  myMessage.add(sensor);
  myMessage.add(enc);
  myMessage.add(blink);
  myMessage.add(jawClench);
  oscP5.send(myMessage, puerto7000);
  oscP5.send(myMessage, puerto57120);
}