// Kết nối Arduino với thStepper:
//    Arduino pin       thStepper pin
//       10        ---    I3
//       11        ---    I2
//       12        ---    I1
//       13        ---    I0
//       VCC      ---     V+
//       GND      ---     GND
// Kết nối Arduino với biến trở:
//    Arduino pin       thKnob pin
//       A3        ---     VAR
//       VCC       ---     A
//       GND       ---     B

int I0_pin = 13;
int I1_pin = 12;
int I2_pin = 11;
int I3_pin = 10;

#include <Stepper.h>
Stepper myStepper(64, I0_pin, I2_pin, I1_pin, I3_pin);
int stepsPerRevolution = 2048;  // số bước để động cơ quay đủ 1 vòng

int knob_sensor_pin = A3;

// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);               // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến

}

// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int knob_value = analogRead(knob_sensor_pin);                // đọc giá trị cảm biến
  //Serial.print(knob_value);                                     // in kết quả ra màn hình
  //Serial.print(" -- ");    
  int speed_value = (float)(knob_value * 500.0) / 1023.0;  // Khởi tạo Giá trị tốc độ quay
  //int speed_value = (int) (knob_value * 0.48);                // Khởi tạo Giá trị tốc độ quay
  //Serial.print(speed_value);
  //Serial.println();
  //if(speed_value <= 15) speed_value = 0;    
  myStepper.setSpeed(speed_value);                   
  myStepper.step(1);
  //delay(1);                      
}

/*Mỗi bước của động cơ quét 1 góc 5.625 độ, vậy để quay 1 vòng động cơ phải thực hiện 64 bước.*/
/*corner: Góc quay (0 -> 360); Speed (): Tốc độ quay , Mặc định là quay thuận*/
void rotation_Speed(long rotation, int MySpeed)
{
  long res = (long)((rotation * 2048) / 360);
  myStepper.setSpeed(MySpeed);  //Đặt tốc độ
  myStepper.step(res);          // quay thuận
}

/*Sử dụng thKnob điều chỉnh tốc độ quay của động cơ bước*/
void speed_adjustment(long step_value)
{
  int knob_value = analogRead(knob_sensor_pin);         // đọc giá trị cảm biến
  Serial.println(knob_value);                           // in kết quả ra màn hình
  long speed_value = (long) (knob_value * 500 / 1023);  // Khởi tạo Giá trị tốc độ quay
  myStepper.setSpeed(speed_value);                      // Giá trị tốc độ quay
  myStepper.step(step_value);                           // Giá trị bước quay thuận (từ 0 đến 2048)
}
