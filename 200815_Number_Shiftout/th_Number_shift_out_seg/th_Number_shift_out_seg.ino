int pin_SDI = 10; //Ghi du lieu
int pin_SCK = 11; //Nhan du lieu
int pin_RCK = 12; //Chot du lieu

void setup() 
{
  pinMode (pin_SDI, OUTPUT);
  pinMode (pin_SCK, OUTPUT);
  pinMode (pin_RCK, OUTPUT);
}

void shift_out(int pin_SDI, int pin_SCK, byte out_put)
{
  for(int i = 0; i <= 7; i++)
  {
    digitalWrite(pin_SDI, !((out_put & 128) != 0) );
    out_put = out_put << 1;
    digitalWrite(pin_SCK, HIGH);
    digitalWrite(pin_SCK, LOW);
  }
}
void seg(byte output)
{
  shift_out(pin_SDI, pin_SCK, output);;
}

byte Aray[10] =
{
0b10111110, 
0b10100000, 
0b00101111,
0b10101011,
0b10110001,
0b10011011,
0b10011111,
0b10101000,
0b10111111,
0b10111011,
};
byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};

void num2(int index, int val)
{
  if (index == 0)
  {
    seg(so[0]);
    seg(so[0]);
    seg(so[val / 10]);
    seg(so[val % 10]);
    digitalWrite(pin_RCK, HIGH);
    digitalWrite(pin_RCK, LOW);
  }
  else if (index == 2)
  {
    seg(so[val / 10]);
    seg(so[val % 10]);
    digitalWrite(pin_RCK, HIGH);
    digitalWrite(pin_RCK, LOW);
  }
}

void loop() 
{
    seg(_BV(3));
    digitalWrite(pin_RCK, HIGH);
    digitalWrite(pin_RCK, LOW);
}
