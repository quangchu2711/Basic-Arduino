int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

int button1_pin = 6;
int button2_pin = 5;
int button3_pin = 4;
int button4_pin = 10;
int button0_pin = 11;
#include<thButton.h>;
thButton button0 (button0_pin);
thButton button1 (button1_pin);
thButton button2 (button2_pin);
thButton button3 (button3_pin);
thButton button4 (button4_pin);

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
    digitalWrite(SDI_pin, !((data & 128) != 0));
    data = data << 1;
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);
  }
}

byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};
void Num(int val)
{
  byte Array[4] = {0x00, 0x00, 0x00, 0x00};
  int value = abs(val);
  int dem = 3;
  while(value > 0)
  {
    Array[dem] = so[value % 10];
    value = value / 10;
    dem--;
  }
  if(val == 0) Array[dem] = so[0];
  if(val < 0) Array[dem] = _BV(0);
  for(int i = 0; i <= 3; i++)
  {
    shift_out(Array[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

byte NUM_2[4] = {0x00, 0x00, 0x00, 0x00};
void num2(int index, int val)
{
  if(index == 0)
  {
    NUM_2[2] = so[val / 10];
    NUM_2[3] = so[val % 10];
  }
  else if(index == 2)
  {
    NUM_2[0] = so[val / 10];
    NUM_2[1] = so[val % 10];
  }
  for(int i = 0; i <= 3; i++)
  {
    shift_out(NUM_2[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

void Cham_Sang(int index)
{
  if (index == 0) NUM_2[3] = NUM_2[3] | _BV(6);
  else if (index == 1) NUM_2[2] = NUM_2[2] | _BV(6);
  else if (index == 2) NUM_2[1] = NUM_2[1] | _BV(6);
  else if (index == 3) NUM_2[0] = NUM_2[0] | _BV(6);
  for(int i = 0; i <= 3; i++)
  {
    shift_out(NUM_2[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

void Cham_Tat(int index)
{
  if (index == 0) NUM_2[3] = NUM_2[3] & ~(_BV(6));
  else if (index == 1) NUM_2[2] = NUM_2[2] & ~(_BV(6));
  else if (index == 2) NUM_2[1] = NUM_2[1] & ~(_BV(6));
  else if (index == 3) NUM_2[0] = NUM_2[0] & ~(_BV(6));
  for(int i = 0; i <= 3; i++)
  {
    shift_out(NUM_2[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

int phut = 0, giay = 0;
void loop()
{
  if(button0.onPress())
  {
    while(1)
    {
      for(int i = phut; i <= 59; i++)
      {
        if(button0.onPress()) return;
        num2(2, i);
        for(int j = giay; j <= 59; j++)
        {
          if(button0.onPress()) return;
          num2(0, j);
          Cham_Sang(2);
          delay(500);
          Cham_Tat(2);
          delay(500);
          giay++;
          if(giay > 59) giay = 0;
        }
        phut++;
        if(phut > 59) phut = 0;
      }
    }
  }
  if(button1.onPress())
  {
      phut++;
      if(phut > 59) phut = 0;
      num2(2, phut);
      delay(100);
  }
  if(button2.onPress())
  {
      phut--;
      if(phut < 0) phut = 59;
      num2(2, phut);
      delay(100);
  }
  if(button3.onPress())
  {
      giay++;
      if(giay > 59) giay = 0;
      num2(0, giay);
      delay(100);
  }
  if(button4.onPress())
  {
      giay--;
      if(giay < 0) giay = 59;
      num2(0, giay);
      delay(100);
  }
}
