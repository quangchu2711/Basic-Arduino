/*-------------------------------------------------------------------------------*/
//the opcodes for the MAX7221 and MAX7219
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
/*-------------------------------------------------------------------------------*/
#define SPI_MOSI 12   //DIN
#define SPI_CLK 11    //CLK
#define SPI_CS 10     //CS
/*-------------------------------------------------------------------------------*/
byte Status[64] = {0};
byte spidata[8] = {0};
int maxDevices = 4;
/*-------------------------------------------------------------------------------*/
void setup() 
{
  pinMode(SPI_MOSI,OUTPUT);
  pinMode(SPI_CLK,OUTPUT);
  pinMode(SPI_CS,OUTPUT);
  //Đặt lại chân Load
  digitalWrite(SPI_CS,HIGH);        
  for(int i=0;i<64;i++)
  {
    Status[i] = 0x00;     
  }
  for(int i=0;i<maxDevices;i++) 
  {
    //Kiểm tra ledMatric
    spiTransfer(i, OP_DISPLAYTEST, 0);
    //Chế độ quét Led (0 - 7)
    SetScanLimit(i,7);
    //Chế độ giải mã
    spiTransfer(i,OP_DECODEMODE,0);
    //Xóa dữ liệu trên LedMatric
    ClearDisplay(i);
    //Bật ledMatric
    Shutdown(i, false);
    //Đặt cường độ sáng của ledMatric (0 - 15)
    SetIntensity(i, 5);
   }
}
/**********************************************************************************************/
uint32_t Data_out_index[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void Test_Pixels(int row, int col, uint32_t state, uint32_t Data_out)
{
  Data_out = (Data_out & ~((uint32_t)(1 << col)) | ((uint32_t)(state << col)));
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
  for(int i = 1 ; i <= 8; i++)
  {
    if(row == i) Data_out_index[i - 1] = Data_out;
  }
}
/**********************************************************************************************/
void Set_Led_Pixels(int row, int col, uint32_t state)
{
  row = 7 - row;
  for(int i = 1; i <= 8; i++)
  {
      if(row == i - 1) Test_Pixels(row, col, state, Data_out_index[i - 1]);    
  }
}
/**********************************************************************************************/
void loop()
{
  Test_demo();
}
/**********************************************************************************************/
void Test_demo()
{
  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 31; j++)
    {
      Set_Led_Pixels(i, j, HIGH);
      delay(10);
    }
  }
  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 31; j++)
    {
      Set_Led_Pixels(i, j, LOW);
      delay(10);
    }
  }
}
/**********************************************************************************************/
void Shutdown(int addr, bool b) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(b)
        spiTransfer(addr, OP_SHUTDOWN,0);
    else
        spiTransfer(addr, OP_SHUTDOWN,1);
}
/**********************************************************************************************/
void SetScanLimit(int addr, int limit) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(limit>=0 && limit<8)
        spiTransfer(addr, OP_SCANLIMIT,limit);
}
/**********************************************************************************************/
void SetIntensity(int addr, int intensity) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(intensity>=0 && intensity<16)  
        spiTransfer(addr, OP_INTENSITY,intensity);
}
/**********************************************************************************************/
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
/**********************************************************************************************/
void SetLed(int addr, int row, int column, boolean state) 
{
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
/**********************************************************************************************/
void SetRow(int addr, int row, byte value) 
{
    int offset;
    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7)
        return;
    offset=addr*8;
    Status[offset+row]=value;
    spiTransfer(addr, row+1,Status[offset+row]);
}
/**********************************************************************************************/
void SetColumn(int addr, int col, byte value) 
{
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
/**********************************************************************************************/
void spiTransfer(int addr, uint8_t opcode, uint8_t data) {
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
/**********************************************************************************************/    
