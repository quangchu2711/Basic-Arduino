#include<thNumber.h>
#include<thButton.h>

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

int button0_pin = 10;
int button2_pin = 5;
int button1_pin = 11;
thButton button0(button0_pin); 
thButton button2(button2_pin); 

int dem = -1;
void setup()
{
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.begin(9600);
}

void loop()
{
  if(button0.onPress())
  {
     dem++;
     Serial.println(dem);
     if(dem < 0)
    {
//      thNumber.setBitmap(3, 0b00000001);
//      thNumber.setNum3(0, abs(dem));
       if(dem >= -9 && dem <= -1)
       {
         thNumber.setBitmap(1, 0b00000001);
         thNumber.setDigit(0, abs(dem));
       }
       else if(dem >= -99 && dem <= -10)
       {
         thNumber.setBitmap(2, 0b00000001);
         thNumber.setNum2(0, abs(dem));
       }
       else if(dem >= -999 && dem <= -100)
       {
         thNumber.setBitmap(3, 0b00000001);
         thNumber.setNum3(0, abs(dem));
       }
    }
    else if(dem >= 0)
    {
      //thNumber.setBitmap(3, FONT7_0);
      //thNumber.setNum3(0, abs(dem));
      if(dem <= 9 && dem >= 1)
       {
         thNumber.setDigit(0, abs(dem));
       }
       else if(dem <= 99 && dem >= 10)
       {
         thNumber.setNum2(0, abs(dem));
       }
       else if(dem <= 999 && dem >= 100)
       {
         thNumber.setNum3(0, abs(dem));
       }
    }
  }else if(button2.onPress())
  {
    dem--;
    Serial.println(dem);
    if(dem < 0)
    {
      //thNumber.setBitmap(3, 0b00000001);
      //thNumber.setNum3(0, abs(dem));
      if(dem >= -9 && dem <= -1)
       {
         thNumber.setBitmap(1, 0b00000001);
         thNumber.setDigit(0, abs(dem));
       }
       else if(dem >= -99 && dem <= -10)
       {
         thNumber.setBitmap(2, 0b00000001);
         thNumber.setNum2(0, abs(dem));
       }
       else if(dem >= -999 && dem <= -100)
       {
         thNumber.setBitmap(3, 0b00000001);
         thNumber.setNum3(0, abs(dem));
       }
    }
    else if(dem >= 0)
    {
      //thNumber.setBitmap(3, FONT7_0);
      //thNumber.setNum3(0, abs(dem));
      if(dem <= 9 && dem >= 1)
       {
         thNumber.setDigit(0, abs(dem));
       }
       else if(dem <= 99 && dem >= 10)
       {
         thNumber.setNum2(0, abs(dem));
       }
       else if(dem <= 999 && dem >= 100)
       {
         thNumber.setNum3(0, abs(dem));
       }
    }
  }
}
