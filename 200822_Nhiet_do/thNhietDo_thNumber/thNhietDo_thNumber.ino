// Kết nối Arduino với cảm biến nhiệt độ:
//    Arduino pin        thTemp pin
//       2         ---     OUT
//       VCC       ---     VCC
//       GND       ---     GND
int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;

int temperature_pin = 2;

#include <OneWire.h>            // https://github.com/PaulStoffregen/OneWire/archive/master.zip
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library/archive/master.zip

OneWire  oneWire(temperature_pin);
DallasTemperature  sensors(&oneWire);


// Hàm setup() chạy một lần:
void setup()
{
  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_RCK, OUTPUT);
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  sensors.begin();  // cài đặt cảm biến nhiệt độ
}

byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};
void shift_out(byte data)
{
  for(int i = 0; i <= 7; i++)
  {
    digitalWrite(pin_SDI , !((data & 128) != 0));
    data = data << 1;
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

void Display(int value)
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
  Array[1] = Array[1] | _BV(6);
  for(int i = 0; i <= 3; i++)
  {
    shift_out(Array[i]); 
  }
  digitalWrite(pin_RCK,HIGH); //Chan RCk hoat dong
  digitalWrite(pin_RCK,LOW); //Chan OE hoat dong
}

void hien_thi()
{
  sensors.requestTemperatures();                   // kích hoạt cảm biến nhiệt độ
  float temp = sensors.getTempCByIndex(0);  // đọc giá trị nhiệt độ (C)
  Serial.println(temp);                     // in kết quả ra màn hình
  delay(250);                                      // thời gian trễ giữa mỗi lần đọc
  int kq = (int) (temp * 100);
  Display(kq);
}

void loop()
{ 
  hien_thi();
//  sensors.requestTemperatures();                   // kích hoạt cảm biến nhiệt độ
//  float temperature = sensors.getTempCByIndex(0);  // đọc giá trị nhiệt độ (C)
//  Serial.println(temperature);                     // in kết quả ra màn hình
//  delay(250);                                      // thời gian trễ giữa mỗi lần đọc
}
