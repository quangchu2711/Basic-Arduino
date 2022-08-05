int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

int button0_pin = 11;
int button2_pin = 5;
int button4_pin = 10;

#include <thButton.h>
thButton button0(button0_pin);
thButton button2(button2_pin); 
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

//Button0 la Dung;
//Button2 la Tang;
//Button4 la Giam;
int val = 0; //Gia tri led sang
int kt1 = 0; // Khoi tao cac trang thai cua nut bam
int kt2 = 0;

void Kiem_tra_nut_bam()
{
  if(button0.onPress()) kt1 = 0;
  else if(button2.onPress())
  {
    kt1 = 1;
    kt2 = 1;
  }
  else if(button4.onPress())
  {
    kt1 = 1;
    kt2 = 0;
  }
}

void Nut_bam()
{
  Kiem_tra_nut_bam();
  if(kt1 == 0)
  {
    Num(val);
    return;
  }
  if(kt1 == 1 && kt2 == 1)
  {
    if(val > 9999)
    {
      val = 0;
      Num(val);
    }
     val++;
  }
  if(kt1 == 1 && kt2 == 0)
  {
    if(val < -999)
    {
      val = 0;
      Num(val);
    }
    val--;
  }
  Num(val);
  delay(10);
}

void loop() 
{
  Nut_bam();
}
