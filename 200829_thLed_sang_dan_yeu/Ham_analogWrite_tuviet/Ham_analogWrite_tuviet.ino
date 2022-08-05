int led5 = 10;
int led3 = 11;

void setup() 
{
  //analogWrite(led4, 50);
  pinMode(led5, OUTPUT);
}

void analog_Write(int led, int val)
{
  float value = (float) (val / 256.0);
  value = round(value * 100.0) / 100.0;
  int T_HIGH = (int)(value * 1000);
  int T_LOW = 1000 - T_HIGH;
  digitalWrite(led, HIGH);
  delayMicroseconds(T_HIGH);
  digitalWrite(led, LOW);
  delayMicroseconds(T_LOW);

}


void loop() 
{
  analogWrite(led3, 15);
  analog_Write(led5, 15);
}
