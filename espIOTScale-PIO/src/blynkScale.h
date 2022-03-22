#include "blynkConfig.h"

void setup()
{
    Serial.begin(115200);

    /**********
    * Print start information
    ********/
    Serial.println(programName); // print information
    Serial.println(date);
    Serial.print("by ");
    Serial.println(author);
    Serial.println(email);
    Serial.println();

    /**********
    * In/Outputs
    **********/
    Serial.println("Starting In/Outputs...");

    pinMode(rbutton, INPUT_PULLUP);

    /**********
    * Scale
    **********/
    Serial.println("Starting scale...");

    scale.begin(DT, SCK);
    scale.set_scale();
    scale.tare(); //Reset the scale to 0

    long zero_factor = scale.read_average(); //Get a baseline reading

    /**********
    * Blynk
    **********/
    Serial.println("Starting Blynk...");

    Blynk.begin(auth, ssid, pass);

    /**********
     * LCD
     **********/
    Serial.println("Starting LCD...");

    lcd.begin();
    lcd.setCursor(LCDColumns / 2 - 1 - 3 / 2, 0);
    lcd.print("IOT");
    lcd.setCursor(LCDColumns / 2 - 1 - 14 / 2, 1);
    lcd.print("Weighing Scale");

    Serial.println("Waiting 3 seconds...");
    delay(3000);
    lcd.clear();

    /**********
     * WiFi
    **********/
    lcd.print("Connecting Wifi...");

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

    Serial.println("Waiting 2 seconds...");
    delay(2000);

    Serial.println("Starting main program...");
    Serial.println();

    lcd.setCursor(0, 0);
    lcd.print("Measured Weight");
}

void loop()
{
    currentMillis = millis();
    if (currentMillis - lastReadMillis > iterationMillis)
    {
        Blynk.run();

        scale.set_scale(calibration_factor); //Adjust to this calibration factor

        weight = scale.get_units(5);

        if (weight != oldWeight)
        {
            lcd.setCursor(0, 1);
            lcd.print(weight);
            lcd.print(" kg     ");

            oldWeight = weight;
            Blynk.virtualWrite(V3, weight);
        }

        Serial.print("Weight: ");
        Serial.print(weight);
        Serial.println(" kg");
        Serial.println();
    }

    if (digitalRead(rbutton) == LOW)
    {
        scale.set_scale();
        scale.tare(); //Reset the scale to 0
    }
}
