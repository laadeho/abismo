void emularSensores() {
  emulaOnda("/alpha", 1, 0.00015);
  emulaOnda("/beta", 1, 0.00031);
  emulaOnda("/gamma", 1, 0.0008);
  emulaOnda("/delta", 1, 0.0001);
  emulaOnda("/theta", 1, 0.00022);
  emulaOnda("/alpha", 2, 0.00025);
  emulaOnda("/beta", 2, 0.00038);
  emulaOnda("/gamma", 2, 0.00032);
  emulaOnda("/delta", 2, 0.00025);
  emulaOnda("/theta", 2, 0.00028);
}

void emulaOnda(String etiqueta, int sensor, float multi) {
  OscMessage myMessage = new OscMessage(etiqueta);
  myMessage.add(sensor);
  myMessage.add(noise(millis()*multi));
  oscP5.send(myMessage, puerto7000);
  oscP5.send(myMessage, puerto57120);
}