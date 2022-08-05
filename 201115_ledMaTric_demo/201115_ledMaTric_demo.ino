#include "LedControl.h"                   //Khai báo thư viện Led Control
LedControl matrix = LedControl(12, 11, 10, 4); //Khai báo chân DIN, CLK, CS, số module



const int numbyte = 40; // Số dãy Byte (1 chữ gồm 8 dãy byte = 64 bit)

void setup()
{
  
  matrix.shutdown(0, false);      //Bật hiển thị
  matrix.shutdown(1, false);      //Bật hiển thị
  matrix.shutdown(2, false);      //Bật hiển thị
  matrix.shutdown(3, false);      //Bật hiển thị
  matrix.setIntensity(0, 5);     //Đặt độ sáng lớn nhất
  matrix.setIntensity(1, 5);     //Đặt độ sáng lớn nhất
  matrix.setIntensity(2, 5);     //Đặt độ sáng lớn nhất
  matrix.setIntensity(3, 5);     //Đặt độ sáng lớn nhất
}

//Mảng chứa dữ liệu chữ
byte a[numbyte] =
{
  0x42, 0x42, 0x42, 0x5a, 0x66, 0x66, 0x42, 0x00, //M
  0x38, 0x04, 0x3c, 0x24, 0x18, 0x00, 0x00, 0x00, //e
  0x18, 0x24, 0x04, 0x24, 0x18, 0x00, 0x00, 0x00, //c
  0x14, 0x14, 0x1c, 0x04, 0x04, 0x04, 0x00, 0x00, //h
  0x38, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00  //a
};

void flash()                //Thay đổi từng chữ
{
  matrix.clearDisplay(0);   //Xóa sạch màn hình

  //Set từng chữ
  for (int i = 0 ; i + 8 <= numbyte; i += 8)  
  {
    for (int j = 0; j < 8; j++)
    {
            matrix.setRow(0, j, a[i + j]);
      matrix.setRow(1, j, a[i + j]);
      matrix.setRow(2, j, a[i + j]);

      matrix.setRow(3, j, a[i + j]);
    }
    delay(500);           //Chờ 0,5s
  }
}

void scroll()             //Chạy chữ
{
  matrix.clearDisplay(0);
  
  //Set từng hàng
  for (int i = 0 ; i + 8 <= numbyte; i++)
  {
    for (int j = 0 ; j < 8; j++)
    {
      matrix.setRow(0, j, a[i + j]);
    } 
    delay(100); // Chờ 100s
  }
}



void loop()
{
  //matrix.setRow(0, 7, 0b11111111);
  scroll();     //Chạy hàm scroll()
}
