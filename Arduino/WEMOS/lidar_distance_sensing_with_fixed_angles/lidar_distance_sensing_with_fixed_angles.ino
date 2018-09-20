// CODE TO OBTAIN DISTANCE AND SIGNAL FROM LIDAR
// AND PRINT 10 DIGIT STRING WITH 2 FIXED ANGLE

// the angle is arbitrarily chosen to check if distance is being plotted
// data is sent in the form of string so that it can be read easily by the mapping software.

#include<SoftwareSerial.h>        // soft serial port header file
SoftwareSerial Serial2(0,2);      // define the soft serial port as Serial2, D1 as RX, and D2 as TX
/*For Arduino board with multiple serial ports such as DUE board, comment out the above two codes, and directly use Serial2 port*/
uint16_t dist;                    // LiDAR actually measured distance value
uint16_t strength;                // LiDAR signal strength
uint16_t check;                   // check numerical value storage
int i;
byte uart[9];                     // store data measured by LiDAR
byte HEADER=0x59;                 // data package frame header (check datasheet)

void setup()
{
  Serial.begin(115200);           //set the Baud rate of Arduino and computer serial port
  Serial2.begin(115200);          //set the Baud rate of LiDAR and Arduino serial port
}

void loop()
{
  if (Serial2.available())        //check whether the serial port has data input
  {
            delay(1);             // this delay stabilizes code
            uart[0] = Serial2.read();
            
    if(uart[0]==HEADER)           // determine data package frame header 0x59
    {
              uart[1] = Serial2.read();
              
      if(uart[1]==HEADER)//determine data package frame header 0x59
      {
        for(i=2;i<9;i++)// store data to array
        {
          uart[i]=Serial2.read();
        }
      check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
      
      if(uart[8]==(check&0xff))// check the received data as per protocols
      {
        dist = 0;
        dist = dist | uart[3];// higher bits
        dist = dist<<8;
        dist = dist | uart[2];// lower bits

        strength = 0;
        strength = strength | uart[5];// higher bits
        strength = strength<<8;
        strength = strength | uart[4];// lower bits
  
        Serial.print("039");  // arbitrary fixed angles
        Serial.print("073");
        if(dist<10)
          Serial.print("000");
        else if(dist<100)
          Serial.print("00");
        else if(dist<1000)
          Serial.print("0");
        Serial.print(dist);// output LiDAR tests distance value
        Serial.print('\n');
       }
     }
   }
 }
}
