#include<thNumber.h>
int SDI_pin = 7; //datapin
int SCK_pin = 8; //clock pin
int RCK_pin = 9; //latch pin;

void setup() {
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

byte Font[10] = {
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void shift_out(byte val) {
  uint32_t i;
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void set_Num1(int16_t value)
{
  shift_out(0x00);
  shift_out(0x00);
  shift_out(0x00);
  shift_out(Font[value]);
  digitalWrite(RCK_pin,HIGH); //Chan RCk hoat dong
  digitalWrite(RCK_pin,LOW); //Chan OE hoat dong
}

void set_Num2(int16_t value)
{
  if (value >= 0)
   {
     shift_out(0x00);
     shift_out(0x00000001);
     shift_out(Font[value / 10]);
     shift_out(Font[value % 10]);
     digitalWrite(RCK_pin,HIGH); //Chan RCk hoat dong
     digitalWrite(RCK_pin,LOW); //Chan OE hoat dong
   }
   else
   {
     shift_out(0x00);
     shift_out(0x00000001);
     shift_out(Font[value / 10]);
     shift_out(Font[value % 10]);
     digitalWrite(RCK_pin,HIGH); //Chan RCk hoat dong
     digitalWrite(RCK_pin,LOW); //Chan OE hoat dong
   }
}

void set_Num3(int16_t value)
{
   if (value >= 0)
   {
    shift_out(0x00);
    shift_out(Font[value / 100]);
    value = value % 100;
    shift_out(Font[value / 10]);
    shift_out(Font[value % 10]);
    digitalWrite(RCK_pin,HIGH); //Chan RCk hoat dong
    digitalWrite(RCK_pin,LOW); //Chan OE hoat dong
   }
   else
   {
    shift_out(0x00000001);
    shift_out(Font[value / 100]);
    value = value % 100;
    shift_out(Font[value / 10]);
    shift_out(Font[value % 10]);
    digitalWrite(RCK_pin,HIGH); //Chan RCk hoat dong
    digitalWrite(RCK_pin,LOW); //Chan OE hoat dong
   }
}

void set_Num4(int16_t value)
{
   shift_out(Font[value / 1000]);
   value = value % 1000;
   shift_out(Font[value / 100]);
   value = value % 100;
   shift_out(Font[value / 10]);
   value = value % 10;
   shift_out(Font[value]);
   digitalWrite(RCK_pin,HIGH); //Chan RCk hoat dong
   digitalWrite(RCK_pin,LOW); //Chan OE hoat dong
}

void loop()
{
  for(int i = -20; i <= 20; i++)
  {
    
  }
}
