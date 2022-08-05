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
  shiftOut(data_pin, clock_pin, LSBFIRST, Led);
  digitalWrite(latch_pin, HIGH); //Chân Lach_pin sẽ chốt dữ liệu khi sườn từ 0 lên 1.
  digitalWrite(latch_pin, LOW); //Khi chốt xong sẽ phải hạ xuống mức LOW, sau 8 bit sẽ chốt 1 lần.
}

//byte led1[] = {0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF, };
byte led1[] = {0x00,0x18,0x3C,0x7E,0xFF, };

int button1_pin = 9;
int button2_pin = 8;
#include<thButton.h>
thButton button1(button1_pin);
thButton button2(button2_pin);

bool HieuUngCanhBuom() 
{
      shift_out_1_byte(0);
    delay(200);
    shift_out_1_byte(led1[1]);
    delay(200);
    shift_out_1_byte(led1[2]);
    delay(200);
    shift_out_1_byte(led1[3]);
    delay(200);
    shift_out_1_byte(led1[4]);
    delay(200);
}

int dem = 0;
void loop()
{
  if(button2.onPress())
  {
    dem++;
    if(dem % 2 == 1)
    {
      Serial.println("Hieu ung");
      while(1)
      {
        HieuUngCanhBuom();
        if(button2.onPress()) break;
      }
    }
    if(dem % 2 == 0)
    {
      Serial.println("TAT");
      shift_out_1_byte(led1[0]);
    }
  }
}
