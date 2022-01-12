//Note:- Smoke and temperature sensor are not used as the fire was small so couldn't get the minimum threshold for sensors to work. 

// FOR SERIAL COMMUNICATION
int s = 0;

//FOR SERVO MOTOR
#include <Servo.h>
Servo myservo;

// FOR FLAME SENSOR
#include <SoftwareSerial.h>

// FOR TEMPERATURE SENSOR
#include <dht.h>
dht DHT;
#define DHT11_PIN 7

// FOR WATER PUMP
const int in7 = 31; //negative of pump
const int in8 = 29; // positive of pump

// FOR DC MOTORS
// defining right 3 motors of first L298  driver
const int in1 = 33; //blue       //in3
const int in2 = 35; //grey      //in4
int enB = 8;
// defining left 3 motors of second L298 driver
const int in3 = 28; // in1
const int in4 = 32; // in2
int enA = 4;

// FOR 3 DC FANS
const int in5 = 30; //in3   for fans
const int in6 = 34; //in4   for fans

// FOR SMOKE SENSOR
int smokeA0 = A1;
//int sensorThreshold = 200;

// FOR FLAME/INFRARED SENSOR
int sensorPin = A0;	 // select the input pin for the LDR
int sensorValue = 0; // variable to store the value coming from the flame sensor

// FOR BUZZER
const int buzzer = 50;

// FOR HEAD LAMPS
const int leda = 46;
const int ledb = 48;

// FOR ULTRASONIC SENSOR
const int trigPin = 40;
const int echoPin = 42;
long duration;
int distance;

// FOR ALARM LED LIGHTS
int ledc = 6;
int ledd = 5;

void setup()
{
	Serial.begin(9600);
	myservo.attach(10);
	pinMode(smokeA0, INPUT);
	pinMode(leda, OUTPUT);
	pinMode(ledb, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(in5, OUTPUT);
	pinMode(in6, OUTPUT);
	pinMode(ledc, OUTPUT);
	pinMode(ledd, OUTPUT);
	pinMode(buzzer, OUTPUT);
	pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
	Warmup();
	myservo.write(-90); // water nozzle goes up in search position
}

void loop() 
{
again:
	left(); // rotating continuously on its place
	detectflame(); // starts to detect flame
	detectdistance(); // to avoid any obstacle
	if (sensorValue <= 400) // if robot detects flame
	{
		forward(); // move towards the flame source
		detectflame(); // keep detecting flame
		if (sensorValue <= 80) // if bot comes close enough to flame
		{
			halt(); // stop
			delay(2000);
			if (Serial.available()) // read MATLAB serial data
			{
				s = Serial.read();
				delay(3000);
				if (s == 'F') //if MATLAB confirms fire
				{
					myservo.write(90); // lower the water nozzle to fire water
					delay(1000);
					Fanon(); //turn on fans to suck in smoke
					firehere(); // sound the alarm
					delay(2000);
					Alarmoff();
					Fanoff();
				}
				else // if MATLAB not confirmes fire
				{
					back(); // go back to starting location
					delay(2000);
					goto again; //starts the searching process again
				}
			}
		}
	}

	//COLLISION PREVENTION LOGIC  HERE
	if (distance <= 20 && distance >= 3) // if bot detects any wall in front of it in 20cm distance
	{
		halt();
		delay(1000);
		back();
		delay(1000);
		halt();
		delay(1000);
	}

} 

// ************************* ALL FUNCTIONS DEFINED HERE
void detectsmoke()
{
	int analogSensor = analogRead(smokeA0);
	//Serial.print("sensor value : ");
	//Serial.println(analogSensor);
	delay(100);
}

void detectflame()
{
	sensorValue = analogRead(sensorPin);
	Serial.println(sensorValue);
}

void Alarmon()
{
	digitalWrite(ledc, HIGH);
	delay(50);
	digitalWrite(ledc, LOW);
	tone(buzzer, 1000);
	delay(50);
}

void Alarmoff()
{
	digitalWrite(ledd, HIGH); // turn the LED on (HIGH is the voltage level)
	delay(50);				 
	digitalWrite(ledd, LOW);
	noTone(buzzer);
}

void forward()
{
	analogWrite(enA, 180); // Range 100rpm to 255rpm only
	analogWrite(enB, 180);
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
}

void back()
{
	analogWrite(enA, 180); // Range 100rpm to 255rpm only
	analogWrite(enB, 180);
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
}

void left()
{
	analogWrite(enA, 170); // Range 100rpm to 255rpm only
	analogWrite(enB, 170);
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
}

void right()
{
	analogWrite(enA, 180); // Range 100rpm to 255rpm only
	analogWrite(enB, 180);
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
}

void halt()
{
	analogWrite(enA, 180); // Range 100rpm to 255rpm only
	analogWrite(enB, 180);
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void Fanon()
{
	digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
}

void Fanoff()
{
	digitalWrite(in5, LOW);
	digitalWrite(in6, LOW);
}

void Warmup()
{
	Alarmon();
	digitalWrite(ledc, HIGH);
	digitalWrite(ledd, HIGH);
	delay(100);
	digitalWrite(ledc, LOW);
	digitalWrite(ledd, LOW);
	delay(100);
	digitalWrite(ledc, LOW);
	digitalWrite(ledd, LOW);
	Alarmoff();
	digitalWrite(ledc, LOW);
	digitalWrite(ledd, LOW);
	delay(2000);
	digitalWrite(ledc, HIGH);
	digitalWrite(ledd, HIGH);
	digitalWrite(leda, HIGH); // turn the LED on (HIGH is the voltage level)
	digitalWrite(ledb, HIGH); // wait for a second
	delay(2000);
	digitalWrite(leda, LOW); // turn the LED off by making the voltage LOW
	digitalWrite(ledb, LOW);
	digitalWrite(ledc, LOW);
	digitalWrite(ledd, LOW);
	delay(1000);
}

void detectdistance()
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(10);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration * (0.034 / 2);
	//   Serial.print("Distance: ");
	//   Serial.println(distance);
}

void detecttemp()
{
	int chk = DHT.read11(DHT11_PIN);
	Serial.print("Temperature=");
	Serial.println(DHT.temperature);
	Serial.print("Humidity=");
	Serial.println(DHT.humidity);
	delay(1000);
}

void alarmlamp()
{
	digitalWrite(ledc, HIGH);
	delay(100);
	digitalWrite(ledc, LOW);
	delay(100);
	digitalWrite(ledd, HIGH); // turn the LED on (HIGH is the voltage level)
	delay(100);				  // wait for a second
	digitalWrite(ledd, LOW);
	delay(100);
}
void firehere()
{
	Alarmon();
	delay(50);
	Alarmoff();
	delay(50);
	Alarmon();
	delay(50);
	Alarmoff();
	delay(50);
}
