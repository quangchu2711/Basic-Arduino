#include<thNumber.h>
int SDI_pin = 9;
int SCK_pin = 8;
int RCK_pin = 7;

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

byte DigitFont[10] = {
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void my_shiftOut(byte val) {
  uint32_t i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void loop()
{
  my_shiftOut(3);
}
