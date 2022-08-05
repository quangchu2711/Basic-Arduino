// Kết nối Arduino với thLed:
//    Arduino pin       thLed pin
//       4        ---     SDI
//       5        ---     RCK
//       6        ---     SCK
//       VCC      ---     V3
//       GND      ---     GND

int thLED_SDI_pin = 6;  
int thLED_RCK_pin = 4;  
int thLED_SCK_pin = 5; 

#include <thLed.h>


// Hàm setup() chạy một lần:
void setup()
{ 
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);  // cài đặt thLed
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  int t = 3;
  for(int i = 4 ;i <= 7;i++){
    thLed.setLed(i,LED_ON);
    thLed.setLed(t,LED_ON);
    delay(100);
    t--;
  }
  int e = 3;
  for(int i = 4 ;i <= 7;i++){
    thLed.setLed(i,LED_OFF);
    thLed.setLed(e,LED_OFF);
    delay(100);
    e--;
  }
}
