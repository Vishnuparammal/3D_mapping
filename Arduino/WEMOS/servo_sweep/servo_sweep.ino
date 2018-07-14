#include <Servo.h> 

 
Servo myservo;  // create servo object to control a servo 
Servo yourservo;                // twelve servo objects can be created on most boards
 
int pos;
int j;


void setup() {
  // put your setup code here, to run once:
   myservo.attach(13);  // D7
  yourservo.attach(12); // D6

}

void loop() {
  // put your main code here, to run repeatedly:
  yourservo.write(j);
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  { 
    myservo.write(pos);            // tell servo to go to position in variable 'pos'   
    delay(15);
  }
  j++;
  yourservo.write(j);
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);    
  }
  j++;
  yourservo.write(j);
  if(j==180)
    return;
}
