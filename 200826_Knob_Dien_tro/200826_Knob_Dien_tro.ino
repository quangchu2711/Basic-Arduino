// Kết nối Arduino với biến trở:
//    Arduino pin       thKnob pin
//       A3        ---     VAR
//       VCC       ---     A
//       GND       ---     B

int pin_SDI = 7;
int pin_SCK = 8;
int pin_RCK = 9;

int knob_sensor_pin = A3;


// Hàm setup() chạy một lần:
void setup() 
{
  pinMode(pin_SDI, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_RCK, OUTPUT);
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
}

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

void display_Knop()
{
  int knob_value = analogRead(knob_sensor_pin);  // đọc giá trị cảm biến
  num(knob_value);
  Serial.println(knob_value);                    // in kết quả ra màn hình
  delay(250);                                    // thời gian trễ giữa mỗi lần đọc
}
void loop() 
{
  display_Knop();
}
