//the opcodes for the MAX7221 and MAX7219
/*Note: Tên các thanh ghi và địa chỉ tương ứng của nó xem trong datasheet*/
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15
/*----------------------------------------------------------------------------------*/
/*Note: Dùng 3 chân điều khiển ledMatric 32 x 8 dùng IC MAX7219*/
#define SPI_MOSI 12           //DIN
#define SPI_CLK 11            //CLK
#define SPI_CS 10             //CS
/*----------------------------------------------------------------------------------*/
byte Status[64] = {0};       
byte spidata[8] = {0};
int maxDevices = 4;           //Số thiết bị: 8x32 => có 4 thiết bị 8x8
/*----------------------------------------------------------------------------------*/
void setup() 
{
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SPI_CLK, OUTPUT);
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS,HIGH);
  for(int i=0;i<64;i++) 
      Status[i]=0x00;
  for(int i=0;i<maxDevices;i++) 
  {
    spiTransfer(i,OP_DISPLAYTEST,0);
    //scanlimit is set to max on startup
    SetScanLimit(i,7);
    //decode is done in source
    //spiTransfer(i,OP_DECODEMODE,0);
    ClearDisplay(i);
    //we go into shutdown-mode on startup
    Shutdown(i, false);
    SetIntensity(i, 5);
   }
}
/*----------------------------------------------------------------------------------*/
/*Cách dung hàm Display_4ledMatric(tức ledMatric 8x32, 8 hàng và 32 cột):
Digit: Chỉ số hàng muốn hiển thị.
Data: 1byte gồm 8 bit truyền vào từng hàng của từng con ledMatric.
ledMatric: vị trí con ledMtric mà mk muốn sử dụng (có tất cả là 4 con)
*/ 
byte Data[4] = {0, 0, 0, 0};
void LedMatric_Display(int ledMatric, volatile byte Digit, volatile byte Output)
{
   Data[ledMatric] = Output;
   digitalWrite(SPI_CS,LOW);
   for(int i = 0 ; i <= 3; i++)
   {    
      shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, Digit);
      shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, Data[i]);
   }
    digitalWrite(SPI_CS,HIGH);
}

/*LedMatric(8x32): 
row = 8;
col = 32;
*/
void Out_Display(int row ,byte data0,byte data1, byte data2, byte data3)
{
    digitalWrite(SPI_CS,LOW);  
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data0);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data1);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data2);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
    shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data3);
    digitalWrite(SPI_CS,HIGH);
}

uint8_t Tym[8] = {0x00,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x00};
uint8_t I[8] = {0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x7E};//I
uint8_t U[8] = {0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C};//U

void Display_Pixel(byte Data[], int row, int col)
{
  
  Out_Display(Data[0], 1, 0, 0, 1);
  Out_Display(2, 0, 0, 1, 1);
  Out_Display(3, 0, 1, 0, 0);
  Out_Display(4, 0, 1, 0, 0);
  Out_Display(5, 1, 0, 0, 1);
  Out_Display(6, 0, 0, 1, 1);
  Out_Display(7, 0, 1, 0, 0);
  Out_Display(8, 0, 1, 0, 0);  
}

void Text_effect(int delaytime, uint8_t text[])
{
  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0 ; j <= 7; j++)
    {
      Out_Display(j + 1, text[j] << i, text[j] << i, text[j] << i, text[j] << i);
    }
    delay(delaytime);
  }  
}
/**********************************************************************************************/
uint32_t Data_out_0 = 0x00000000;
uint32_t Data_out_1 = 0x00000000;
uint32_t Data_out_2 = 0x00000000;
uint32_t Data_out_3 = 0x00000000;
uint32_t Data_out_4 = 0x00000000;
uint32_t Data_out_5 = 0x00000000;
uint32_t Data_out_6 = 0x00000000;
uint32_t Data_out_7 = 0x00000000;

//uint8_t data1 = 0x00;
//uint8_t data2 = 0x00;
//uint8_t data3 = 0x00;
//uint8_t data4 = 0x00;

uint32_t one = 0x00000001;
uint32_t HIGH_P = 0x00000001;
uint32_t LOW_P = 0x00000000;
//, uint32_t state, uint32_t Data_out
void Test_Pixels(int row, int col, uint32_t state, uint32_t Data_out)
{
  Data_out = (Data_out & ~((uint32_t)(one << col)) | ((uint32_t)(state << col)));
  uint8_t data1 = (uint8_t) Data_out;
  uint8_t data2 = (uint8_t) (Data_out >> 8);
  uint8_t data3 = (uint8_t) (Data_out >> 16);
  uint8_t data4 = (uint8_t) (Data_out >> 24);
  row += 1;
  digitalWrite(SPI_CS,LOW);  
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data4);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data3);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data2);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, row);
  shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, data1);
  digitalWrite(SPI_CS,HIGH);
  
  for(int i = 0 ; i <= 7; i++)
  {
    if(row == 1) Data_out_0 = Data_out;
    if(row == 2) Data_out_1 = Data_out;
    if(row == 3) Data_out_2 = Data_out;
    if(row == 4) Data_out_3 = Data_out;
    if(row == 5) Data_out_4 = Data_out;
    if(row == 6) Data_out_5 = Data_out;
    if(row == 7) Data_out_6 = Data_out;
    if(row == 8) Data_out_7 = Data_out;
  }
}

