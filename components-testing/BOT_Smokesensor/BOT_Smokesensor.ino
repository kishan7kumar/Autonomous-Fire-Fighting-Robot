int smokeA0 = A1;
//int sensorThreshold = 200;

void setup() 
{
   pinMode(smokeA0, INPUT);
   Serial.begin(9600);
}

void loop() 
{
  int analogSensor = analogRead(smokeA0);
  Serial.print("sensor value : ");
  Serial.println(analogSensor);
  delay(100);
}

