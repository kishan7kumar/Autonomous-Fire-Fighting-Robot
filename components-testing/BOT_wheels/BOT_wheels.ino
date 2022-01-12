
// defining my right 3 motors 

const int in1 = 29;
const int in2 = 31;

// defining my left 3 motors
//6
//const int in1 = 7;
//const int in2 = 6;


void setup()
{
  
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
//  pinMode(in3, OUTPUT);
//  pinMode(in4, OUTPUT);
  }
 
 
 void loop()
 {
 // start
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
//turn on motor B froward direction
//digitalWrite(in3, HIGH);
// digitalWrite(in4, LOW);
 delay(7000);
 // Stop
 digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);
 
// digitalWrite(in3, LOW);
// digitalWrite(in4, LOW);
// delay(5000);

 }
 
 
 

