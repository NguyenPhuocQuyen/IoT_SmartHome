// #include <Arduino.h>
// #include <WiFi.h>
// #include <WiFiClient.h>

// #include <ArduinoJson.h>

// const char* ssid = "NhatroDongAnh_T2";
// const char* password = "0935211678";

// #include <FirebaseESP32.h>



// #define FIREBASE_HOST "fir-esp32-17707-default-rtdb.firebaseio.com"
// #define FIREBASE_AUTH "R0B0EXUlahdmd2QDD75f112CEAg1MWvKkOcKxSD5"

// FirebaseData firebasedata ;

// FirebaseAuth auth;
// FirebaseConfig config;

// String path ="/";

// void setup() 
// {
//   Serial.begin(115200);
//   delay(200);
//   Serial.println();
//   Serial.print("Connecting to wifi: ");
//   Serial.println(ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.print("Connected with IP: ");
//   Serial.println(WiFi.localIP());
//   Serial.println();
//   Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

//   config.api_key = FIREBASE_AUTH;
//   config.database_url =FIREBASE_HOST ;
//   Firebase.reconnectWiFi(true);
//   Firebase.begin(&config, &auth);
//   Firebase.setDoubleDigits(5);


//   if (Firebase.ready())
//   {
//      if (!Firebase.beginStream(firebasedata, path))
//     {
//       Serial.println("REASON: " + firebasedata.errorReason());
//       Serial.println();
//     }
//       Serial.println("Connecting Success");
//       Serial.print("Connect with IP: ");
//       Serial.println(WiFi.localIP());
//       Serial.println();
//   }
  

  

// }

// void loop(){

//   //   int so = random(0, 99);
//   // if (Firebase.setString(firebasedata, "/set", String(so))) {
//   //   Serial.println("set: " + String(so));
//   // }

//   // // get data
//   // if (Firebase.getString(firebasedata, "/get")) {
//   //   String s = firebasedata.stringData();
//   //   Serial.println("get: " + s);
//   // }
// // if (Firebase.ready())
// // {
// //   Serial.printf("Firebase ready !");
// //   Firebase.setInt(firebasedata,path +"/data",1);
// // }
// // else{
// //   Serial.printf("Error ready Firebase !");
// // }

  


// }





