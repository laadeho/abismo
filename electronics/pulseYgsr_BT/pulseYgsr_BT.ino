/*
  Pulse Sensor and GSR Sensor to bluetooth
  Eduardo H Obieta
  www.laad.com.mx
  www.abismo.cc
  abismo // proximo
*/

#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX, TX
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx

//PSW 1234

//////////////////////////// GSR
#define smooth 5
int oldReading = 0;    // variable to hold the old analog value
int analogValueSmooth = 0;
int thresh = 10;
int smoothArray[smooth];

int valMin = 5, valMax = 800;

int pinSensorGSR = A0;
int pinSensorPulso = A1;

int pinLed = 5;

int Signal;
int Threshold = 650;

int pulso = 0;
boolean escribe = true;
boolean debug = true;
int cuenta = 0;
void setup() {
  pinMode(pinLed, OUTPUT);
  Serial.begin(19200); // Imprime en el puerto serial
  BTserial.begin(9600); // Imprime en el puerto BT Serial
}

void loop() {
  ///////// Pulse Sensor ///////// 15
  Signal = analogRead(pinSensorPulso);
  if (debug) {
    Serial.println(Signal);
  }

  if (Signal > Threshold) {
    digitalWrite(pinLed, HIGH);
    if (debug) {
      Serial.println("_______________________________");
    }

    if (escribe) {
      BTserial.write('B'); // imprime val = 66
      BTserial.write("1"); // imprime 49
      BTserial.write(analogRead(pinSensorPulso));
      BTserial.write(',');
    }
  } else {
    digitalWrite(pinLed, LOW);
    ///////// GSR ///////// 20

    addToArray();
    int smoothReading = findAverage();
    if (smoothReading > -1) {
      if (debug) {
        Serial.print("SIN: ");
        Serial.print(smoothReading);
        Serial.print(", MAP: ");
      }
      int diff = smoothReading - oldReading;
      //the op amp inverts, so we're flipping the numbers
      BTserial.write('A'); // imprime val = 65
      BTserial.write("2"); // imprime 50
      int mapSmoothReading = int(map(smoothReading, valMin, valMax, 0, 255));
      BTserial.write(mapSmoothReading); // Se mapea a 255 (byte)
      BTserial.write(','); // imprime 44
      if (debug) {
        Serial.println(mapSmoothReading);
      }
    }
    oldReading = smoothReading;
  }

  delay(100);
  cuenta++;
  if (cuenta > 150) {
    BTserial.overflow();
    Serial.println("//////////////////// overflow");
    cuenta = 0;
  }
}
void addToArray() {
  for (int i = smooth - 1; i >= 1; i--) {
    smoothArray[i] = smoothArray[i - 1]; //shift every num up one slot
  }
  smoothArray[0] = analogRead(pinSensorGSR);  //add latest reading into slot 5
}

//finds the average of all the values in the array
int findAverage() {
  int average = 0;
  for (int i = 0; i < smooth; i++) {
    average += smoothArray[i];
  }
  average = average / smooth;
  return average;
}

/*
  Galvanic Skin Response meter code from
  Chris Kairalla
*/
