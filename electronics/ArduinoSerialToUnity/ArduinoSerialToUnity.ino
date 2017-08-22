
int x = 1;
int y = 0;
int button_A = 5;
int button_B = 3;
int button_C = 4;
int LED = 13;
bool izq, der, arr, aba;
bool rotar;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  int i;
  for (i = 3; i <= 5; i++)
    pinMode(i, INPUT);

  pinMode(LED, OUTPUT);

}

void loop () {
  //if (Serial.available() > 0)
  //sCmd.readSerial();

  int val;
  while (1)
  {
    val = analogRead(x); //Read Analog input
    //IZQUIERDA
    if (val > 1000)
      izq = true;
    else
      izq = false;
    //DERECHA
    if (val < 20)
      der = true;
    else
      der = false;

    if (izq) {
      Serial.println("IZQUIERDA");
    }
    if (der) {
      Serial.println("DERECHA");
    }

    val = analogRead(y);
    //ARRIBA
    if (val > 1000)
      aba = true;
    else
      aba = false;
    //ABAJO
    if (val < 20)
      arr = true;
    else
      arr = false;
    if (arr) {
      Serial.println("ARRIBA");
    }
    if (aba) {
      Serial.println("ABAJO");
    }

    if (digitalRead(button_A) == 0) //Check Button A
    {
      digitalWrite(LED, HIGH);   // Set LED on
      Serial.println("BOTON A");
    }
    else digitalWrite(LED, LOW);
    if (digitalRead(button_B) == 0) //Check Button B
    {
      Serial.println("Boton B");
      digitalWrite(LED, HIGH);    // Set LED Off
    }
    else digitalWrite(LED, LOW);
    if (digitalRead(button_C) == 0) //Check Button C
    {
      Serial.println("Boton C");
      rotar = true;

      digitalWrite(LED, HIGH);    // Set LED off
    }
    else {
      digitalWrite(LED, LOW);
      rotar = false;
    }
  }

}
/*
  void pingHandler (const char *command) {
  Serial.println("PONG");
  }

  void echoHandler () {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL)
    Serial.println(arg);
  else
    Serial.println("nothing to echo");
  }*/
