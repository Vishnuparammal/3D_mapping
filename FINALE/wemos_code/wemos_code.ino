/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 28 May 2015
 by Michael C. Miller
 modified 8 Nov 2013
 by Scott Fitzgerald

 http://arduino.cc/en/Tutorial/Sweep
*/ 
 #include<SoftwareSerial.h>// soft serial port header file
SoftwareSerial Serial2(0,2); // define the soft serial port as Serial2, D3 as RX, and D4 as TX
/*For Arduino board with multiple serial ports such as DUE board, comment out the above two codes, and directly use Serial2 port*/
#include <Servo.h> 

 
Servo myservo;  // create servo object to control a servo 
Servo yourservo;                // twelve servo objects can be created on most boards
 
int pos;
int j=0;

uint16_t dist;// LiDAR actually measured distance value
uint16_t strength;// LiDAR signal strength
uint16_t check;// check numerical value storage
int i;
byte uart[9];// store data measured by LiDAR
byte HEADER=0x59;// data package frame header

void setup() 
{ 
  myservo.attach(13);  // attaches the servo on GIO2 to the servo object 
  yourservo.attach(12);
  Serial.begin(115200);//set the Baud rate of Arduino and computer serial port
  Serial2.begin(115200);//set the Baud rate of LiDAR and Arduino serial port
 
} 
 
void loop() 
{ 
  
  yourservo.write(j);
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);            // tell servo to go to position in variable 'pos' 
    delay(3);                      // waits 3ms for the servo to reach the position 
     if (Serial2.available())//check whether the serial port has data input
  {
            delay(1);
            uart[0] = Serial2.read();
 
    if(uart[0]==HEADER)// determine data package frame header 0x59
    {
              uart[1] = Serial2.read();
      
      if(uart[1]==HEADER)//determine data package frame header 0x59
      {
        for(i=2;i<9;i++)// store data to array
        {
          uart[i]=Serial2.read();
        }
      check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
      if(uart[8]==(check&0xff))// check the received data as per protocols (comment this line if code doesnt work)
      {
        dist = 0;
        dist = dist | uart[3];
        dist = dist<<8;
        dist = dist | uart[2];

        if(pos<10)
          Serial.print("00");
        else if(pos<100)
          Serial.print("0");
        Serial.print(pos);
        
        if(j<10)
          Serial.print("00");
        else if(j<100)
          Serial.print("0");
        Serial.print(j);
        
        if(dist<10)
          Serial.print("000");
        else if(dist<100)
          Serial.print("00");
        else if(dist<1000)
          Serial.print("0");
        Serial.print(dist,DEC);// output LiDAR tests distance value
        Serial.print('\n');
     }
   }
  }
  }
    j++;
    yourservo.write(j);
    
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 

    delay(3);                       // waits 3ms for the servo to reach the position 
     if (Serial2.available())//check whether the serial port has data input
  {
            delay(1);
            uart[0] = Serial2.read();

    if(uart[0]==HEADER)// determine data package frame header 0x59
    {
                  uart[1] = Serial2.read();
                       
      if(uart[1]==HEADER)//determine data package frame header 0x59
      {
        for(i=2;i<9;i++)// store data to array
        {
                uart[i]=Serial2.read();
        }
      check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(check&0xff))// check the received data as per protocols (comment this line if code doesnt work)
      {
        dist = 0;
        dist = dist | uart[3];
        dist = dist<<8;
        dist = dist | uart[2];

        if(pos<10)
          Serial.print("00");
        else if(pos<100)
          Serial.print("0");
        Serial.print(pos);
        
        if(j<10)
          Serial.print("00");
        else if(j<100)
          Serial.print("0");
        Serial.print(j);
        
        if(dist<10)
          Serial.print("000");
        else if(dist<100)
          Serial.print("00");
        else if(dist<1000)
          Serial.print("0");
        Serial.print(dist,DEC);// output LiDAR tests distance value
        Serial.print('\n');
       }
     }
   }
  }
  } 
    j++;
    yourservo.write(j);
    if(j==181)
    { 
      return;
    }
  }} 

