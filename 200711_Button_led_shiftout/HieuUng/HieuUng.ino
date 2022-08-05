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


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  /*if (button1.onPress()){
    for(int i = 0;i <= 7;i++){
      thLed.setLed(i,HIGH);
      thLed.setLed(i+1,HIGH);
      delay(100);
      thLed.setLed(i,LOW);
      thLed.setLed(i+1,LOW);
  }
    for(int i = 7;i >= 0;i--){
      thLed.setLed(i,HIGH);
      thLed.setLed(i+1,HIGH);
      delay(100);
      thLed.setLed(i,LOW);
      thLed.setLed(i+1,LOW);
    }
  }*/
  if (button1.onPress()){
    int e = 4;
    for(int i = 3;i >= 0;i--){
      thLed.setLed(i,HIGH);
      thLed.setLed(e,HIGH);
      delay(100);
      e++;
    }
    int t = 4;
    for(int i = 3;i >= 0;i--){
      thLed.setLed(i,LOW);
      thLed.setLed(t,LOW);
      delay(100);
      t++;
    }
  }
}
