
/*
 * Author: Thanh Le Duc
 * Created on Tue Mar 19 2024
 * Copyright (c) 2024 Your Company
 */

/************************************************************************************************************
 * Includes
 ************************************************************************************************************/
#include <Arduino.h>
#include <WiFi.h>              /* Library for used to connect WiFi with ESP32 */
#include <FirebaseESP32.h>     /* Library for connect to Firebase console    */
#include <Adafruit_Sensor.h>   /* Library for sensor */
#include <DHT.h>               /* Library for DHT11 sensor */
#include <DHT_U.h>             /* Library for DHT11 sensor */
#include <Wire.h>              /* Library for Wire I2C */
#include <LiquidCrystal_I2C.h> /* Library for I2C LCD */
#include <ESP32Time.h>         /* Library for display time */
#include <driver/adc.h>        /* Library for ADC channel */
#include <ESP32Servo.h>
#include <addons/RTDBHelper.h> /* Provide the RTDB payload printing info and other helper functions.*/
#include <HardwareSerial.h>
/************************************************************************************************************
 * Definitions
 ************************************************************************************************************/

/* Define the Wifi Credentials */

#define WIFI_SSID "NhatroDongAnh_T2" /* Define the WiFi credentials */
#define WIFI_PASSWORD "0935211678"   /* Define the WiFi Password */

/* Define Pin Sensor of Schematic - Input */

#define TCRT500_Analog_Sensor_Pin GPIO_NUM_36 /* Define the DHT11 Sensor Pin */
#define Digital_Gas_Pin GPIO_NUM_34           /* Define the Digital Gas Sensor Pin */
#define Gas_Analog_Pin GPIO_NUM_39            /* Define the Analog Gas Sensor Pin */
#define Flame_Analog_Sensor_Pin GPIO_NUM_35   /* Define the Analog Flame Sensor Pin */
#define Fan_Pin GPIO_NUM_15
// #define Flame_Digital_Sensor_Pin 32                       /* Define the Digital Flame Sensor Pin */
#define DHT11_Pin GPIO_NUM_33                  /* Define the Analog TCRT5000 Sensor Pin */
#define TCRT500_Digital_Sensor_Pin GPIO_NUM_25 /* Define the Digital TCRT5000 Sensor Pin */

#define I2C_SDA 21 /* Define the SDA LCD Pin */
#define I2C_SCL 22 /* Define the SCL LCD Pin */

#define DHTType DHT11 /* Define the Sensor type */

Servo servo;
uint8_t servoPin = 26;

/* If work with RTDB, define the RTDB URL and database secret */
/* Duc Thanh */
// #define DATABASE_URL "fir-esp32-17707-default-rtdb.firebaseio.com" /* Define the RTDB URL*/
// #define DATABASE_SECRET "R0B0EXUlahdmd2QDD75f112CEAg1MWvKkOcKxSD5" /* Define the RTDB secret*/
/* Phuoc quyen */
#define DATABASE_URL "iotsmarthome-e9c19-default-rtdb.firebaseio.com" /* Define the RTDB URL*/
#define DATABASE_SECRET "vdIBLbXiddF6F00VTNtw0jlU80gfBs7yEMlVAudG"    /* Define the RTDB secret*/

/************************************************************************************************************
 * Prototypes
 ************************************************************************************************************/

uint16_t GasSensor();
/*
 * brief: Function to read gas sensor analog signal.
 */
void DHT11Sensor(float_t &Temp, float_t &Humi);
/*
 * @brief : Function to read Dht11 sensor analog signal.
 * @param Temp :Temperature value of Dht11 sensor.
 * @param Humi :Humidity value of Dht11 sensor.
 */
void LCD_DHT11();
/*
 * brief: Function to display Dht11 sensor analog signal on LCD.
 */
void LCD_Time();
/*
 * brief: Function to display time on LCD.
 */
void IRAM_ATTR gasDetectISR();
/*
 * brief: Function to interrupt of Gas sensor.
 */
uint16_t FlameSensor();
/*
 * brief: Function to read flame sensor analog signal.
 */
uint16_t LightSensor();
/*
 * brief: Function to read light sensor analog signal.
 */
uint16_t TCRT5000DigitalSensor();
/*
 * brief: Function to read Tcrt5000 sensor digital signal.
 */
void Control_Fan(bool n);
/*
 * brief: Function to control Fan.
 */

