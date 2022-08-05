/*Chân của thNUmbeu*/
int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;

/*Chân của Knob*/
int knob_sensor_pin = A3;

/*Chân của Buzzer*/
int buzzer_pin = A0;

/*Chân của SRF05*/
int TRIGGER_PIN = 10;
int ECHO_PIN    = 11;
#include <NewPing.h>  // https://bitbucket.org/teckel12/arduino-new-ping/downloads/NewPing_v1.8.zip
NewPing srf05(TRIGGER_PIN, ECHO_PIN);  // Cấu hình các pin

void setup() 
{
  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT); 
  pinMode(pin_RCK, OUTPUT);
  
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến

  pinMode(buzzer_pin, OUTPUT);  // cài đặt OUTPUT điều khiển buzzer
 
}

byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};

void shift_out(byte val)
{
  for (int i = 0; i <= 7; i++)
  {
    digitalWrite(pin_SDI, !((val & 128) != 0));
    val = val << 1; 
    digitalWrite(pin_SCK, HIGH);
    digitalWrite(pin_SCK, LOW);
  }
}

void Num(int value)
{
  int val = abs(value);
  byte Array[4] = {0x00, 0x00, 0x00, 0x00};
  int dem = 3;
  while(val > 0)
  {
    Array[dem] = so[val % 10];
    val = val / 10; 
    dem--;
  }
  if(value == 0) Array[dem] = so[0];
  if(value < 0) Array[dem] = _BV(0);
  for(int i = 0; i <= 3; i++)
  {
    shift_out(Array[i]); 
  }
  digitalWrite(pin_RCK,HIGH); //Chan RCk hoat dong
  digitalWrite(pin_RCK,LOW); //Chan OE hoat dong
}
 
int set_threshold(int knob_value)
{
  int threshold;
  if(knob_value <= 300 && knob_value >= 0) threshold = 50;
  else if(knob_value <= 500 && knob_value > 300) threshold = 100;
  else if(knob_value <= 800 && knob_value > 500) threshold = 150;
  else if(knob_value > 800) threshold = 200;
  return threshold;
}

void loop() 
{
  int distance_cm = srf05.ping_cm();
  Num(distance_cm);
  int knob_value = analogRead(knob_sensor_pin); 
  Serial.print(knob_value);
  Serial.print("-");
  Serial.print(set_threshold(knob_value));
  Serial.print("-");
  Serial.print(distance_cm);  
  Serial.println();
  if(distance_cm < set_threshold(knob_value))
  {
    tone(buzzer_pin, 2000);  
  }
  else noTone(buzzer_pin);
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}
