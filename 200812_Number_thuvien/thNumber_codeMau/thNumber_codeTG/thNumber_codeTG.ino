#include<thNumber.h>
int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin); 
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 234; i++)
  {
    thNumber.setNum3(0, i);
    delay(1000);
  }
}
