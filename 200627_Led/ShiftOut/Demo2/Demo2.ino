int latch_pin = 5; // Chan RCK (12): Khi có sườn dương của xung clock, chân RCK sẽ chốt dữ liệu, dược đẩy ra các chân OUTPUT tương ứng
int clock_pin = 6; // Chan SCK (11): Khi có 1 xung tích cực ở sườn dương từ 0 lên tới 1 thì 1 bit sẽ dịch chuyển  vào IC
int data_pin = 4; // Chan SDI(14):  lay dữ liệu (ví dụ:1 byte ), các bit đưa vào kiểu nối tiếp.
int button = 10;
void setup() 
{
  pinMode(button, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
  pinMode(latch_pin,OUTPUT);
  pinMode(clock_pin,OUTPUT);
  pinMode(data_pin,OUTPUT); 
}

byte led[] = {0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF, }; 
void shift_out_1_byte(int Led)
{
  digitalWrite(latch_pin, LOW); //Cac trang thai Led deu tat.
  shiftOut(data_pin, clock_pin, LSBFIRST, Led);
  digitalWrite(latch_pin, HIGH); //Chân Lach_pin sẽ chốt dữ liệu khi sườn từ 0 lên 1.
  digitalWrite(latch_pin, LOW); //Khi chốt xong sẽ phải hạ xuống mức LOW, sau 8 bit sẽ chốt 1 lần.
}

void loop() {
  int buttonStatus = digitalRead(button);    //Đọc trạng thái button
  if (buttonStatus == HIGH) { // Nếu mà button bị nhấn
    shift_out_1_byte(led[1]); // Đèn led sáng
  } else { // ngược lại
    shift_out_1_byte(led[0]);
  }
}
