int SDI_pin = 7;
int SCK_pin = 9;
int RCK_pin = 8;

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
    digitalWrite(SDI_pin, (data & 128) != 0);
    data = data << 1;
    digitalWrite(SCK_pin, HIGH);
    digitalWrite(SCK_pin, LOW);
  }
  digitalWrite(RCK_pin, HIGH);
  digitalWrite(RCK_pin, LOW);
}


int output = 0x00;
void set_led(int val, int state)
{
  if(state == HIGH)
  {
    output = output | (1 << val);
    shift_out(output);
  }
  else
  {
    output = output & ~(1 << val);
    shift_out(output); 
  }
}

void loop() 
{
  int max_led = 7;
  while(max_led >= 0)
  {
    for(int i = 0; i <= max_led; i++)
    {
      set_led(i, HIGH);
      delay(200);
      set_led(i, LOW);
    }
    set_led(max_led, HIGH);
    max_led--;
    delay(200);
  }
  for(int i = 0; i <= 7; i++)
  {
    set_led(i, LOW);
  }
  delay(5
  00);
  //shift_out(0x00000000);
  //delay(1000);
}
