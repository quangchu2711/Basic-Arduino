int latchPin = 5;  // ST_CP / RCK (  12) của 74HC595
int clockPin = 6;  // SH_CP / SCK (pin 11) của 74HC595
int dataPin = 4;   // DS    / SDI (pin 14) của 74HC595
void shift_out_1_byte(int ledStatus)
{
  digitalWrite(latchPin, LOW); //các đèn LED sẽ không sáng khi bạn digital LOW
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);  
  //shiftOut(dataPin, clockPin, LSBFIRST, ledStatus); 
  digitalWrite(latchPin, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
  digitalWrite(latchPin, LOW);
}

byte led1[] = {0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF, }; 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop()
{
    shift_out_1_byte(led1[0]);
    delay(500);
    shift_out_1_byte(led1[1]);
    delay(500);
    shift_out_1_byte(led1[2]);
    delay(500);
    shift_out_1_byte(led1[3]);
    delay(500);
    shift_out_1_byte(led1[4]);
    delay(500);
    shift_out_1_byte(led1[5]);
    delay(500);
    shift_out_1_byte(led1[6]);
    delay(500);
    shift_out_1_byte(led1[7]);
    delay(500);
    shift_out_1_byte(led1[8]);
    delay(500);
}
