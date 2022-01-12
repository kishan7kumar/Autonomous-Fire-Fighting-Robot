

int ledpin = 7;
void setup() 
{
  
  pinMode(ledpin, OUTPUT);
}


void loop() 
{
  digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);                       // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
