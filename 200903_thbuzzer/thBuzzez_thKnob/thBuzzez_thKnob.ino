int buzzer_pin = 12;
int knob_sensor_pin = A3;

// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);
  pinMode(buzzer_pin, OUTPUT);  // cài đặt OUTPUT điều khiển buzzer
  pinMode(knob_sensor_pin, INPUT);  
}

// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int knob_value = analogRead(knob_sensor_pin);  
  //Serial.println(knob_value);
  delay(250);                  
  int x = (int)((float)knob_value * 8000.0/1023.0);  
  Serial.println(x);                          
  tone(buzzer_pin, x);   // phát tần số 440Hz trong 1000ms
  delay(250);
  //delay(1000);             // thời gian phát
//  noTone(buzzer_pin);      // dừng phát
//  delay(1500);             // thời gian tr
}
