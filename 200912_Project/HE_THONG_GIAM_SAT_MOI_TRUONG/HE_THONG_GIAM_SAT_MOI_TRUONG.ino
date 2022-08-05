int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;

int light_sensor_pin = A3;

int temperature_pin = 12;
#include <OneWire.h>            // https://github.com/PaulStoffregen/OneWire/archive/master.zip
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library/archive/master.zip
OneWire  oneWire(temperature_pin);
DallasTemperature  sensors(&oneWire);


int dht11_pin = 10;

int button0_pin = 11;
int button1_pin = 4;
int button3_pin = 5;
#include <thButton.h>
thButton button0(button0_pin);
thButton button1(button1_pin); 
thButton button3(button3_pin); 

#include <dht.h>  // https://arduino-info.wikispaces.com/file/view/DHT-lib.zip/545470280/DHT-lib.zip
dht  DHT;


void setup() {
  /**/
  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_RCK, OUTPUT);

  /**/
  pinMode(light_sensor_pin, INPUT); 

  /**/
  Serial.begin(9600);

  /**/
  sensors.begin();  // cài đặt cảm biến nhiệt độ

  /**/
  Serial.println("Humidity (%)\tTemperature (C)");
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
  Array[1] |= _BV(6);
  for(int i = 0; i <= 3; i++)
  {
    shift_out(Array[i]); 
  }
  digitalWrite(pin_RCK,HIGH); //Chan RCk hoat dong
  digitalWrite(pin_RCK,LOW); //Chan OE hoat dong
}

void num(int value)
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

void Nhiet_do()
{
  sensors.requestTemperatures();                   // kích hoạt cảm biến nhiệt độ
  float temperature = sensors.getTempCByIndex(0);  // đọc giá trị nhiệt độ (C)
  int temp = (int) (temperature * 100);
  Num(temp);   
}

void Do_am()
{
  DHT.read11(dht11_pin);  // kích hoạt cảm biến DHT11
  Num(DHT.humidity * 100); 
}

void Anh_sang()
{
  int light_value = analogRead(light_sensor_pin);  // đọc giá trị cảm biến ánh sáng
  num(light_value);
  Serial.println(light_value);  // in kết quả ra màn hình
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}

int kt1 = 0, kt2 = 0;
int check()
{
  if(button0.onPress())
  {
    kt1 = 0;
    kt2 = 1;
  }
  else if(button1.onPress())
  {
    kt1 = 1;
    kt2 = 0;
  }
  else if(button3.onPress())
  {
    kt1 = 1;
    kt2 = 1;
  }
}

void loop()
{
  check();
  if(kt1 == 0 && kt2 == 1) 
  {
    Nhiet_do();
  }
  else if(kt1 == 1 && kt2 == 0) 
  {
    Do_am();
  }
  else if(kt1 == 1 && kt2 == 1)
  {
    Anh_sang();
    delay(100);
  } 
}

//void loop()
//{
//  if(button0.onPress()) 
//  {
//    Nhiet_do();
//  }
//  else if(button1.onPress()) 
//  {
//    Do_am();
//  }
//  else if(button3.onPress())
//  {
//    Anh_sang();
//  }
//}
