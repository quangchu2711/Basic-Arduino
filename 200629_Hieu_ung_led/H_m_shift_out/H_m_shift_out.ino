

int latchPin = 10;//RCK
int clockPin = 11;//SCK
int dataPin = 12;//SDI
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void my_shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
  uint8_t i;

  for (i = 0; i < 8; i++)  {
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
void loop() {
  for (int i=0; i<8; i++)
  {
    set_led(i,HIGH);
    delay(100);
  }

  for (int i=7; i>=0; i--)
  {
    set_led(i,LOW);
    delay(100);
  }
}
