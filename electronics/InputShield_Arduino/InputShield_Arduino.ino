//This input shield use Digital Pin 3,4,5 (3 buttons) and Analog Pin 0,1 (JS) 
// // Upload the code to Arduino
// www.dfrobot.com
// Last modified on 24/12/2009

int x=1;
int y=0;
int button_A= 5;
int button_B= 3;
int button_C= 4;
 
void setup()
{
  int i;
  for(i=3;i<=5;i++)
  pinMode(i, INPUT);
  pinMode(LED,OUTPUT);
}

void loop()
{  
  int val;
  while(1)
  {
    val=analogRead(x); //Read Analog input 
    if(val>1000||val<20) digitalWrite(LED, HIGH);
    else digitalWrite(LED,LOW);
    val=analogRead(y);
    if(val>1000||val<20) digitalWrite(LED, HIGH);
    else digitalWrite(LED,LOW);
    
    if(digitalRead(button_A)==0)    //Check Button A
     {
         digitalWrite(LED, HIGH);   // Set LED on
     }
    else digitalWrite(LED,LOW);
    if(digitalRead(button_B)==0)   //Check Button B
     {
         digitalWrite(LED, HIGH);    // Set LED Off
     }
    else digitalWrite(LED,LOW);     
    if(digitalRead(button_C)==0)   //Check Button C
     {
         digitalWrite(LED, HIGH);    // Set LED off
     }
    else digitalWrite(LED,LOW); 
  } 
}
