
int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5;
int thLED_SCK_pin = 6;
#include<thLed.h>

int button1_pin = 9;
int button2_pin = 8;

#include <thButton.h>
thButton button1(button1_pin); 
thButton button2(button2_pin); 


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
   thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);
}

int trangthaitruoc=1;
int trangthaiht;
int dem=0;
// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
// trangthaiht=digitalRead(nutnhan);
 //Serial.println(trangthaiht);
 //Serial.println(dem);
 if(trangthaiht!=trangthaitruoc)
 {
  if(trangthaiht==1)
  {
  dem+=1;
  }
  trangthaitruoc=trangthaiht;
 }
 if((dem%2)==1)
 {
  for(int i = 0;i <= 7;i++){
      thLed.setLed(i,LED_ON);
    }
 }
 else
 {
  for(int i = 7;i >= 0;i--){
      thLed.setLed(i,LED_ON);
    }
 }
}
