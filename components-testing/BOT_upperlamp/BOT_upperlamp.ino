

int ledpina = 6;
int ledpinb = 5;
void setup() 
{
  
  pinMode(ledpina, OUTPUT);
  pinMode(ledpinb, OUTPUT);
}


void loop() 
{
  digitalWrite(ledpina, HIGH);
  delay(100);
  digitalWrite(ledpina, LOW);
  delay(100);
  digitalWrite(ledpinb, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(ledpinb, LOW);
  delay(100);
  //digitalWrite(ledpina, LOW); ;    // turn the LED off by making the voltage LOW
  //delay(1000);                       // wait for a second
}
