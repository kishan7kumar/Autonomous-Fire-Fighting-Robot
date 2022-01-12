#include<SoftwareSerial.h>

int sensorPin = A0;     // select the input pin for the LDR
int sensorValue = 0;     // variable to store the value coming from the sensor

void setup() 
{  Serial.begin(9600);
}
void loop()
{
sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);
if (sensorValue < 200)
{
Serial.println("Fire Detected");
}
}


