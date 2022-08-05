int buzzer_pin = 10; //(PB2 xet output la chan 10)

void setup() 
{
  pinMode(buzzer_pin, OUTPUT);
  Timer1_Init();
}

void loop() 
{
  Tone(buzzer_pin, 4000);
  delay(1000);
  Tone(buzzer_pin, 440);
  delay(1000);
}

void Timer1_Init()
{
  TCCR1A = 0; TCCR1B = 0; //Reset hai thanh ghi
  DDRB |= 1 << PB2; //Tuc chon dau ra chan pin 10 la output;
  TCCR1A |= (1 << WGM11); //Chon che do Fast PWM , che do tha tu do ICR1 
  TCCR1B |= (1 << WGM12) | (1 << WGM13); //Chon che do Fast PWM , che do tha tu do ICR1 
  TCCR1A |= 1 << COM1B1; //Chon kieu so sanh thuong (none_inverting)
}

void Tone(int pin, int PWM)
{
  ICR1 = 16000000 / PWM; // xung tran so (16Mhz/PWM) clock
  OCR1B = (16000000 / PWM) / 2; //Chon do rong cua xung la 50%
  TCCR1B |= 1 << CS10;
}
