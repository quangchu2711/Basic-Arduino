// Kết nối Arduino với thBuzzer:
//    Arduino pin       thBuzzer pin
//       12        ---    A2  (nối với chân A1 sẽ kêu to hơn)
//       GND       ---    B

int buzzer_pin = 11;


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);
  pinMode(buzzer_pin, OUTPUT);  
}

//delayMicroseconds(T_HIGH);

//int period = 1000;
//unsigned long time_now = 0;
//  
//void Tone_Delay(int buzzer_pin, int val, int period, unsigned long time_now)
//{
//  float value = (float) (1.0 / val) * 0.5;
//  int value_tone = (int) (value* pow(10, 6));
//  int dem = 1000;
//  while(1)
//   {
//      time_now = millis();
//      Serial.println("Hello");
//      while(millis() < time_now + period)
//      {
//        digitalWrite(buzzer_pin, HIGH);
//        delayMicroseconds(value_tone);
//        digitalWrite(buzzer_pin, LOW);
//        delayMicroseconds(value_tone);
//      }
//   }
//}

void Tone(int buzzer_pin, int val,int Delay)
{
   float value = (float) (1.0 / val) * 0.5;
   int value_tone = (int) (value* pow(10, 6));
   //int dem = 1000;
   //Serial.println(value_tone);
   while(Delay--)
   {
     digitalWrite(buzzer_pin, HIGH);
     delayMicroseconds(value_tone);
     digitalWrite(buzzer_pin, LOW);
     delayMicroseconds(value_tone);
   }
}

void No_tone(int buzzer_pin)
{
  digitalWrite(buzzer_pin, LOW);
}

void loop() 
{
  Serial.println("");
  Tone(buzzer_pin, 524, 500);
  Tone(buzzer_pin, 588, 500);
  Tone(buzzer_pin, 660, 500);
  Tone(buzzer_pin, 698, 500);
  Tone(buzzer_pin, 784, 500);
  Tone(buzzer_pin, 880, 500);
  Tone(buzzer_pin, 987, 500);
//  tone(buzzer_pin, 524);
//  delay(500);
//  tone(buzzer_pin, 588);
//  delay(500);
//  tone(buzzer_pin, 660);
//  delay(500);
//  tone(buzzer_pin, 698);
//  delay(500);
//  tone(buzzer_pin, 784);
//  delay(500);
//  tone(buzzer_pin, 880);
//  delay(500);
//  tone(buzzer_pin, 987);
//  delay(500);
}
