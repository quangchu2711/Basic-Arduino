// Kết nối Arduino với cảm biến DHT11:
//    Arduino pin       DHT11 pin
//       10       ---     OUT
//       VCC      ---     VCC
//       GND      ---     GND

int dht11_pin = 10;

#include <dht.h>  // https://arduino-info.wikispaces.com/file/view/DHT-lib.zip/545470280/DHT-lib.zip
dht  DHT;

int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;

// Hàm setup() chạy một lần:
void setup()
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  Serial.println("Humidity (%)\tTemperature (C)");
  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_RCK, OUTPUT);
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  //Hien thi len cong Com
  DHT.read11(dht11_pin);  // kích hoạt cảm biến DHT11
  Serial.print(DHT.humidity);       // độ ẩm (%)
  Serial.print("\t\t");
  Serial.println(DHT.temperature);  // nhiệt độ (C

  //Hien thi do am va nhiet do thNUmber
  long do_am = DHT.humidity;
  long nhiet_do = DHT.temperature;
  long value = (long) (DHT.humidity * 1000000.0 + DHT.temperature);
  Display(value);
  delay(1000);  // thời gian trễ giữa mỗi lần đọc  
}

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

byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};
void Display(long value)
{
  long val = abs(value);
  byte Array[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  int dem = 7;
  while(val > 0)
  {
    Array[dem] = so[val % 10];
    val = val / 10; 
    dem--;
  }
  if(value == 0) Array[dem] = so[0];
  //if(value < 0) Array[dem] = _BV(0);
  Array[1] |= _BV(6);
  Array[5] |= _BV(6);
  for(int i = 0; i <= 7; i++)
  {
    shift_out(Array[i]); 
  }
  digitalWrite(pin_RCK,HIGH); //Chan RCk hoat dong
  digitalWrite(pin_RCK,LOW); //Chan OE hoat dong
}
