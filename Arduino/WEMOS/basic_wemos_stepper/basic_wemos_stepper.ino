void setup() {
  // put your setup code here, to run once:
  pinMode(D4,OUTPUT);  //step
  pinMode(D2,OUTPUT);  //dir
  digitalWrite(D2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int x=0;x<4;x++)
  {
    for(int y=0;y<50;y++)
    {
      digitalWrite(D4,HIGH);
      delay(50);
      digitalWrite(D4,LOW);
      delay(50);  
    }  
  }
}
