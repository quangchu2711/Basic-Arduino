#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

char incomingByte;   // lưu tín hiệu đến
//String x = ;

void setup() 
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);     // mở cổng serial với mức baudrate là 9600
  mySerial.begin(9600);
  digitalWrite(2, LOW);
}

void loop() 
{
//  // xuất tín hiệu khi nhận được tín hiệu
  if (Serial.available() > 0) 
  {
     digitalWrite(2, HIGH);
    // đọc các giá trị nhận được
    incomingByte = Serial.read();
    mySerial.println(incomingByte);
//    if (incomingByte == '1')
//    {
//      digitalWrite(2, HIGH);
//    }
//    if (incomingByte == '0')
//    {
//      digitalWrite(2, LOW);
//    }
  }


//  Serial.println("hello acsacas");
//  delay(1000);
}
