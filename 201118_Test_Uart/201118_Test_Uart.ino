
void setup()
{
 Serial.begin(9600); 
}
uint32_t Num = 0x7fffff11;
byte Num1 = 0b11;

void Test(uint32_t data)
{
  uint8_t data1 = (uint8_t) data;
  uint8_t data2 = (uint8_t) (data >> 8);
  uint8_t data3 = (uint8_t) (data >> 16);
  uint8_t data4 = (uint8_t) (data >> 24);

  Serial.println("KQ");
  Serial.println(data1, BIN);
  Serial.println(data2, BIN);
  Serial.println(data3, BIN);
  Serial.println(data4, BIN);
  delay(3000);
}

uint32_t dich = 0x00000001;
void loop()
{
   uint32_t Data_out = (Data_out & ~((uint32_t)(dich << 24)) | ((uint32_t)(dich << 24)));
   Test(Data_out);
}
