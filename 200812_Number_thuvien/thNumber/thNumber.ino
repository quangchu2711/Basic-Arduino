#include<thNumber.h>

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

int ChuQ = SEG7_A | SEG7_B | SEG7_C | SEG7_D | SEG7_E | SEG7_F;
int ChuU = SEG7_B | SEG7_C | SEG7_D | SEG7_E | SEG7_F;
int ChuA = SEG7_A | SEG7_B | SEG7_C | SEG7_G | SEG7_E | SEG7_F;
int ChuN = SEG7_A | SEG7_B | SEG7_C | SEG7_E | SEG7_F;
int ChuT = SEG7_A | SEG7_B | SEG7_C;

int so1 = SEG7_B | SEG7_C ;
int so2 = SEG7_A | SEG7_B | SEG7_D | SEG7_E | SEG7_G;
int so0 = SEG7_A | SEG7_B | SEG7_C | SEG7_D | SEG7_E | SEG7_F;
int so8 = SEG7_A | SEG7_B | SEG7_C | SEG7_D | SEG7_E | SEG7_F;

void setup() {
  // put your setup code here, to run once:
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
//  thNumber.setBitmap(3, ChuQ);
//  thNumber.setBitmap(2, ChuU);
//  thNumber.setBitmap(1, ChuA);
//  thNumber.setBitmap(0, ChuT);
//    thNumber.setBitmap(3, SEG7_DP);
//    thNumber.setBitmap(2, 0b01000000);
//    thNumber.setBitmap(1, 1 << 6);
//    thNumber.setDigit(3, 1);
//    thNumber.setDigit(2, 2);
//    thNumber.setDigit(1, 0);
//    thNumber.setDigit(0, 8);
    thNumber.setNum2(2, 12);
    thNumber.setNum2(0, 8);
}
