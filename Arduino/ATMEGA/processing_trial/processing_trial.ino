float x=0,y=0,z=0,i=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(String(-x, 5) + " " + String(y, 5) + " " + String(-z, 5));
  x = random(0,100);
  y = random(0,100);
  z = random(0,100);
  i++;
  if(i==100)
    return;
}
