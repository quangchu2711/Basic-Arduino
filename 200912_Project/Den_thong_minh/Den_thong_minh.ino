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

int light_sensor_pin = A2;

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

int latchPin = 8;//RCK
int clockPin = 9;//SCK
int dataPin = 7;//SDI
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến

  pinMode(buzzer_pin, OUTPUT);  // cài đặt OUTPUT điều khiển buzzer
  
  pinMode(light_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
}
void my_shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
  uint8_t i;

  for (i = 0; i < 8; i++) 
  {
    if (bitOrder == MSBFIRST) {
      digitalWrite(dataPin, val & 1);
      val >>= 1;
    } else {  
      digitalWrite(dataPin, (val & 128) != 0 );
      val <<= 1;
    }
      
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);    
  }
}

byte outPut=0x00;
void set_led(int index, int state)
{
    outPut = (outPut & ~ (1 << index)); // dich bit truoc nhan xog roi dao 
    outPut = outPut | (state << index);// 
    my_shiftOut(dataPin, clockPin, LSBFIRST, outPut);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
}

void Led_HIGH()
{
  for(int i = 0; i <= 7; i++)
  {
    set_led(i, HIGH);
  }
}

void Led_LOW()
{
  for(int i = 0; i <= 7; i++)
  {
    set_led(i, LOW);
  }
}

int set_distance()
{
  int kt = 0;
  int distance_cm = srf05.ping_cm();  // đo khoảng cách (đơn vị cm)
  if(distance_cm <= 50) kt = 1;
  else kt = 0;
  return kt;
}

int set_threshold(int knob_value)
{
  int threshold;
  if(knob_value <= 200 && knob_value >= 0) threshold = 300;
  else if(knob_value <= 400 && knob_value > 200) threshold = 400;
  else if(knob_value <= 600 && knob_value > 400) threshold = 500;
  else if(knob_value > 600) threshold = 600;
  return threshold;
}

int set_thLight()
{
  int kt = 1;
  int light_value = analogRead(light_sensor_pin);
  int knob_value = analogRead(knob_sensor_pin); 
  if(light_value > set_threshold(knob_value)) kt = 1;
  else kt = 0;
  return kt;
}

void loop() 
{
  int distance_cm = srf05.ping_cm();  // đo khoảng cách (đơn vị cm)
  int light_value = analogRead(light_sensor_pin);
  int knob_value = analogRead(knob_sensor_pin); 
  Serial.print(distance_cm);
  Serial.print("-");
  Serial.print(light_value);
  Serial.print("-");
  Serial.print(set_threshold(knob_value));
  Serial.println();
  if(set_distance() == 1) Led_HIGH();
  else if(set_thLight() == 1) Led_HIGH();
  else if(set_distance() == 1 && set_distance() == 1) Led_HIGH();
  else Led_LOW();
  delay(500);
}
