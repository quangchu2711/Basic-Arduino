int SDI_pin = 7;
int SCK_pin = 8;
int RCK_pin = 9;


void setup() 
{
  pinMode(SDI_pin, OUTPUT);
  pinMode(SCK_pin, OUTPUT);
  pinMode(RCK_pin, OUTPUT);
}

void shift_out(byte data)
{
  for(int i = 0; i <= 7; i++)
  {
    digitalWrite(SDI_pin, !((data & 128) != 0));
    data = data << 1;
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);
  }
}

void loop() 
{
  shift_out(0x00);
  shift_out(0x00);
  shift_out(0x00);
  shift_out(_BV(7));
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
  delay(200);
//  for(int i = 0; i <= 7; i++)
//  {
//    shift_out(_BV(i + 3));
//    shift_out(_BV(i + 2));
//    shift_out(_BV(i + 1));
//    shift_out(_BV(i));
//    delay(200);
//  }
}