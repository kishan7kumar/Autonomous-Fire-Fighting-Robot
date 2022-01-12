
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos;    // variable to store the servo position

void setup()
{
  myservo.attach(10);
  //serv();
  // attaches the servo on pin 9 to the servo object
}
//void serv()
//{     // drop
//  //
//  //for (pos =80; pos >= 0; pos -= 1) 
//  //{ 
//    //myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    //delay(5);                       // waits 15ms for the servo to reach the position
// //}
//}
void loop()
{  
//    for (pos = 0; pos <= 180; pos += 1) 
//    { // goes from 0 degrees to 180 degrees
////    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(5);                       // waits 15ms for the servo to reach the position
//   }

   //myservo.write(0); 
  
    delay(1000);
    myservo.write(90);   //hold 
    delay(1000);
     myservo.write(-90); 
    

}




