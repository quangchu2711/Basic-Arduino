#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

uint16_t dataReceive;
uint8_t dataCheck;

void setup() 
{
  // put your setup code here, to run once:
  dataCheck = 0;
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(13, OUTPUT);
//  digitalWrite(13, HIGH);
}

void loop() 
{
//  // put your main code here, to run repeatedly:
//  if (mySerial.available() > 0)
//  {
//    dataReceive = mySerial.read();
//    if (dataReceive == '1')
//    {
//      digitalWrite(13, HIGH);
//    }
//    else if (dataReceive == '0')
//    {
//      digitalWrite(13, LOW);
//    }
//    Serial.println(dataReceive);
//  }
  
  if (Serial.available() > 0)
  {
    digitalWrite(13, HIGH);
//    dataReceive = Serial.read();
//    if (dataReceive == '1')
//    {
//      digitalWrite(13, HIGH);
//    }
//    else if (dataReceive == '0')
//    {
//      digitalWrite(13, LOW);
//    }
  }

}