void Set_Led_Pixels(int row, int col, uint32_t state)
{
  if(row == 0) Test_Pixels(row, col, state, Data_out_0);
  else if(row == 1) Test_Pixels(row, col, state, Data_out_1);
  else if(row == 2) Test_Pixels(row, col, state, Data_out_2);
  else if(row == 3) Test_Pixels(row, col, state, Data_out_3);
  else if(row == 4) Test_Pixels(row, col, state, Data_out_4);
  else if(row == 5) Test_Pixels(row, col, state, Data_out_5);
  else if(row == 6) Test_Pixels(row, col, state, Data_out_6);
  else if(row == 7) Test_Pixels(row, col, state, Data_out_7);
}

void Test_demo()
{
    for(int i = 0; i <= 3; i++)
  {
    ClearDisplay(i);
  }

  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 31; j++)
    {
      Set_Led_Pixels(i, j, HIGH_P);
      delay(10);
    }
  }
  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 31; j++)
    {
      Set_Led_Pixels(i, j, LOW_P);
      delay(10);
    }
  }

  for(int i = 0; i <= 3; i++)
  {
    ClearDisplay(i);
  }
}

int delay_time = 100;
void I_demo()
{
  for(int i = 6; i >= 1; i--)
  {
    Set_Led_Pixels(1, i, HIGH_P);
    delay(delay_time);     
  }
  for(int i = 2; i <= 5; i++)
  {
    Set_Led_Pixels(i, 4, HIGH_P);
    Set_Led_Pixels(i, 3, HIGH_P);
    delay(delay_time);     
  }
  for(int i = 6; i >= 1; i--)
  {
    Set_Led_Pixels(6, i, HIGH_P);
    delay(delay_time);     
  }
}

void L_demo()
{
  for(int i = 1; i <= 6; i++)
  {
    Set_Led_Pixels(i, 30, HIGH_P);
    Set_Led_Pixels(i, 29, HIGH_P);
    delay(delay_time);     
  }
  for(int i = 28; i >= 25; i--)
  {
    Set_Led_Pixels(6, i, HIGH_P);
    delay(delay_time);     
  }
}

void E_demo()
{
  for(int i = 1; i <= 6; i++)
  {
    Set_Led_Pixels(i, 22, HIGH_P);
    Set_Led_Pixels(i, 21, HIGH_P);
    delay(delay_time);     
  }
  for(int i = 20; i >= 17; i--)
  {
    Set_Led_Pixels(1, i, HIGH_P);
    Set_Led_Pixels(3, i, HIGH_P);
    Set_Led_Pixels(4, i, HIGH_P);    
    Set_Led_Pixels(6, i, HIGH_P);
    delay(delay_time);     
  }
}

void V_demo()
{
  for(int i = 1; i <= 4; i++)
  {
    Set_Led_Pixels(i, 14, HIGH_P);
    Set_Led_Pixels(i, 9, HIGH_P);
    delay(delay_time);     
  }  
  for(int i = 3; i <= 5; i++)
  {
    Set_Led_Pixels(i, 13, HIGH_P);
    Set_Led_Pixels(i, 10, HIGH_P);
    delay(delay_time);     
  }
  for(int i = 4; i <= 6; i++)
  {
    Set_Led_Pixels(i, 12, HIGH_P);
    Set_Led_Pixels(i, 11, HIGH_P);
    delay(delay_time);     
  }
}




///**********************************************************************************************/
const int numbyte = 40; // Số dãy Byte (1 chữ gồm 8 dãy byte = 64 bit)

byte a[numbyte] =
{
  0x42, 0x42, 0x42, 0x5a, 0x66, 0x66, 0x42, 0x00, //M
  0x38, 0x04, 0x3c, 0x24, 0x18, 0x00, 0x00, 0x00, //e
  0x18, 0x24, 0x04, 0x24, 0x18, 0x00, 0x00, 0x00, //c
  0x14, 0x14, 0x1c, 0x04, 0x04, 0x04, 0x00, 0x00, //h
  0x38, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00  //a
};


void scroll()             //Chạy chữ
{
  ClearDisplay(0);
  
  //Set từng hàng
  for (int i = 0 ; i + 8 <= numbyte; i++)
  {
    for (int j = 0 ; j < 8; j++)
    {
            SetRow(0, j, a[i + j]);
      SetRow(1, j, a[i + j]);
      SetRow(2, j, a[i + j]);

      SetRow(3, j, a[i + j]);
    } 
    delay(100); // Chờ 100s
  }
}




