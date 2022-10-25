String programName = "espIOTScale";
String date = "20221025";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/**********
 * Type of LCD
 **********/
// I2C or 595
#define LCDType I2C

/**********
 * HX711
 **********/
#include "HX711.h" //You must have this library in your arduino library folder

#define DT D5
#define SCK D6

HX711 scale;

// Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -21215; // -21215 worked for my 4x50Kg max scale setup

/**********
 * Serial
 **********/
const int serialSpeed = 115200;

/**********
 * LCD
 **********/
// use the library at https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library, not the one installed by Arduino IDE's library manager
#include <Wire.h>

#define lcdColumns 16
#define lcdRows 2

#if LCDType == I2C
#include <LiquidCrystal_I2C.h>

// SCL -> D1
// SDA -> D2

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

#elif LCDType == 595
#include <LiquidCrystal595.h> // include the library

#define data D3
#define latch D7
#define clock D8

LiquidCrystal595 lcd(data, latch, clock); // datapin, latchpin, clockpin

#endif

/**********
 * WiFi
 **********/
#include <ESP8266WiFi.h>

WiFiClient client;

/**********
 * Buttons
 **********/
#define rbutton D4 // this button will be used to reset the scale to 0

/**********
 * Blynk
 **********/
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

/**********
 * Misc
 **********/
float weight;
float oldWeight = -1;

unsigned long currentMillis;
unsigned long lastReadMillis = 0;

const int iterationMillis = 2000;
