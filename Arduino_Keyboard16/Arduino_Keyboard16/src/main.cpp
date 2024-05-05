// #include <Arduino.h>
// #include <Keypad.h>
// #include <Servo.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>      // Khai báo thư viện LCD sử dụng I2C
// LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 địa chỉ LCD, 16 cột và 2 hàng
// Servo myservo; //Tạo biến myServo của loại Servo

// //Tạo ký tự đặc biệt &
//  byte va[] = {
//   B00000,
//   B01100,
//   B10010,
//   B10100,
//   B01000,
//   B10101,
//   B10010,
//   B01101
// };
// const byte ROWS = 4;
// const byte COLS = 4;
// char password[5];
// char On_equip[]="4242"; // Mật khẩu mở cửa
// char Off_equip[]="C"; // Mật khẩu đóng cửa
// int i = 0;
// int on=0;
// int servo = 10;
// int RedLed = 13;

// char MatrixKey[ROWS][COLS] =
// {
//   {'1','2','3','A'},
//   {'4','5','6','B'},
//   {'7','8','9','C'},
//   {'*','0','#','D'}
// };
// byte rowPins[ROWS] = {26,28,30,32}; // R1,R2,R3,R4
// byte colPins[COLS] = {34,36,38,40}; // C1,C2,C3,C4

// Keypad Mykeys = Keypad( makeKeymap(MatrixKey), rowPins, colPins, ROWS, COLS);

// //=================================================================================================================

// void setup()
// {
//   Serial.begin(9600);
//   pinMode(RedLed,OUTPUT);

//   lcd.init(); // Khởi tạo màn hình Màn hình
//   lcd.backlight(); // Bật đèn màn hình Màn hình
//   lcd.createChar(0, va); // Tạo ký tự đặc biệt &

//   myservo.attach(servo);
//   myservo.write (0);

// // Hiện chữ M&E Automation
//   lcd.setCursor(1, 0); // Di chuển con trỏ đến cột 1 và hàng 0
//   lcd.print("M");
//   lcd.setCursor(2, 0);
//   lcd.write(byte(0)); // in ký tự đặc biệt đã tạo &.
//   lcd.setCursor(3, 0);
//   lcd.print("E");
//   lcd.setCursor(5, 0);
//   lcd.print("Automation");
//   delay(1000);
//   lcd.clear();
//   lcd.print(" Enter Password");
// }
// //=================================================================================================================

// void loop()
// {
//   char EnterKey = Mykeys.getKey();

//  if (EnterKey)
//  {
//     password[i]=EnterKey; // Nhập lần lượt các ký tự vào biến chuỗi ký tự Psssword
//     i++;
//     on++;
//     Serial.println(password);
//     // Nhập mật khẩu
//     if (i == 0) {
//       password[0] = EnterKey;
//       lcd.setCursor(6, 1);
//       lcd.print(password[0]);
//       delay(500); // Ký tự hiển thị trên màn hình LCD trong 0.5s
//       lcd.setCursor(6, 1);
//       lcd.print("*"); // Ký tự được thay bởi dấu *
//     }
//     if (i == 1) {
//       password[1] = EnterKey;
//       lcd.setCursor(7, 1);
//       lcd.print(password[1]);
//       delay(500);
//       lcd.setCursor(7, 1);
//       lcd.print("*");
//     }
//     if (i == 2) {
//       password[2] = EnterKey;
//       lcd.setCursor(8, 1);
//       lcd.print(password[2]);
//       delay(500);
//       lcd.setCursor(8, 1);
//       lcd.print("*");
//     }
//     if (i == 3) {
//       password[3] = EnterKey;
//       lcd.setCursor(9, 1);
//       lcd.print(password[3]);
//       delay(500);
//       lcd.setCursor(9, 1);
//       lcd.print("*");
//     }
//  }
//              if(on==4)
//                  {
//                 if(!strcmp(password,On_equip))
//                   {
//                     lcd.clear();
//                     lcd.print("    Correct!");
//                     myservo.write(180); // Mở cửa!
//                     digitalWrite(RedLed,LOW);
//                     delay(1000);
//                     lcd.clear();
//                     lcd.print("      Opened!");
//                     i=0;
//                     Serial.println(" Dung mat khau mo cua!");
//                   }

//                  if(!strcmp(password,Off_equip))
//                  {
//                     lcd.clear();
//                     myservo.write(0); // Đóng cửa
//                     lcd.print("     Closed!");
//                     digitalWrite(RedLed,LOW);
//                     delay(2000);
//                     lcd.clear();
//                     lcd.print(" Enter Password");
//                     i=0;
//                   }

//                   if(strcmp(password,On_equip))
//                   {
//                     if(strcmp(password,Off_equip))
//                     {

//                     lcd.clear();
//                     lcd.print("   Incorrect!");
//                     delay(1000);
//                     lcd.clear();
//                     lcd.print("   Try Again!");
//                     delay(1000);
//                     lcd.clear();
//                     lcd.print(" Enter Password");
//                     i = 0;
//                     Serial.println(" Sai mat khau nhap lai.............");
//                     digitalWrite(RedLed,HIGH);

//                     }
//                   }
//                   on=0;
//                   }
//  }