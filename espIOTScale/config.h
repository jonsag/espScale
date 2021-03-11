/**********
 * HX711
 **********/
#include "HX711.h" //You must have this library in your arduino library folder

#define DT D5
#define SCK D6

HX711 scale;

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
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
#include <LiquidCrystal_I2C.h>

// SCL -> D1
// SDA -> D2

LiquidCrystal_I2C lcd(0x27, 16, 2);

/**********
 * WiFi
 **********/
#include <ESP8266WiFi.h>

WiFiClient client;

/**********
 * Buttons
 **********/
int rbutton = D4; // this button will be used to reset the scale to 0

/**********
 * Misc
 **********/
float weight;
