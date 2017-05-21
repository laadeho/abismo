#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX, TX
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx

//PSW 1234

int pinSensorPulso = 0;
int pinLed = 13;

int Signal;
int Threshold = 650;

int pulso = 0;
boolean escribe = true;

void setup() {
  pinMode(pinLed, OUTPUT);
  Serial.begin(19200); // Imprime en el puerto serial
  BTserial.begin(9600); // Imprime en el puerto BT Serial
}

void loop() {
  Signal = analogRead(pinSensorPulso);

  //BTserial.write('A');

  Serial.println(Signal);

  if (Signal > Threshold) {
    digitalWrite(pinLed, HIGH);
    pulso = 3;
    Serial.println("_______________________________");

    if (escribe) {
      BTserial.write(1);
      BTserial.write("15");
      BTserial.write(3);
    }
  } else {
    digitalWrite(pinLed, LOW);
    pulso = 6;
    if (escribe) {
      BTserial.write(2);
    }
  }
  delay(100);
  // Revisar si al cambiar el delay de 10 a 30 la cola de mensajes seriales no se hace tan larga
}
