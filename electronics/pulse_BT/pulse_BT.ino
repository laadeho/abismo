#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX, TX
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx

int pinSensorPulso = 0;
int pinLed = 13;

int Signal;
int Threshold = 550;

int pulso = 0;
boolean escribe = true;

void setup() {
  pinMode(pinLed, OUTPUT);
  BTserial.begin(9600);
}

void loop() {
  Signal = analogRead(pinSensorPulso);

  Serial.println(Signal);

  if (Signal > Threshold) {
    digitalWrite(pinLed, HIGH);
    pulso = 1;
    if (escribe) {
      BTserial.write(pulso);
    }
  } else {
    digitalWrite(pinLed, LOW);
    pulso = 0;
    if (escribe) {
      BTserial.write(pulso);
    }
  }
  delay(10);
}