void loop()
{
//scroll();

//  Test_demo();


//  for(int i = 0; i <= 7; i++)
//  {
//    for(int j = 0; j <= 31; j++)
//    {
//      Set_Led_Pixels(i, j, LOW_P);
//      
//    }
//  }
//
  L_demo();
//  E_demo();
//  V_demo();
//  I_demo();
//  delay(100);
//  for(int i = 0; i <= 7; i++)
//  {
//    for(int j = 0; j <= 31; j++)
//    {
//      Set_Led_Pixels(i, j, LOW_P);
//      
//    }
//  }
//

//  
//  Set_Led_Pixels(7, 3, HIGH_P);
//  Set_Led_Pixels(5, 3, HIGH_P);
//  delay(1000);
//  Set_Led_Pixels(7, 3, LOW_P);
//  Set_Led_Pixels(5, 3, LOW_P);
//  delay(1000);

  
//  Test_Pixels(5, 3, HIGH_P, Data_out_5);
//  Test_Pixels(5, 15, HIGH_P, Data_out_5);
//  Test_Pixels(3, 31, HIGH_P, Data_out_3);
//  Test_Pixels(1, 3, HIGH_P, Data_out_1);
//  delay(1000);
//  Test_Pixels(5, 3, LOW_P, Data_out_5);
//  Test_Pixels(5, 15, LOW_P, Data_out_5);
//  Test_Pixels(3, 31, LOW_P, Data_out_3);
//  Test_Pixels(1, 3, LOW_P, Data_out_1);
//  delay(1000);
//

//    for(int i = 0; i <= 7; i++)
//    {
//        ClearDisplay(i);
//    }
//    int max_led = 31;
//    while(max_led >= 0)
//    {
//        for(int i = 0; i <= max_led; i++)
//        {
//          Test_Pixels(0, i, HIGH_P);
//          delay(50);
//          Test_Pixels(0, i, LOW_P);
//        }
//        Test_Pixels(0, max_led, HIGH_P);
//        max_led--;
//        delay(50);
//    }
//    for(int i = 0; i <= 7; i++)
//    {
//        ClearDisplay(i);
//    }
  
//  Test_Pixels(0, 10, HIGH_P);
//  Test_Pixels(0, 9, HIGH_P);
//  delay(1000);
//  Test_Pixels(0, 10, LOW_P);
//  Test_Pixels(0, 9, LOW_P);
//  delay(1000);
  
//    Text_effect(100, I);
//    Text_effect(100, Tym);
//    Text_effect(100, U);
//    delay(200);
}

void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};

  /* now display them one by one with a small delay */
  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 7; j++)
    {
      SetRow(0,i, 0x01 << j);
      delay(100);    
    }
    delay(100);  
  }
}

void Shutdown(int addr, bool b) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(b)
        spiTransfer(addr, OP_SHUTDOWN,0);
    else
        spiTransfer(addr, OP_SHUTDOWN,1);
}

void SetScanLimit(int addr, int limit) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(limit>=0 && limit<8)
        spiTransfer(addr, OP_SCANLIMIT,limit);
}

void SetIntensity(int addr, int intensity) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(intensity>=0 && intensity<16)  
        spiTransfer(addr, OP_INTENSITY,intensity);
}

void ClearDisplay(int addr) {
    int offset;

    if(addr<0 || addr>=maxDevices)
        return;
    offset=addr*8;
    for(int i=0;i<8;i++) {
        Status[offset+i]=0;
        spiTransfer(addr, i+1,Status[offset+i]);
    }
}

void SetLed(int addr, int row, int column, boolean state) {
    int offset;
    byte val=0x00;

    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7 || column<0 || column>7)
        return;
    offset=addr*8;
    val=B10000000 >> column;
    if(state)
        Status[offset+row]=Status[offset+row]|val;
    else {
        val=~val;
        Status[offset+row]=Status[offset+row]&val;
    }
    spiTransfer(addr, row+1,Status[offset+row]);
}

void SetRow(int addr, int row, byte value) {
    int offset;
    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7)
        return;
    offset=addr*8;
    Status[offset+row]=value;
    spiTransfer(addr, row+1,Status[offset+row]);
}

void SetColumn(int addr, int col, byte value) {
    byte val;

    if(addr<0 || addr>=maxDevices)
        return;
    if(col<0 || col>7) 
        return;
    for(int row=0;row<8;row++) {
        val=value >> (7-row);
        val=val & 0x01;
        SetLed(addr,row,col,val);
    }
}

void spiTransfer(int addr, volatile byte opcode, volatile byte data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=maxDevices*2;

    for(int i=0;i<maxbytes;i++)
        spidata[i]=(byte)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line 
    digitalWrite(SPI_CS,LOW);
    //Now shift out the data 
    for(int i=maxbytes;i>0;i--)
        shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    digitalWrite(SPI_CS,HIGH);
}    
