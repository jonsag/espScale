#include <ESP8266WiFi.h>
#include <HX711_ADC.h>
//#include <LiquidCrystal_I2C.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "arduino-wifi-trial.firebaseio.com"
#define FIREBASE_AUTH "2zFMnhypKoDGt88N1IuuqmZvEfmEwL7AxHDmKpaS"

char ssid[] = "TECNO L9 Plus";
char pass[] = "deedee97";

//HX711 scale(5, 4); //D1, D2
HX711_ADC LoadCell(5, 4); //D1, D2
//LiquidCrystal_I2C lcd(0x3F,18,2);

unsigned long interval = 11;
unsigned long previousMillis = 0;

long t;

int ledpin = 13; //D7
int button = 12; //D6
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  delay(200);
  pinMode(ledpin,OUTPUT);
  pinMode(button,OUTPUT);  

  Serial.println("connecting to");

  //initiating the wifi connection
  WiFi.disconnect();
  Serial.println("disconnected");
  WiFi.begin(ssid,pass);

   while (WiFi.status() != WL_CONNECTED)
   {
//            unsigned long currentMillis=millis();
//        if ((unsigned long) (currentMillis-previousMillis)>=interval){
          Serial.print(".");
          delay(10);          
          //saves the "current" time
//          previousMillis = millis();
//        }
    }

  Serial.println("done!");
  Serial.print("SSID...,");
  Serial.println(WiFi.SSID());
  Serial.println("Successfully connected...");

  Serial.print("IP Address allocated to NodeMCU ESP8266");
  Serial.println(WiFi.localIP());

  Serial.print("MAC Address of ESP...");
  Serial.println(WiFi.macAddress());
  WiFi.printDiag(Serial);

  LoadCell.begin();
  Serial.println("begun");
  long stabilisingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilising time
  LoadCell.start(stabilisingtime);
  Serial.println("stable");
  LoadCell.setCalFactor(99500.0); // user set calibration factor (float)
  Serial.println(LoadCell.getCalFactor());
  Serial.println("Startup + tare is complete");

//  digitalWrite(ledpin, HIGH); 
//  delay(2000);
//  digitalWrite(ledpin, LOW); 

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

//  lcd.begin(18,2);
//  lcd.init();
//  lcd.backlight();

}
void loop() {
  LoadCell.update();
  buttonState=digitalRead(button);

   //get smoothed value from data set + current calibration factor
  if (millis() > t + 250) {
    float i = LoadCell.getData();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    // append a new value to /logs
    String name = Firebase.pushInt("weight", i);
    // handle error
    if (Firebase.failed()) {
      Serial.print("pushing /weight :");
      Serial.println(Firebase.error());  
      return;
    }
//    lcd.setCursor(4, 1);
//    lcd.print(i);
//    lcd.setCursor(9, 1);
//    lcd.print("kg");

//    if (buttonState == 1);
//    {
//      Serial.print("Weight is: ");
//      Serial.println(i);
//      digitalWrite(ledpin, HIGH); 
//      delay(100);
//      digitalWrite(ledpin, LOW);       
//    }
    t = millis();
  }

}
