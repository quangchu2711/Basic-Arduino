int led5 = 10;
int led3 = 11;

void setup() 
{
  pinMode(led5, OUTPUT);
}

void loop() 
{
  analogWrite(led3, 50);
  delay(200);
  digitalWrite(led5,HIGH);
  delay(20);
}
