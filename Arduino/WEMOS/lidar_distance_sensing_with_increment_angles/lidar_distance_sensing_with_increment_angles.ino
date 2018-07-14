// LIDAR DISTANCE SENSING WITH ANGLE INCREMENT IN EACH LOOP

#include<SoftwareSerial.h>// soft serial port header file
SoftwareSerial Serial2(5,4); // define the soft serial port as Serial2, pin2 as RX, and pin3 as TX
/*For Arduino board with multiple serial ports such as DUE board, comment out the above two codes, and directly use Serial2 port*/
uint16_t dist;// LiDAR actually measured distance value
uint16_t strength;// LiDAR signal strength
uint16_t check;// check numerical value storage
int i;
int theta=0,phi=0;
byte uart[9];// store data measured by LiDAR
byte HEADER=0x59;// data package frame header
void setup()
{
  Serial.begin(115200);//set the Baud rate of Arduino and computer serial port
  Serial2.begin(115200);//set the Baud rate of LiDAR and Arduino serial port
}
void loop()
{
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
      
      if(uart[8]==(check&0xff))// check the received data as per protocols
      {
        dist = 0;
        dist = dist | uart[3];
        dist = dist<<8;
        dist = dist | uart[2];

        strength = 0;
        strength = strength | uart[5];
        strength = strength<<8;
        strength = strength | uart[4];
        
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
        Serial.print(dist,DEC);// output LiDAR tests distance value
        Serial.print('\n');

         if(phi%2==0)
            theta++;
          else
            theta--;
          if(theta==180||theta==0)
            phi++;
          if(phi==180)
            phi=0;
       }
     }
   }
 }
}
