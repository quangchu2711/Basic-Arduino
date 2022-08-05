#include<Wire.h>
#include<TimeLib.h>
#include<DS1307RTC.h>
#include<thNumber.h>

int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;

tmElements_t tm, Time;

byte DigitFont[10] = {                          
    FONT7_0, FONT7_1, FONT7_2, FONT7_3, FONT7_4, 
    FONT7_5, FONT7_6, FONT7_7, FONT7_8, FONT7_9
};

void my_shiftOut(byte val) { //shiftOut
  byte i;

  
  for (i = 0; i < 8; i++) {
    digitalWrite(SDI_pin, !(val & (1 << (7 - i)))); //mặc định là MSBFIRST
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);    
  }
}

void display_currentTime(int _min, int sec) { //Hiển thị thời gian lên thNumber
  byte bNum[4] = {FONT7_0, FONT7_0, FONT7_0, FONT7_0};
  byte x = 3, y = 1;
  while (_min > 0) {              
    bNum[y] = DigitFont[_min % 10];
    _min /= 10;
    y--;
  }
  while (sec > 0) {
    bNum[x] = DigitFont[sec % 10];
    sec /= 10;
    x--;
  }
  bNum[1] |= _BV(6);
  for (byte i = 0; i < 4; i++) {
    my_shiftOut(bNum[i]);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}

void print_serial(tmElements_t Time) { // hiển thị thời gian lên Serial monitor
  
  // hiển thị: giờ : phút : giây
  print2digits(Time.Hour);
  Serial.print(":");
  print2digits(Time.Minute);
  Serial.print(":");
  print2digits(Time.Second);
  Serial.println();
}

void print2digits(int number) { //
  if (number >= 0 && number < 10)
    Serial.print('0');
  Serial.print(number);
}

tmElements_t getTime(const char *str)
{
  int Hour, Min, Sec;
  sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec);
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec + 10; 
  return tm;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  thNumber.begin(SDI_pin, SCK_pin, RCK_pin);
  getTime(__TIME__);
  RTC.write(tm);
  //print_serial(tm);
}

void loop() {
  // put your main code here, to run repeatedly:
  RTC.read(tm);  // đọc dữ liệu từ RTC
  print_serial(tm);
  int Min = tm.Minute;
  int Sec = tm.Second;
  display_currentTime(Min, Sec);
  delay(1000);
}
