// // #include <Arduino.h>
// // #include <driver/gpio.h>
// // #include <esp_adc_cal.h>

// // // #define Gas_Digital_Pin 39
// // // #define Gas_Analog_Pin 34


// // #define Gas_Analog_Pin GPIO_NUM_34

// // void setup()
// // {
// // Serial.begin(115200);
// // gpio_set_direction(Gas_Analog_Pin, GPIO_MODE_INPUT);
// // gpio_set_pull_mode(Gas_Analog_Pin, GPIO_PULLUP_PULLDOWN);
// // }

// // void loop()
// // {

// // int sensorValue_3 = analogRead(Gas_Analog_Pin);
// // Serial.println(sensorValue_3);
// // delay(200);

// // }
// #include <Arduino.h>
// #include <driver/adc.h>

// #define Gas_Analog_Pin GPIO_NUM_39

// void setup()
// {
//   Serial.begin(115200);

//   // Khởi tạo chân ADC
//   adc1_config_width(ADC_WIDTH_BIT_12);
//   adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);

//   // Khởi tạo chân GPIO
//   pinMode(Gas_Analog_Pin, INPUT);
// }

// void loop()
// {
//   // Đọc giá trị analog từ chân ADC
//   int sensorValue_3 = adc1_get_raw(ADC1_CHANNEL_3);
//   Serial.println(sensorValue_3);
//   delay(200);
// }