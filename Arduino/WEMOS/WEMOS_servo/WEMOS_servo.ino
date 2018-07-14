#include <Servo.h>

Servo servoRotate;
Servo servoScan;

int servoRotatePosition = 0;
int servoScanPosition = 0;

int servoRotateDirection = 1;
int servoScanDirection = 1;


void setup() {
  // put your setup code here, to run once:
 servoRotate.attach(14);  //Servo making the pan movement D5
 servoScan.attach(12);    //Servo making the tilt movement D6

  //Moving to initial position
  servoRotate.write(servoRotatePosition);
  servoScan.write(servoScanPosition);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
   //Limit to only one scan, for more the program (or the arduino) must be restarted
  if (servoScanPosition <= 180)
  {

    servoRotate.write(servoRotatePosition);
    servoScan.write(servoScanPosition);

     //Making the pan servo move both ways
    if (servoRotateDirection == 1)
      servoRotatePosition++;
    else
      servoRotatePosition--;

    if (servoRotatePosition == 180 || servoRotatePosition == 0)
    {
      servoRotateDirection = -servoRotateDirection;
      servoScanPosition++;
    }  
  
    //Delay to allow servos moving and sensor reading  
    delay(20);
  }

}
