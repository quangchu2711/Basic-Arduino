#include<thNumber.h>
#include<thButton.h>

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

int button0_pin = 11;
int button1_pin = 6;
int button2_pin = 5;
int button3_pin = 4;
int button4_pin = 10;

thButton button0(button0_pin); 
thButton button2(button2_pin);
thButton button1(button1_pin); 

void setup()
{
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

int phut = 0;
int giay = 0;
void loop()
{
//  if(button0.onPress())
//  {
//    while(1)
//    {
//      if (phut > 59) phut = 0;
//      for (int minute = phut; minute < 60; minute++)
//      {
//        if(button0.onPress()) return;
//        thNumber.setNum2(2, minute);
//        if (giay > 59) giay = 0;
//        for (int second = giay; second < 60; second++)
//        {
//           if(button0.onPress()) return;
//           thNumber.setNum2(0, second);
//           thNumber.showDot(2);
//           delay(500);
//           thNumber.hideDot(2);
//           delay(500);
//           giay++;
//        }
//        phut++;
//      }
//    }
//  }
  thNumber.setNum2(2, 45);
}