/* Create a char for Temp */
byte degree[8] = {0B01110, 0B01010, 0B01110, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};

/************************************************************************************************************
 * Declaration
 ************************************************************************************************************/

FirebaseData firebase_smthome; /* Define the name RTDB */

ESP32Time rtc(0); /* Define the name RT in ESP32 */

DHT_Unified DHT(DHT11_Pin, DHTType); /* Define the name DHT11 sensor*/

LiquidCrystal_I2C LCD(0x27, 16, 2); /* Define the name LCD */

FirebaseAuth auth; /* Define the FirebaseAuth data for authentication data */

FirebaseConfig config; /* Define the FirebaseConfig data for config data */

/************************************************************************************************************
 * Variables
 ************************************************************************************************************/

unsigned long dataMillis = 0; /* Variables for millis2 */

uint32_t delayms; /* Variables for delay of Dht11 sensor*/

String path = "/";             /* Variables for receive data from rtdb*/
boolean Set_interrupt = false; /* Variables for interrupts*/
const uint16_t freq = 5000;    /* Config the frequency for PWM*/
const uint8_t ledChannel1 = 3; /* Config the channel 0 for PWM*/
const uint8_t ledChannel2 = 4; /* Config the channel 1 for PWM*/
const uint8_t resolution = 8;  /* Config the resolution for PWM*/
const uint8_t Led_02_Pin = 18; /* Config the Led 2 Pin for PWM*/
const uint8_t Led_01_Pin = 19; /* Config the Led 1 Pin for PWM*/

void setup()
{
    Serial2.begin(9600);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    servo.setPeriodHertz(50); // standard 50 hz servo
    servo.attach(servoPin, 500, 2400);
    /* Config the ADC channel */
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

    /* PinMode */
    pinMode(Flame_Analog_Sensor_Pin, INPUT);
    pinMode(Gas_Analog_Pin, INPUT);
    pinMode(TCRT500_Analog_Sensor_Pin, INPUT);
    pinMode(TCRT500_Digital_Sensor_Pin, INPUT_PULLUP);
    pinMode(DHT11_Pin, INPUT);
    pinMode(Fan_Pin, OUTPUT);

    // Configure LED PWM functionalitites
    ledcSetup(ledChannel1, freq, resolution);
    ledcSetup(ledChannel2, freq, resolution);

    // Attach the channel to the GPIO to be controlled
    ledcAttachPin(Led_01_Pin, ledChannel1);
    ledcAttachPin(Led_02_Pin, ledChannel2);

    /* Declaration Serial Monitor */
    Serial.begin(115200);
    delay(200);

    /*DHT11 sensor starting*/
    sensor_t sensor;
    delayms = sensor.min_delay / 1000;
    DHT.begin();

    /* LCD I2C starting */
    Wire.begin(I2C_SDA, I2C_SCL);
    LCD.init();
    LCD.backlight();
    LCD.begin(12, 13);
    LCD.setCursor(0, 0);
    LCD.createChar(1, degree);
    LCD.clear();

    /* Config the Interrupt */
    attachInterrupt(digitalPinToInterrupt(Digital_Gas_Pin), gasDetectISR, RISING);

    /*Setup connect Wifi for ESP32*/
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the database URL and database secret(required) */
    config.database_url = DATABASE_URL;
    config.signer.tokens.legacy_token = DATABASE_SECRET;
    Firebase.reconnectNetwork(true);
    firebase_smthome.setBSSLBufferSize(8192, 8192);

    /* Initialize the library and connecting RTDB */
    Firebase.begin(&config, &auth); /* Firebase.begin(DATABASE_URL, DATABASE_SECRET); */
    if (Firebase.ready())
    {
        if (!Firebase.beginStream(firebase_smthome, path))
        {
            Serial.println("Reason: " + firebase_smthome.errorReason());
            Serial.println();
        }
        Serial.println("Connecting Success");
        Serial.print("Connect with IP: ");
        Serial.println(WiFi.localIP());
        Serial.println();
    }
    /* Initial the realtime */
    rtc.setTime(0, 50, 13, 3, 4, 2024);
}

