int latchPin = 9;//RCK
int clockPin = 8;//SCK
int dataPin = 7;//SDI

byte Aray[10] =
{
0b10111110, // 0xBE
0b10100000, // 0x
0b00101111,
0b10101011,
0b10110001,
0b10011011,
0b10011111,
0b10101000,
0b10111111,
0b10111011,
};

byte aray[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};

byte Array[4] = {
0b10111110,
0b10100000,
0b00101111,
0b10101011,
};

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
    }  
    else
    {  
      digitalWrite(dataPin, (val & 128) != 0 );
      val <<= 1;
    }
      
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);    
  }
}

byte outPut=0x00;
void shift_out(int index, int state)
{
    outPut = (outPut & ~ (1 << index)); // dich bit truoc nhan xog roi dao 
    outPut = outPut | (state << index);// 
    my_shiftOut(dataPin, clockPin, LSBFIRST, outPut);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
}

byte A = 0x03;
byte B = 0x05;
byte C = 0x07;
byte D = 0x01;
byte E = 0x02;
byte F = 0x04;
byte G = 0x00;
byte Cham = 0x06;

void set_seg(int index, int state)
{
  if (state == HIGH)
  {
    shift_out(index, LOW);
  }
  else
  {
    shift_out(index, HIGH);
  }
}

void num_1(int state)
{
  if (state == HIGH) set_seg(0, LOW);
  else if (state == LOW)
  {
    for (int i = 0; i <= 7; i++)
    {
      set_seg(i, LOW);
    }
  }
}

void so1(int state)
{
   if (state == HIGH)
   {
    set_seg(5, HIGH);
    set_seg(7, HIGH);
    set_seg(0, LOW);
    set_seg(1, LOW);
    set_seg(2, LOW);
    set_seg(3, LOW);
    set_seg(4, LOW);
    set_seg(6, LOW);
   }
   else
   {
    for(int i = 0; i <= 7; i++)
    {
      set_seg(i, LOW);
    }
   }
}

void My_shift_out(int16_t state)
{
  for(int i=0; i<8; i++)
  {
    digitalWrite(dataPin, !(state & (1 << (7 - i))));
    digitalWrite(clockPin, HIGH);//cho phep hoat dong 
    digitalWrite(clockPin, LOW);
  }
}

void loop() {
//    shift_out(0, HIGH);
//    shift_out(1, HIGH);
//    shift_out(2, HIGH);
//    shift_out(3, HIGH);
//    shift_out(4, HIGH);
//    shift_out(5, HIGH);
//    shift_out(6, HIGH);
//    shift_out(7, HIGH);
//    shift_out(3, LOW);
//    delay(1000);
//   for(int i = 0; i <= 3; i++)
//   {
//    set_seg(Array[i], HIGH);
//    delay(1000);
//   }
//   for(int i = 0; i <= 9; i++)
//   {
//    My_shift_out(0x00);
//    My_shift_out(0x00);
//    My_shift_out(0x00);
//    My_shift_out(aray[i]);
//    digitalWrite(latchPin,HIGH);
//    digitalWrite(latchPin,LOW);
//    delay(1000);
//   }
    My_shift_out(_BV(7));
    //My_shift_out(0x10000000);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
    delay(1000);
}

    
