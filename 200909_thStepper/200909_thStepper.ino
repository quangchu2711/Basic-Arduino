// Kết nối Arduino với thStepper:
//    Arduino pin       thStepper pin
//       10        ---    I3
//       11        ---    I2
//       12        ---    I1
//       13        ---    I0
//       VCC      ---     V+
//       GND      ---     GND

int I0_pin = 13;
int I1_pin = 12;
int I2_pin = 11;
int I3_pin = 10;

void setup()
{
  pinMode(I0_pin, OUTPUT);
  pinMode(I1_pin, OUTPUT);
  pinMode(I2_pin, OUTPUT);
  pinMode(I3_pin, OUTPUT);
  myStepper(I0_pin, I2_pin, I1_pin, I3_pin);
}

void myStepper(int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4)
{
  motor_pin_1 = I0_pin;
  motor_pin_2 = I2_pin;
  motor_pin_3 = I1_pin;
  motor_pin_4 = I3_pin;
}

void loop()
{
 myStepper(I0_pin ,I0_pin, I2_pin, I1_pin, I3_pin);
  
}
//#include <Stepper.h>
//Stepper myStepper(64, I0_pin, I2_pin, I1_pin, I3_pin);
//
//int stepsPerRevolution = 2048;  // số bước để động cơ quay đủ 1 vòng
//
//
//// Hàm setup() chạy một lần:
//void setup() 
//{
//  Serial.begin(9600); 
//}
//
//
//// Hàm loop() chạy lặp lại vô hạn:
//void loop() 
//{
//  Serial.print(I0_pin);
//  Serial.print(I1_pin);
//  Serial.print(I2_pin);
//  Serial.print(I3_pin);
//  Serial.println();
//  int mySpeed = 300;
//  myStepper.setSpeed(mySpeed);              // đặt tốc độ = 300
//  myStepper.step(stepsPerRevolution);       // quay thuận 1 vòng
//  
//  delay(1000);                              // dừng 1s
//
//  mySpeed = 150;
//  myStepper.setSpeed(mySpeed);              // đặt tốc độ = 150
//  myStepper.step(-stepsPerRevolution / 2);  // quay ngược 1/2 vòng
//  
//  delay(1000);                              // dừng 1s
//}