void loop()
{
    /* Initial variables */

    boolean Set_RedAlertTime = false; /* Variables for gas alert */
    boolean Set_DataReceive1 = false; /* Variables for receive data 01 from rtdb*/
    uint8_t Set_DataReceive2 = 0;     /* Variables for receive data 02 from rtdb*/
    boolean Set_DataReceive3 = false; /* Variables for receive data 03 from rtdb*/
    boolean Set_DataReceive4 = false;
    boolean Set_DataReceive5 = false;
    String Set_DataReceive6;
    boolean Switch_LCD = true; /* Variables for receive data switch LCD from rtdb*/
    __volatile uint16_t Gas_value = 0;
    __volatile uint16_t Flame_value = 0;
    __volatile uint16_t Light_value = 0;
    __volatile uint16_t TCRT_digital = 0;
    float_t temperature;
    float_t humidity;
    /* Create realtime based on ESP32Time library */

    // Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); // (String) returns time with specified format
    if (Set_DataReceive3 == 0)
    {
        LCD_DHT11();
    }
    else
    {
        LCD_Time();
    }

    /*Task of Interrupt*/
    if (Set_interrupt == true)
    {
        // Serial.println("Red Alert, Red Alert...");
        Set_RedAlertTime = true;
    }
    if (Set_RedAlertTime == true)
    {
        digitalWrite(Led_01_Pin, HIGH); // Set the led status in Red Alert Case.
        if (digitalRead(Digital_Gas_Pin) == 1)
        {
            digitalWrite(Led_01_Pin, LOW);
            Set_RedAlertTime = false;
            Set_interrupt = false;
        }
    }

    /* Get and set Data to Firebase */
    unsigned long currentTime = millis();
    if (currentTime - dataMillis > 1000)
    {
        /* Create the time delay by millis */
        dataMillis = currentTime;
        /* Read and send Gas sensor value to RTDB */
        Gas_value = GasSensor();
        Flame_value = FlameSensor();
        Light_value = LightSensor();
        TCRT_digital = TCRT5000DigitalSensor();
        Serial.printf("Gia tri Gas sensor: ");
        Serial.println(Gas_value);
        // Serial.printf("Gia tri Flame sensor: ");
        // Serial.println(Flame_value);
        // Serial.printf("Gia tri TCRT5000 sensor: ");
        // Serial.println(TCRT_value);
        // Serial.printf("Gia tri TCRT5000 digital sensor: ");
        // Serial.println(TCRT_digital);
        if (isnan(Gas_value))
        {
            if (Firebase.setString(firebase_smthome, "/Gassensor", "Gas Sensor Error !")) /* Firebase.setInt(firebase_smthome,path +"/Key on Firebase",Data); */
            {
                Serial.println("Gas Sensor Error !");
            }
        }
        else
        {
            Serial.printf("Gas Sensor operating!\n");
            Firebase.setString(firebase_smthome, "/Gassensor", String(Gas_value));
        }

        /* Read and send DHT11 sensor value to RTDB */
        DHT11Sensor(temperature, humidity);
        if (isnan(temperature) or isnan(humidity))
        {
            // Serial.println("DHT11 Error !");
        }
        else
        {
            Firebase.setString(firebase_smthome, "/DHT11Sensor/Humi", String(humidity));
            Firebase.setString(firebase_smthome, "/DHT11Sensor/Temp", String(temperature));
        }
        /* Get data from RTDB for LED1 */
        if (Firebase.getString(firebase_smthome, "/Led/Led1Status"))
        {
            int s1 = firebase_smthome.intData();
            Serial.println("Led1: ");
            Serial.println(s1);
            Set_DataReceive1 = s1;
            // Serial.print(Set_DataReceive1);
        }
        /* Get data from RTDB for LED2 */
        if (Firebase.getString(firebase_smthome, "/Led/Led2Status"))
        {
            int s2 = firebase_smthome.intData();
            Serial.println("Led2: ");
            Serial.println(s2);
            Set_DataReceive2 = s2;
            // Serial.print(Set_DataReceive2);
        }
        /* Get data from RTDB  for LCD */
        if (Firebase.getInt(firebase_smthome, "Switch"))
        {
            String s3 = firebase_smthome.stringData();
            if (s3 == "1")
            {
                Set_DataReceive3 = true;
            }
            if (s3 == "0")
            {
                Set_DataReceive3 = false;
            }
            // Serial.println("LCD: " + s3);
        }
        if (Firebase.getString(firebase_smthome, "/Span/Span1Status"))
        {
            String s4 = firebase_smthome.stringData();
            if (s4 == "1")
            {
                Set_DataReceive4 = true;
            }
            if (s4 == "0")
            {
                Set_DataReceive4 = false;
            }
        }
        /* Get data from RTDB for Curtain */
        if (Firebase.getString(firebase_smthome, "/Rem/Rem1Status/"))
        {
            String s5 = firebase_smthome.stringData();
            if (s5 == "1")
            {
                Set_DataReceive5 = true;
                // Serial.println("Rem: " + s5);
            }
            if (s5 == "0")
            {
                Set_DataReceive5 = false;
                // Serial.println("Rem: " + s5);
            }
        }
        /* Get data from RTDB for Password */
        if (Firebase.getString(firebase_smthome, "PasswordDoor/password/"))
        {
            String s6 = firebase_smthome.stringData();
            Set_DataReceive6 = s6;
            Serial.println("Password: " + Set_DataReceive6);
            Serial2.print(Set_DataReceive6 +"/");
        }
        /* Get data from RTDB for Door */
        if (Firebase.getInt(firebase_smthome, "Cua/Cua1Status/"))
        {
            int s7 = firebase_smthome.intData();
            if (s7 == 1)
            {
                Serial2.print("1/");
            }
            if (s7 == 0)
            {
                Serial2.print("0/");
            }
        }
    }

    /* Output LED 1*/
    ledcWrite(ledChannel1, Set_DataReceive1);

    /* Output LED 2*/
    ledcWrite(ledChannel2, Set_DataReceive2);

    /* Control Fan*/

    if (Set_DataReceive4 == true)
    {
        digitalWrite(Fan_Pin, HIGH);
    }
    else
    {
        digitalWrite(Fan_Pin, LOW);
    }

    /* Control Curtain */
    if (Set_DataReceive5 == true)
    {
        for (int i = 0; i < 360; i++)
        {
            servo.write(i);
        }
    }
    else
    {
        for (int i = 360; i > 0; i--)
        {
            servo.write(i);
        }
    }
}

