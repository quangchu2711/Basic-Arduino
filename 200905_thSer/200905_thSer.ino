// Kết nối Arduino với thServo
//    Arduino pin       thServo pin
//        9       ---     CTRL  (orange)
//       VCC      ---     VCC   (red)
//       GND      ---     GND   (brown)

int myServo_pin = 5;

#include <Servo.h>              // sử dụng thư viện Servo
Servo myServo;                  // khai báo myServo

int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;


// Hàm setup() chạy một lần
void setup()
{
  int SG90_minPulse =  700;
  int SG90_maxPulse = 2300;
  myServo.attach(myServo_pin, SG90_minPulse, SG90_maxPulse);    // khởi tạo myServo
  Serial.begin(9600);

  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_RCK, OUTPUT);
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

// Hàm loop() chạy lặp lại vô hạn
void loop()
{
  int waittime = 30;            // thời gian đợi servo quay (ms)
// vị trí servo
  
//  for (; pos <= 180; pos += 1)  // quay servo từ 90 đến 180 độ
//  { 
//    myServo.write(pos);         // quay myServo đến vị trí 'pos'
//    delay(waittime);            // đợi servo quay
//  }
//  for (; pos >= 90; pos -= 1)   // quay servo từ 180 đến 90 độ
//  { 
//    myServo.write(pos);         // quay myServo đến vị trí 'pos'
//    delay(waittime);
//  }
//
//  delay(2000);                  // dừng 2 giây
  
  for (int pos = 90; pos >= 0; pos -= 1)    // quay servo từ 90 đến 0 độ
  { 
    myServo.write(pos);
    Serial.println(pos);
    Num(pos);
    delay(waittime);
  }
  //delay(2000); 
  for (int pos = 0; pos <= 90; pos += 1)   // quay servo từ 0 đến 90 độ
  { 
    myServo.write(pos);
    Serial.println(pos);
    Num(pos);
    delay(waittime);
  }

  delay(2000);                  // dừng 2 giây
}
