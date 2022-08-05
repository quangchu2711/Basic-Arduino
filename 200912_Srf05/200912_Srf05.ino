// Kết nối Arduino với cảm biến SRF05:
//    Arduino pin        SRF05 pin
//       10        ---     TRIGGER
//       11        ---     ECHO
//       VCC       ---     VCC
//       GND       ---     GND

int TRIGGER_PIN = 10; /*kích hoạt quá trình phát sóng âm, quá trình kích hoạt khi một chu kì điện cao / thấp diễn ra.*/
int ECHO_PIN    = 11; /*bình thường sẽ ở trạng thái 0V, được kích hoạt lên 5V ngay khi có tín hiệu trả về, sau đó trở về 0V.*/
#define time_out 30000 /*vượt quá 30000 us sẽ dừng bộ đếm thời gian và trả về giá trị 0*/

// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT); /*Xuất tín hiệu ở chân TRIP*/
  pinMode(ECHO_PIN, INPUT); /*Nhận tín hiệu ở chân ECHO*/
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  //int distance_cm = srf05.ping_cm();  // đo khoảng cách (đơn vị cm)
  long distance_cm = get_distance();
  if(distance_cm <= 0) Serial.println(500);
  else Serial.println(distance_cm);
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}

//Hàm trả về khoảng cách mà cảm biến đo được (đơn vị cm)
long get_distance()
{
  /*Cần truyền tín hiệu cho chân TRIGGER theo chu kỳ LOW HIGH LOW*/
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long time_value = pulseIn(ECHO_PIN, HIGH, time_out); /*sẽ trả về thời gian tín hiệu nhảy từ mức HIGH xuống LOW*/
  return time_value / 29.4 / 2.0; /*vận tốc âm thanh: 340m/s,  1cm đi được 29.4 us*/
}
