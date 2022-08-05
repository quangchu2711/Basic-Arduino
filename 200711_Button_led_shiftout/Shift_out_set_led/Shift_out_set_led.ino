int latch_pin = 5; // Chan RCK (12): Khi có sườn dương của xung clock, chân RCK sẽ chốt dữ liệu, dược đẩy ra các chân OUTPUT tương ứng
int clock_pin = 6; // Chan SCK (11): Khi có 1 xung tích cực ở sườn dương từ 0 lên tới 1 thì 1 bit sẽ dịch chuyển  vào IC
int data_pin = 4; // Chan SDI(14):  lay dữ liệu (ví dụ:1 byte ), các bit đưa vào kiểu nối tiếp.

void setup() 
{
  Serial.begin(9600);
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
}

void shift_out_1_byte(int Led)
{
  digitalWrite(latch_pin, LOW); //Cac trang thai Led deu tat.
  shiftOut(data_pin, clock_pin, MSBFIRST, Led);
  digitalWrite(latch_pin, HIGH); //Chân Lach_pin sẽ chốt dữ liệu khi sườn từ 0 lên 1.
  digitalWrite(latch_pin, LOW); //Khi chốt xong sẽ phải hạ xuống mức LOW, sau 8 bit sẽ chốt 1 lần.
}

//byte led[] = {0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF, };
byte led1[] = {0x00,0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80, };

void loop()
{
  //shift_out_1_byte(0x80);
  //shift_out_1_byte(0x40);
  //shift_out_1_byte(0x20);
  //shift_out_1_byte(0x10);
  //shift_out_1_byte(0x8);
  //shift_out_1_byte(0x4);
  //shift_out_1_byte(0x4);
  //shift_out_1_byte(0x2);
  //shift_out_1_byte(0x1);
  for(int i = 7; i >= 0; i++)
  {
    shift_out_1_byte(led1[i]);
    delay(200);
    shift_out_1_byte(led1[0]);
  }
}
