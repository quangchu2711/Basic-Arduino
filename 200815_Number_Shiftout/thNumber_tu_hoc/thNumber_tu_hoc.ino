                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                #include<thNumber.h>
#include<thButton.h>

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

int button0_pin = 10;
int button2_pin = 5;
thButton button0(button0_pin); 
thButton button2(button2_pin); 

void setup()
{
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  Serial.begin(9600);
}

int ChuL = SEG7_D | SEG7_E | SEG7_F ;
int ChuO = SEG7_A | SEG7_F | SEG7_E | SEG7_D | SEG7_B | SEG7_C;
int ChuE = SEG7_A | SEG7_F |SEG7_G |SEG7_E |SEG7_D ;
int ChuV = SEG7_F | SEG7_E |SEG7_D |SEG7_C |SEG7_B ;
int ChuE1 = SEG7_A | SEG7_F |SEG7_G |SEG7_E |SEG7_D ;
int ChuE2 = SEG7_G | SEG7_D | SEG7_A;
int ChuM1 = SEG7_E | SEG7_F | SEG7_A;
int ChuM2 = SEG7_C | SEG7_B | SEG7_A;

void Hieuung1()
{
  thNumber.setBitmap(3, ChuL);
  thNumber.setBitmap(2, ChuO);
  thNumber.setBitmap(1, ChuV);
  thNumber.setBitmap(0, ChuE);
  delay(200);
  thNumber.setBitmap(3, 0x00);
  thNumber.setBitmap(2, 0x00);
  thNumber.setBitmap(1, 0x00);
  thNumber.setBitmap(0, 0x00);
  delay(200);
}

void Hieuung2()
{
  for(int i = 0; i <= 3; i++)
  {
    thNumber.setBitmap(i, ChuL);
    delay(500);
    thNumber.setBitmap(i, 0x00);
  }
  thNumber.setBitmap(3, ChuL);
  
  for(int i = 0; i <= 2; i++)
  {
    thNumber.setBitmap(i, ChuO);
    delay(500);
    thNumber.setBitmap(i, 0x00);
  }
  thNumber.setBitmap(2, ChuO);

  for(int i = 0; i <= 1; i++)
  {
    thNumber.setBitmap(i, ChuV);
    delay(500);
    thNumber.setBitmap(i, 0x00);
  }
  thNumber.setBitmap(1, ChuV);
  delay(500);
  
  thNumber.setBitmap(0, ChuE);
  delay(500);
  thNumber.setBitmap(0, 0x00);

  for(int i = 0; i <= 3; i++)
  {
    thNumber.setBitmap(i, 0x00);
  }
  delay(500);
}

void Hieuung3()
{
  thNumber.setBitmap(2, ChuE);
  thNumber.setBitmap(1, ChuM1);
  thNumber.setBitmap(0, ChuM2);
  delay(300);
  thNumber.setBitmap(3, 0x00);
  thNumber.setBitmap(2, 0x00);
  thNumber.setBitmap(1, 0x00);
  thNumber.setBitmap(0, 0x00);
  delay(300);
}

void loop()
{
  Hieuung2();
  Hieuung1();
  Hieuung3();
  Hieuung3();
}
