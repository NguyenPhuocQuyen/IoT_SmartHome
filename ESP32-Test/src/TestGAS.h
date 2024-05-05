// #include <Arduino.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>


// #ifndef _Arduino.h_

//     #define _Arduino.h_

// #endif /* <Arduino.h> */



// #define INPUT_PIN 32
// #define DHT11Pin 25
// #define DHTType DHT11
// DHT_Unified DHT(DHT11Pin,DHTType);
// uint32_t delayms ;

// void setDHT11(){

//   Serial.println(F("DHTxx Unifield Sensor"));
//   sensor_t sensor ;
// //print temperature details
//   DHT.temperature().getSensor(&sensor) ;
//   Serial.println(F("-------------------------------------------"));
//   Serial.println(F("Temperature Sensor"));
//   Serial.println(F("Sensor Type: "));
//   Serial.println(sensor.name);
//   Serial.println(F("-------------------------------------------"));
// //print humidity details
//   DHT.humidity().getSensor(&sensor) ;
//   Serial.println(F("-------------------------------------------"));
//   Serial.println(F("Humidity Sensor"));
//   Serial.println(F("Sensor Type: "));
//   Serial.println(sensor.name);
//   Serial.println(F("-------------------------------------------"));
//   delayms = sensor.min_delay /1000;
//   DHT.begin();
  
// }

// float DHT11Sensor(){

// delay(delayms);
// sensors_event_t event;
// float Temp;
// float Humi;
// DHT.temperature().getEvent(&event);
// if(isnan(event.temperature))
//  {
//     Serial.println(F("Error reading temperature !"));
//  }
//  else
//  {
//     Temp = event.temperature;
//  }

//  DHT.humidity().getEvent(&event);
//  if(isnan(event.relative_humidity))
//  {
//     Serial.println(F("Error reading humidity !"));

//  }
//  else
//  {
//     Humi = event.relative_humidity;

//  }
//  return Temp,Humi;
// }
// int GasSensor(){
//     float value = analogRead(INPUT_PIN); //Đọc giá trị cảm biến và gán vào biến gia tri
//     return value;
// }


