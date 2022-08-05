// Kết nối Arduino với biến trở:
//    Arduino pin       thKnob pin
//       A3        ---     VAR
//       VCC       ---     A
//       GND       ---     B

int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;

int latchPin = 4;//RCK
int clockPin = 5;//SCK
int dataPin = 6;//SDI


int knob_sensor_pin = A3;


// Hàm setup() chạy một lần:
void setup() 
{
  //Output 3 chân điều khiển của thLed
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //Output 3 chân điều khiển của thNumber
  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_RCK, OUTPUT);
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
}

//Hàm shift_out của thLed
void shiftOut_Led(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
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

//Hàm điêù khiển led sáng hoặc led tắt từ shift_out
byte outPut=0x00;
void set_led(int index, int state)
{
    outPut = (outPut & ~ (1 << index)); // dich bit truoc nhan xog roi dao 
    outPut = outPut | (state << index);// 
    shiftOut_Led(dataPin, clockPin, LSBFIRST, outPut);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
}

//Hàm shift_out của thNumber
void shift_out(byte data)
{
  for(int i = 0; i <= 7; i++)
  {
    digitalWrite(pin_SDI, !((data & 128) != 0));
    data = data << 1;
    digitalWrite(pin_SCK, HIGH);
    digitalWrite(pin_SCK, LOW);
  }
}

//Hàm hiển thị 1 số bất kỳ lên thNumber
byte so[10] = {0xBE, 0xA0, 0x2F, 0xAB, 0xB1, 0x9B, 0x9F, 0xA8, 0xBF, 0xBB};
void num(int val)
{
  int value = val;
  byte Array[4] = {0x00, 0x00, 0x00, 0x00};
  int dem = 3;
  while(value > 0)
  {
    Array[dem] = so[value % 10];
    value = value / 10;
    dem--;
  }
  if(val == 0) Array[3] = so[0];
  for(int i = 0; i <= 3; i++)
  {
    shift_out(Array[i]);
  }
  digitalWrite(pin_RCK, HIGH);
  digitalWrite(pin_RCK, LOW);
}

// Hàm loop() chạy lặp lại vô hạn:

//Hàm hiển thị giá trị cảm biến của thKnob đọc được lên thNumber
void display_Knop(int knob_value)
{
  knob_value = analogRead(knob_sensor_pin);  // đọc giá trị cảm biến
  num(knob_value);
  Serial.println(knob_value);                    // in kết quả ra màn hình
  delay(50);                                    // thời gian trễ giữa mỗi lần đọc
}

//Hàm hiển thị số Led sáng và tắt phục thuộc biến val
void Number_Led_HIGH(int val)
{
  for(int i = 0; i <= val; i++)
  {
    set_led(i, HIGH);
    delay(100);
  }
  for(int i = val + 1; i <= 7; i++)
  {
    set_led(i, LOW);
    delay(100);
  }
}

//Hàm chia khoảng hiển thị Led sáng dần
void display_Led_Knop_Number()
{
  int knob_value = analogRead(knob_sensor_pin);
  if(knob_value >= 0 && knob_value <= 127)
  {
    Number_Led_HIGH(0);
    display_Knop(knob_value); 
  }
  else if(knob_value >= 128 && knob_value <= 255)
  {
    Number_Led_HIGH(1);
    display_Knop(knob_value); 
  }
   else if(knob_value >= 256 && knob_value <= 383)
  {
    Number_Led_HIGH(2);
    display_Knop(knob_value); 
  }
   else if(knob_value >= 384 && knob_value <= 511)
  {
    Number_Led_HIGH(3);
    display_Knop(knob_value); 
  }
   else if(knob_value >= 512 && knob_value <= 639)
  {
    Number_Led_HIGH(4);
    display_Knop(knob_value); 
  }
   else if(knob_value >= 640 && knob_value <= 767)
  {
    Number_Led_HIGH(5);
    display_Knop(knob_value); 
  }
   else if(knob_value >= 768 && knob_value <= 897)
  {
    Number_Led_HIGH(6);
    display_Knop(knob_value); 
  }
   else if(knob_value >= 896 && knob_value <= 1023)
  {
    Number_Led_HIGH(7);
    display_Knop(knob_value); 
  }
}
void loop() 
{
  display_Led_Knop_Number();
}
