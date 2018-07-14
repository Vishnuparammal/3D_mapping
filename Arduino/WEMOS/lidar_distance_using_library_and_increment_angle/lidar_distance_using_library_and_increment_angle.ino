#include <SoftwareSerial.h>
#include "TFMini.h"
#include <Servo.h>

Servo servoRotate;
Servo servoScan;

int servoRotatePosition = 0;
int servoScanPosition = 0;

int servoRotateDirection = 1;
int servoScanDirection = 1;

SoftwareSerial mySerial(5, 4);      // Uno RX D1 , Uno TX D2
TFMini tfmini;
int theta=0,phi=0;

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  mySerial.begin(TFMINI_BAUDRATE);
  tfmini.begin(&mySerial);
  servoRotate.attach(0);  //Servo making the pan movement D3
  servoScan.attach(2);    //Servo making the tilt movement D4
}

void loop() 
{
  uint16_t dist = tfmini.getDistance();
  if(theta<10)
    Serial.print("00");
  else if(theta<100)
    Serial.print("0");
  Serial.print(theta);
  
  if(phi<10)
    Serial.print("00");
  else if(phi<100)
    Serial.print("0");
  Serial.print(phi);
  
  if(dist<10)
    Serial.print("000");
  else if(dist<100)
    Serial.print("00");
  else if(dist<1000)
    Serial.print("0");
  Serial.print(dist);
  
  Serial.print('\n');

  if(phi%2==0)
    theta++;
  else
    theta--;
  if(theta==180||theta==0)
    phi++;
  if(phi==180)
    phi=0;
  
  delay(25);  
}