/* Function: Read Gas sensor value */
uint16_t GasSensor()
{
    __volatile uint16_t Gas_value = adc1_get_raw(ADC1_CHANNEL_3);

    return Gas_value;
}
/* Function: Read Flame sensor value */
uint16_t FlameSensor()
{
    __volatile uint16_t Flame_value = ((adc1_get_raw(ADC1_CHANNEL_7) * 1000) / 4096);

    return Flame_value;
}
/* Function: Read TCRT5000 sensor value */
uint16_t LightSensor()
{
    __volatile uint16_t TCRT5000_value = ((adc1_get_raw(ADC1_CHANNEL_0) * 100) / 4096);

    return TCRT5000_value;
}

uint16_t TCRT5000DigitalSensor()
{
    __volatile uint16_t TCRT5000_Digital = digitalRead(TCRT500_Digital_Sensor_Pin);

    return TCRT5000_Digital;
}
/* Function: Read DHT11 sensor value */
void DHT11Sensor(float_t &Temp, float_t &Humi)
{
    sensors_event_t event;
    DHT.temperature().getEvent(&event);
    Temp = event.temperature;
    DHT.humidity().getEvent(&event);
    Humi = event.relative_humidity;
}

/* Function: Control the Fan by relay module */
void Control_Fan(bool n)
{
    if (n == true)
    {
        digitalWrite(Fan_Pin, HIGH);
    }
    else
    {
        digitalWrite(Fan_Pin, LOW);
    }
}

/* Function Interrupt */
void IRAM_ATTR gasDetectISR()
{
    Set_interrupt = true;
}
/* Function Dht11 - LCD Display */
void LCD_DHT11()
{
    float_t temperature1;
    float_t humidity1;
    DHT11Sensor(temperature1, humidity1);
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Temp: ");
    LCD.print(temperature1);
    LCD.write(1);
    LCD.print("C");
    LCD.setCursor(0, 1);
    LCD.print("Humi: ");
    LCD.print(humidity1);
    LCD.print(" %");
}
/* Function Time - LCD Display */
void LCD_Time()
{
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Date: ");
    LCD.print(rtc.getDay());
    LCD.print("/");
    LCD.print(rtc.getMonth());
    LCD.print("/");
    LCD.print(rtc.getYear());
    LCD.setCursor(0, 1);
    LCD.print("Time: ");
    LCD.print(rtc.getTime());
    struct tm timeinfo = rtc.getTimeStruct();
}
