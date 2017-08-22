int x = 1;
int y = 0;
int button_A = 5;
int button_B = 3;
int button_C = 4;
int LED = 13;
bool izq, der, arr, aba;
bool boton[3];
bool rotar;
bool envia[7];

void setup()
{
  int i;
  for (i = 3; i <= 5; i++)
    pinMode(i, INPUT);

  for (int j = 0; j < 7; j++) {
    envia[j] = true;
  }
  for (int j = 0; j < 3; j++) {
    boton[j] = false;
  }
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int val;
  while (1)
  {
    val = analogRead(x); //Read Analog input
    //IZQUIERDA
    if (val > 1000) {
      izq = true;
    } else {
      izq = false;
    }
    //DERECHA
    if (val < 20)
      der = true;
    else {
      der = false;
    }

    if (izq && envia[0]) {
      Serial.println("I");
      envia[0] = false;
    }
    if (der && envia[1]) {
      Serial.println("D");
      envia[1] = false;
    }

    if (!izq && !envia[0])
      envia[0] = true;
    if (!der && !envia[1])
      envia[1] = true;


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
    if (arr && envia[2]) {
      Serial.println("A");
      envia[2] = false;
    }
    if (aba && envia[3]) {
      Serial.println("a");
      envia[3] = false;
    }

    if (!arr && !envia[2])
      envia[2] = true;
    if (!aba && !envia[3])
      envia[3] = true;


    /////// BOTONES
    if (digitalRead(button_A) == 0) {
      boton[0] = true;
    } else {
      boton[0] = false;
    }
    if (digitalRead(button_B) == 0) {
      boton[1] = true;
    } else {
      boton[1] = false;
    }
    if (digitalRead(button_C) == 0) {
      boton[2] = true;
    } else {
      boton[2] = false;
    }

    if (boton[0] && envia[4]) //Check Button A
    {
      Serial.println("1");
      envia[4] = false;
    }

    if (boton[1] && envia[5]) //Check Button B
    {
      Serial.println("2");
      envia[5] = false;
    }
    if (boton[2] && envia[6]) //Check Button C
    {
      Serial.println("3");
      rotar = true;
      envia[6] = false;
    }
    else {
      rotar = false;
    }
    for (int j = 0; j < 3; j++) {
      if (!boton[j] && !envia[j + 4]) {
        envia[j + 4] = true;
      }
    }
  }

  delay(100);
  /*
    // Send some message when I receive an 'A' or a 'Z'.
    switch (Serial.read())
    {
      case 'A':
        Serial.println("That's the first letter of the abecedarium.");
        break;
      case 'Z':
        Serial.println("That's the last letter of the abecedarium.");
        break;
    }
  */
}
