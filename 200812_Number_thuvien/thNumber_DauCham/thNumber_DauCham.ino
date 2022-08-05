#include<thNumber.h>

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9; 

void setup()
{
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.begin(9600);
}

void loop()
{
//  thNumber.setDigit(3, 0);
//  thNumber.setNum3(0, 111);
//  //thNumber.showDot(3);
//  thNumber.setBitmap(3, SEG7_DP);
    thNumber.setBitmap(3, SEG7_DP);
    //thNumber.setDigit(3, 0);
    thNumber.setNum2(2, 1);
    thNumber.setNum2(0, 11);
}
