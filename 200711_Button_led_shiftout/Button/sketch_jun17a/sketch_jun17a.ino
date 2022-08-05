
//int thLED_SDI_pin = 4;
//int thLED_RCK_pin = 5;
//int thLED_SCK_pin = 6;
//#include<thLed.h>
//
int button1_pin = 3;
int button2_pin = 2;

#include <thButton.h>
thButton button1(button1_pin); 
thButton button2(button2_pin); 


// Hàm setup() chạy một lần:
int dem = 0;
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(13, OUTPUT);
   //thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  if (button2.onPress() )  // nếu button1 được bấm
  {
    dem++;
  }
  if (dem % 2 == 1)  
  {
    Serial.println("SANG");
    digitalWrite(13, HIGH);
//    for(int i = 0;i <= 7;i++){
//      thLed.setLed(i,LED_ON);
//    }
  }
  if (dem % 2 == 0)  
  {
    Serial.println("TOI");
    digitalWrite(13, LOW);
//    for(int i = 0;i <= 7;i++){
//        thLed.setLed(i,LED_OFF);
//    }
  }
}
