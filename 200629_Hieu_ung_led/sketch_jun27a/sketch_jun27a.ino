//Ket noi Arduino voi cam bien anh sang:
//Arduino pin   thLight pin
//A3   out
//VCC  V3
//GND  GND
int light_senor_pin = A3;
int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5;
int thLED_SCK_pin = 6;
#include<thLed.h>

void setup() {
  Serial.begin(9600);
  pinMode(light_senor_pin,INPUT);//Cau hinh INPUT de doc gia tri cam bien
  thLed.begin(thLED_SDI_pin,thLED_SCK_pin,thLED_RCK_pin);
}

void loop() {
  int light_value = analogRead(light_senor_pin); // doc gia tri cam bien anh sang
  Serial.println(light_value);
  if(light_value >= 700){
     for(int i = 0;i <= 7;i++){
       thLed.setLed(i,LED_ON);
       delay(100);
    }
    for(int i = 0;i <= 7;i++){
       thLed.setLed(i,LED_OFF);
       delay(100);
    }
  }
  else if(light_value <= 500){
     for(int i = 0;i <= 7;i++){
         thLed.setLed(i,LED_OFF);
    }
  }else{
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
