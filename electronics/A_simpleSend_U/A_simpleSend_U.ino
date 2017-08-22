int count;
void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
 }
 
 void loop() {
   // put your main code here, to run repeatedly:
   count = count +1;
   if(count == 10000)
     count = 0;
   Serial.print("Teste: ");
   Serial.println(count);
   delay(1000);
 }

