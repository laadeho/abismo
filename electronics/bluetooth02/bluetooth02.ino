#include <SoftwareSerial.h>
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx

int valor = 0;
boolean escribe = true;

SoftwareSerial BT2(10, 11); // RX, TX
int ledpin = 13;
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  BT2.begin(9600);
  //BT2.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin, OUTPUT);
}

void loop() {

  if (escribe) {
    BT2.write(valor);
    digitalWrite(ledpin, valor);
    delay(1000);
    
    valor++;
    valor = valor % 2;
    
  } else {
    // put your main code here, to run repeatedly:
    if (BT2.available()) {
      BluetoothData = BT2.read();
      if (BluetoothData == '1') { // if number 1 pressed ....
        digitalWrite(ledpin, 1);
        BT2.println("LED  On D13 ON ! ");
      }
      if (BluetoothData == '0') { // if number 0 pressed ....
        digitalWrite(ledpin, 0);
        BT2.println("LED  On D13 Off ! ");
      }
    }
    delay(100);// prepare for next data ...
  }

}
