int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5;
int thLED_SCK_pin = 6;
#include<thLed.h>
int light_sensor_pin = A3;
void setup() {
  thLed.begin(thLED_SDI_pin,thLED_SCK_pin,thLED_RCK_pin);
  Serial.begin(9600); //Khoi tao ket noi may tinh voi toc do 9600
  pinMode(light_sensor_pin,INPUT); // cau hinh INPUT de doc gia tri cam bien
}

void xu_li(int n){
  for (int i = 0; i <= n-1; i++)
  {
    thLed.setLed(i, LED_OFF); 
  }
  for (int i = n ; i <= 7; i++)
  {
    thLed.setLed(i, LED_ON); 
  }
}

/*void xuli_0(){
  thLed.setLed(0,LED_ON);
//  thLed.setLed(1,LED_OFF);
//  thLed.setLed(2,LED_OFF);
//  thLed.setLed(3,LED_OFF);
//  thLed.setLed(4,LED_OFF);
//  thLed.setLed(5,LED_OFF);
//  thLed.setLed(6,LED_OFF);
//  thLed.setLed(7,LED_OFF);
  for (int i = 1; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_1(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
//  thLed.setLed(2,LED_OFF);
//  thLed.setLed(3,LED_OFF);
//  thLed.setLed(4,LED_OFF);
//  thLed.setLed(5,LED_OFF);
//  thLed.setLed(6,LED_OFF);
//  thLed.setLed(7,LED_OFF);
  for (int i = 2; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_2(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
  thLed.setLed(2,LED_ON);
//  thLed.setLed(3,LED_OFF);
//  thLed.setLed(4,LED_OFF);
//  thLed.setLed(5,LED_OFF);
//  thLed.setLed(6,LED_OFF);
//  thLed.setLed(7,LED_OFF);
  for (int i = 3; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_3(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
  thLed.setLed(2,LED_ON);
  thLed.setLed(3,LED_ON);
//  thLed.setLed(4,LED_OFF);
//  thLed.setLed(5,LED_OFF);
//  thLed.setLed(6,LED_OFF);
//  thLed.setLed(7,LED_OFF);
  for (int i = 4; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_4(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
  thLed.setLed(2,LED_ON);
  thLed.setLed(3,LED_ON);
  thLed.setLed(4,LED_ON);
//  thLed.setLed(5,LED_OFF);
//  thLed.setLed(6,LED_OFF);
//  thLed.setLed(7,LED_OFF);
  for (int i = 5; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_5(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
  thLed.setLed(2,LED_ON);
  thLed.setLed(3,LED_ON);
  thLed.setLed(4,LED_ON);
  thLed.setLed(5,LED_ON);
//  thLed.setLed(6,LED_OFF);
//  thLed.setLed(7,LED_OFF);
  for (int i = 6; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_6(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
  thLed.setLed(2,LED_ON);
  thLed.setLed(3,LED_ON);
  thLed.setLed(4,LED_ON);
  thLed.setLed(5,LED_ON);
  thLed.setLed(6,LED_ON);
  //thLed.setLed(7,LED_OFF);
  for (int i = 7; i <= 7; i++)
  {
    thLed.setLed(i, LED_OFF);
  }
}

void xuli_7(){
  thLed.setLed(0,LED_ON);
  thLed.setLed(1,LED_ON);
  thLed.setLed(2,LED_ON);
  thLed.setLed(3,LED_ON);
  thLed.setLed(4,LED_ON);
  thLed.setLed(5,LED_ON);
  thLed.setLed(6,LED_ON);
  thLed.setLed(7,LED_ON);
}*/

void loop() 
{
  int light_value = analogRead(light_sensor_pin); // doc gia tri cam bien anh sang
  Serial.println(light_value);
  delay(50);
  if(light_value >= 900)
  {
    //xuli_7();
    xu_li(7);
  }
  else if(light_value < 900 && light_value >= 800)
  {
    //xuli_6();
    xu_li(6);
  }
  else if(light_value < 800 && light_value >= 700)
  {
    // xuli_5();
    xu_li(5);
  }
  else if(light_value < 700 && light_value >= 600)
  {
    //xuli_4();
    xu_li(4);
  }
  else if(light_value < 600 && light_value >= 500)
  {
    //xuli_3();
    xu_li(3);
  }
  else if(light_value < 500 && light_value >= 400)
  {
    //xuli_2();
    xu_li(2);
  }
  else if(light_value < 400 && light_value >= 300)
  {
    //xuli_1();
    xu_li(1);
  }
  else if(light_value < 300 && light_value >= 200)
  {
    //xuli_0();
    xu_li(0);
  }
}
