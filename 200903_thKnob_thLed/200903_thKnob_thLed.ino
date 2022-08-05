// Kết nối Arduino với biến trở:
//    Arduino pin       thKnob pin
//       A3        ---     VAR
//       VCC       ---     A
//       GND       ---     B

int led4 = 10;

int latchPin = 4;//RCK
int clockPin = 5;//SCK
int dataPin = 6;//SDI


int knob_sensor_pin = A3;


// Hàm setup() chạy một lần:
void setup() 
{
  pinMode(led4, OUTPUT);
  //Output 3 chân điều khiển của thLed
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
}

//Hàm shift_out của thLed

void display_Knop(int knob_value)
{
  knob_value = analogRead(knob_sensor_pin);  // đọc giá trị cảm biến
  num(knob_value);
  Serial.println(knob_value);                    // in kết quả ra màn hình
  delay(50);                                    // thời gian trễ giữa mỗi lần đọc
}

void analog_Write(int led, int val)
{
  float value = (float) (val / 256.0);
  value = round(value * 100.0) / 100.0;
  int T_HIGH = (int)(value * 1000);
  int T_LOW = 1000 - T_HIGH;
  digitalWrite(led, HIGH);
  delayMicroseconds(T_HIGH);
  digitalWrite(led, LOW);
  delayMicroseconds(T_LOW);

}

//Hàm chia khoảng hiển thị Led sáng dần
void display_Led_Knop_Number()
{
  int knob_value = analogRead(knob_sensor_pin);
  if(knob_value >= 0 && knob_value <= 127)
  {
    analogWrite(led4, 0);
  }
  else if(knob_value >= 128 && knob_value <= 255)
  {
    analog_Write(led4, 32);
  }
   else if(knob_value >= 256 && knob_value <= 383)
  {
    analog_Write(led4, 64);
  }
   else if(knob_value >= 384 && knob_value <= 511)
  {
    analog_Write(led4, 96);
  }
   else if(knob_value >= 512 && knob_value <= 639)
  {
    analog_Write(led4, 138);
  }
   else if(knob_value >= 640 && knob_value <= 767)
  {
    analog_Write(led4, 150); 
  }
   else if(knob_value >= 768 && knob_value <= 897)
  {
    analog_Write(led4, 182); 
  }
   else if(knob_value >= 896 && knob_value <= 1023)
  {
    analog_Write(led4, 255); 
  }
}
void loop() 
{
   //analog_Write(led4, 0); 
  display_Led_Knop_Number();
}
