// #include <Arduino.h>
// #include <FirebaseESP32.h>
// #include <WiFi.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <NTPClient.h>
// #include <WiFiUdp.h>
// #define WIFI_SSID "NhatroDongAnh_T2"
// #define WIFI_PASSWORD "0935211678"
// LiquidCrystal_I2C LCD(0x27,16,2);
// #define DATABASE_URL "iotsmarthome-e9c19-default-rtdb.firebaseio.com"
// #define DATABASE_SECRET "vdIBLbXiddF6F00VTNtw0jlU80gfBs7yEMlVAudG"
// WiFiUDP User_RT;
// NTPClient RT(User_RT,"pool.ntp.org",7*3600);
// unsigned long datamilis=0;
// FirebaseData firebase_smthome;
// /* 4, Define the FirebaseAuth data for authentication data */
// FirebaseAuth auth;

// /* Define the FirebaseConfig data for config data */
// FirebaseConfig config;
// String path ="/";
// void setup()
// {
// /* Declration Serial Monitor */
//     Serial.begin(115200);
// /* Intialization the Get realtime */
//     RT.begin();
//     RT.setTimeOffset(19800);

// /* LCD I2C starting */
//     LCD.init();
//     LCD.backlight();
//     LCD.begin(12,13);
//     LCD.print("Xin chao cac ban");
//     delay(300);
//     LCD.clear();

// /*Setup connect Wifi for ESP32*/
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//     Serial.print("Connecting to Wi-Fi");
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         Serial.print(".");
//         delay(100);
//     }
//     Serial.println();
//     Serial.print("Connected with IP: ");
//     Serial.println(WiFi.localIP());


// /* Assign the database URL and database secret(required) */
//     config.database_url = DATABASE_URL;
//     config.signer.tokens.legacy_token = DATABASE_SECRET;
//     Firebase.reconnectNetwork(true);
//     firebase_smthome.setBSSLBufferSize(4096 , 1024 );

// /* Initialize the library and connecting RTDB */
//     Firebase.begin(&config, &auth); /*Firebase.begin(DATABASE_URL, DATABASE_SECRET);*/
//     if (Firebase.ready())
//     {
//      if (!Firebase.beginStream(firebase_smthome, path))
//     {
//       Serial.println("Reason: " + firebase_smthome.errorReason());
//       Serial.println();
//     }
//       Serial.println("Connecting Success");
//       Serial.print("Connect with IP: ");
//       Serial.println(WiFi.localIP());
//       Serial.println();
//     }



// }

// void loop()
// {
//     u32_t current_Time = millis();
//     int Monthday;
//     int CurrentMonth;
//     int CurrentYear;
//     String CurrentDate;
//     String formattedTime;
//     if (current_Time - datamilis >500)
//     {
//         datamilis = current_Time;
//         RT.update();
//         time_t epochTime = RT.getEpochTime();
//         formattedTime = RT.getFormattedTime();
//         struct tm *ptm = gmtime ((time_t *)&epochTime);
//         Monthday = ptm->tm_mday;
//         CurrentMonth = ptm->tm_mon+1;
//         CurrentYear = ptm->tm_year+1900;
//         CurrentDate = String(Monthday)+ "/"+String(CurrentMonth)+"/"+String(CurrentYear);
//     }
//         LCD.setCursor(0,0);
//         LCD.print("DATE: "+CurrentDate);
//         LCD.setCursor(0,1);
//         LCD.print("Time: "+ formattedTime);
//         Serial.println(CurrentDate);
//         Serial.println(formattedTime);
// }

