//#include"wiring_private.h"
//#include"pins_arduino.h"
int buzzer_pin = 10;
int knob_pin = A3;
void my_tone(int pin, int fre) {
    ICR1 = 16000000 / fre; //xung răng cưa tràn sau 16000000 / fre p_clock
    OCR1B = 16000000 / fre / 2; //khi TTCN1 == OCR1B thì compare match
    TCCR1B |= (1 << CS10); // f_clock1 = 16Mhz 
}

void no_tone(int pin, int fre) {
    ICR1 = 0 ; //xung răng cưa tràn sau 16000000 / fre p_clock
    OCR1B = 0; //khi TTCN1 == OCR1B thì compare match
    TCCR1B = 0; // f_clock1 = 16Mhz 
}
void Tone(int buzzer_pin, int val)
{
   float value = (float) (1.0 / val) * 0.5;
   int value_tone = (int) (value* pow(10, 6));
   int dem = 1000; /*Chỗ này chưa chắc đúng đâu, mk cứ cho là 1000 đấy*/
   while(dem--)
   {
     digitalWrite(buzzer_pin, HIGH);
     delayMicroseconds(value_tone);
     digitalWrite(buzzer_pin, LOW);
     delayMicroseconds(value_tone);
   }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(knob_pin, INPUT);
  TCCR1A = 0; TCCR1B = 0;// reset 2 thanh ghi
  DDRB |= (1 << PB2); // chọn đầu ra PB2 là output(pin 10)
  TCCR1A |= (1 << WGM11);                 //chọn mode fast pwm(mode 
  TCCR1B |= (1 << WGM12) | (1 << WGM13);  //top value tự do ICR1)
  TCCR1A |= (1 << COM1B1); // chế đô so sánh thường non-inverted
}
void loop() {
  my_tone(buzzer_pin, 4000);
  delay(1000);
  no_tone(buzzer_pin, 4000);
  delay(1000);
}
