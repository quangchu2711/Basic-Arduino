int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;


int button0_pin = 11;
int button1_pin = 6;
int button2_pin = 5;
int button3_pin = 4;
int button4_pin = 10;

#include <thButton.h>
thButton button0(button0_pin);
thButton button1(button1_pin);
thButton button2(button2_pin);
thButton button3(button3_pin); 
thButton button4(button4_pin); 

void setup() 
{
  pinMode(SDI_pin, OUTPUT);
  pinMode(SCK_pin, OUTPUT);
  pinMode(RCK_pin, OUTPUT);
}

void shift_out(byte data)
{
  for(int i = 0; i <= 7; i++)
  {
    digitalWrite(SDI_pin, !((data & 128) != 0) );
    data = data << 1;
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);
  }
}

byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};
void Num(int value)
{
  int val = abs(value);
  byte Array[4] = {0x00, 0x00, 0x00, 0x00};
  int dem = 3;
  while(val > 0)
  {
    Array[dem] = so[val % 10];
    val = val / 10;
    dem--;
  }
  if(value == 0) Array[3] = so[0];
  if(value < 0) Array[dem] = _BV(0);
  for(int i = 0; i <= 3; i++)
  {
    shift_out(Array[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

int start = 0;
void loop() 
{
  if(button0.onPress())
  {
    while(1)
    {
      for(int i = start; i <= 100; i++)
      {
        Num(i);
        if(button0.onPress()) return;
        start++;
        delay(200);   
      }
      if(start > 100) start = 0;
    }
  }
  if(button1.onPress())
  {
    if(start > 100) start = 0;
    start++;
    Num(start);
    delay(100);
  }
  else if(button2.onPress())
  {
    if(start > 100) start = 0;
    start--;
    Num(start);
    delay(100);
  }
}
