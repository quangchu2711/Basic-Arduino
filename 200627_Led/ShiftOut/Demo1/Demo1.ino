int latch_pin = 5; // Chan RCK (12): Khi có sườn dương của xung clock, chân RCK sẽ chốt dữ liệu, dược đẩy ra các chân OUTPUT tương ứng
int clock_pin = 6; // Chan SCK (11): Khi có 1 xung tích cực ở sườn dương từ 0 lên tới 1 thì 1 bit sẽ dịch chuyển  vào IC
int data_pin = 4; // Chan SDI(14):  lay dữ liệu (ví dụ:1 byte ), các bit đưa vào kiểu nối tiếp.
#include<thButton.h>
int button0_pin=10;
int button1_pin=9;
int button2_pin=8;

thButton button0(button0_pin);
thButton button1(button1_pin);
int s=100;
void setup() 
{
  Serial.begin(9600);
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
}

byte led1[] = {0x00,0x18,0x3C,0x7E,0xFF, };
void shift_out_1_byte(int Led)
{
  digitalWrite(latch_pin, LOW); //Cac trang thai Led deu tat.
  shiftOut(data_pin, clock_pin, LSBFIRST, Led);
  digitalWrite(latch_pin, HIGH); //Chân Lach_pin sẽ chốt dữ liệu khi sườn từ 0 lên 1.
  digitalWrite(latch_pin, LOW); //Khi chốt xong sẽ phải hạ xuống mức LOW, sau 8 bit sẽ chốt 1 lần.
}

//Ham de dem bien dem chan hoac le khi bam nut Button

int dem = 0;
int hamDemChanLe()
{
  if(button0.onPress()) dem++;
  if(dem % 2 == 1) return 1;
  else return 0;
}

bool HieuUngCanhBuom(){
  while(1)
  {
//   if(hamDemChanLe() == 1) return false;
//   shift_out_1_byte(led1[0]); 
//   delay(100);
//   if(hamDemChanLe() == 1) return false;
//   shift_out_1_byte(led1[1]); 
//   delay(100);
//   if(hamDemChanLe() == 1) return false;
//   shift_out_1_byte(led1[2]); 
//   delay(100);
//   if(hamDemChanLe() == 1) return false;
//   shift_out_1_byte(led1[3]); 
//   delay(100);
//   if(hamDemChanLe() == 1) return false;
//   shift_out_1_byte(led1[4]); 
//   delay(100);
   for(int i = 0; i <= 4; i++)
    {
      if(hamDemChanLe() == 0){
        return false;
      }else{
        shift_out_1_byte(led1[i]);
        delay(100);
      }
    }
  }
  return true;
}

void loop()
{
  if(HieuUngCanhBuom() == false){
    shift_out_1_byte(led1[0]);
  }
}
