
 #include<SoftwareSerial.h>// soft serial port header file
SoftwareSerial Serial2(5,4); // define the soft serial port as Serial2, pin2 as RX, and pin3 as TX
/*For Arduino board with multiple serial ports such as DUE board, comment out the above two codes, and directly use Serial2 port*/
uint16_t distance;// LiDAR actually measured distance value
uint16_t strength;// LiDAR signal strength
uint16_t check;// check numerical value storage
int i;
byte uart[9];// store data measured by LiDAR
byte HEADER=0x59;// data package frame header
int  theta,phi,t,m=0,n=0,x,y,z; // Theta is hor(lower), Phi is vertical(upper)


void setup()
{
  Serial.begin(115200);//set the Baud rate of Arduino and computer serial port
  Serial2.begin(115200);//set the Baud rate of LiDAR and Arduino serial port


}

//We need a string with fixed length, so zeroes are added to the distances
void printOutput(int angleRotate, int angleScan, uint16_t distance)
{
  Serial.print("T");
  if (m < 10)
    Serial.print("00");
  else if (m < 100)
    Serial.print("0");
  Serial.print(m);
  
  Serial.print("P");
  if (n < 10)
    Serial.print("00");
  else if (n < 100)
    Serial.print("0");
  Serial.print(n);
  
  Serial.print("V");
  
  if (distance < 10)
    Serial.print("000");
  else if (distance < 100)
    Serial.print("00");
  else if (distance < 1000)
    Serial.print("0");
  Serial.println(distance);
}

void loop()
{     
      if (Serial2.available())//check whether the serial port has data input
      {             
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
            distance = 0;
            distance = distance | uart[3];
            distance = distance<<8;
            distance = distance | uart[2];
            
            printOutput(m,n,distance);
                m++;
            if (m==180)       // hor 180 done
          {
            //phi=(n*1.8);
            n++;
            m=0;  
          }

          if (n==180)
          {
            n=0;  
          }
          }          
         }
       }
     }
    
        }
  



