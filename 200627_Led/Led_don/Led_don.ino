int led5 = 12;

void setup()
{
  pinMode(led5, OUTPUT);
}
 
void loop() 
{
  digitalWrite(led5, HIGH);
  delay(1000);
  digitalWrite(led5, LOW);
  delay(1000);
}
