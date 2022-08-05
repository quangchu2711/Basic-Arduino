int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5;
int thLED_SCK_pin = 6;
#include<thLed.h>
int light_sensor_pin = A3;

void setup() {
  thLed.begin(thLED_SDI_pin,thLED_SCK_pin,thLED_RCK_pin);
  Serial.begin(9600);
  pinMode(light_sensor_pin,INPUT);
}

void LedChanSang(){
  /*thLed.setLed(0,HIGH);
  thLed.setLed(2,HIGH);
  thLed.setLed(4,HIGH);
  thLed.setLed(6,HIGH);
  thLed.setLed(1,LOW);
  thLed.setLed(3,LOW);
  thLed.setLed(5,LOW);
  thLed.setLed(7,LOW);*/
  for(int i = 0; i < 8; i++)
  {
    if(i % 2 == 0) thLed.setLed(i,HIGH);
    else thLed.setLed(i,LOW);
  }
}

void LedLeSang(){
  /*thLed.setLed(1,HIGH);
  thLed.setLed(3,HIGH);
  thLed.setLed(5,HIGH);
  thLed.setLed(7,HIGH);
  thLed.setLed(0,LOW);
  thLed.setLed(2,LOW);
  thLed.setLed(4,LOW);
  thLed.setLed(6,LOW);*/
  for(int i = 0; i < 8; i++)
  {
    if(i % 2 == 1) thLed.setLed(i,HIGH);
    else thLed.setLed(i,LOW);
  }
}

void loop() {
  int light_value = analogRead(light_sensor_pin);
  Serial.println(light_value);
  delay(50);
  if(light_value <= 300) LedChanSang();
  else LedLeSang();
}
