int latch_pin = 9; // Chan RCK (12): Khi có sườn dương của xung clock, chân RCK sẽ chốt dữ liệu, dược đẩy ra các chân OUTPUT tương ứng
int clock_pin = 8; // Chan SCK (11): Khi có 1 xung tích cực ở sườn dương từ 0 lên tới 1 thì 1 bit sẽ dịch chuyển  vào IC
int data_pin = 7; // Chan SDI(14):  lay dữ liệu (ví dụ:1 byte ), các bit đưa vào kiểu nối tiếp.

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
  /* Chan latch_pin la chan RCK duoc noi chung voi chan OE la chan cua IC 595 , 
  chan RCK lay du lieu  khi suon tu 0 len 1. con chan OE cho phep IC hoat dong o suon am*/
}

int led_on = 1; // Trang thai led bat
int led_off = 0; //  Trang thai led tat
int output = 0x00;
int phep_dich = 0x01;
int phep_and = 0x01;
void set_led(int led, int sta)
{
  if(sta == led_on)
  {
    output = output | ( phep_dich << led );
    shift_out_1_byte(output);
    //phep_or = 0x01;
  }
  else
  {
    output = output & ~_BV(led);
    shift_out_1_byte(output);
    //phep_and = 0x01;
  }
}

void loop()
{
//  set_led(3,led_on);
//  set_led(2,led_on);
//  set_led(1,led_on);
//  delay(100);
//  set_led(3,led_off);
//  set_led(2,led_off);
//  set_led(1,led_off);
//  delay(100);
    for(int i = 0; i <= 7; i++)
    {
      set_led(i, led_on);
      delay(500);
    }
    for(int i = 7; i>= 0; i--)
    {
      set_led(i, led_off);
      delay(500);
    }
}
