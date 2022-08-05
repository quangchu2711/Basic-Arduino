// Kết nối Arduino với thRTC:
//    Arduino pin        thRTC pin
//       A4        ---     SDA
//       A5        ---     SCL
//       VCC       ---     VCC
//       GND       ---     GND

#include <Wire.h>
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time/archive/master.zip
#include <DS1307RTC.h>  // https://github.com/PaulStoffregen/DS1307RTC/archive/master.zip

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;


void setup()
{
  Serial.begin(9600);
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

byte NUM_2[4] = {0x00, 0x00, 0x00, 0x00};
void num_Two(int index, int val)
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

void dots_High(int index)
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

void dots_Low(int index)
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

int Phut()
{
   tmElements_t  currentTime;
   RTC.read(currentTime);
   int phut = currentTime.Minute;
   return phut;
}

int Giay()
{
   tmElements_t  currentTime;
   RTC.read(currentTime);
   int giay = currentTime.Second;
   giay -= 10;
   if(giay < 0) return( giay = 60 - abs(giay));
   else return giay;
}

void loop() 
{
    tmElements_t  currentTime;
    RTC.read(currentTime);  // đọc dữ liệu từ RTC
//  int phut = currentTime.Minute;
//  Serial.print(phut);
//  Serial.print(" / ");
//  int giay = currentTime.Second;
//  Serial.println(giay - 10);
//  delay(1000);
  for(int phut = Phut(); phut <= 59; phut++)
  {
    num_Two(2, phut);
    for(int giay = Giay(); giay <= 59; giay++)
    {
      num_Two(0, giay);
      dots_High(2);
      delay(500);
      dots_Low(2);
      delay(500);
    }
  }
}
