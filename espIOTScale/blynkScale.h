#include "blynkConfig.h"

void setup()
{
    Serial.begin(115200);
    pinMode(rbutton, INPUT_PULLUP);

    scale.begin(DT, SCK);
    scale.set_scale();
    scale.tare(); //Reset the scale to 0

    long zero_factor = scale.read_average(); //Get a baseline reading

    Blynk.begin(auth, ssid, pass);
    
    lcd.begin();
    lcd.setCursor(6, 0);
    lcd.print("IOT");
    lcd.setCursor(1, 1);
    lcd.print("Weighing Scale");

    delay(3000);
    lcd.clear();

    lcd.print("Connecting Wifi");

    WiFi.begin(ssid, pass);
    {
        delay(1000);
        Serial.print(".");
        lcd.clear();
    }
    Serial.println("");
    Serial.println("WiFi connected");
    lcd.clear();
    lcd.print("WiFi connected");

    delay(2000);
}

void loop()
{

    Blynk.run();
    scale.set_scale(calibration_factor); //Adjust to this calibration factor

    weight = scale.get_units(5);

    lcd.setCursor(0, 0);
    lcd.print("Measured Weight");
    lcd.setCursor(0, 1);
    lcd.print(weight);
    lcd.print(" KG  ");
    Blynk.virtualWrite(V3, weight);
    delay(2000);
    lcd.clear();

    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" KG");
    Serial.println();

    if (digitalRead(rbutton) == LOW)
    {
        scale.set_scale();
        scale.tare(); //Reset the scale to 0
    }
}
