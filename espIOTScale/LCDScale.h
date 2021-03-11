void setup()
{
    Serial.begin(115200);

    pinMode(rbutton, INPUT_PULLUP);

    scale.begin(DT, SCK);
    scale.set_scale();
    scale.tare(); // reset the scale to 0

    long zero_factor = scale.read_average(); // get a baseline reading

    lcd.begin();
    lcd.setCursor(6, 0);
    lcd.print("IOT");
    lcd.setCursor(1, 1);
    lcd.print("Weighing Scale");

    delay(3000);
    lcd.clear();

    scale.set_scale(calibration_factor); // adjust to this calibration factor

    lcd.setCursor(0, 0);
    lcd.print("Measured weight:");
}

void loop()
{
    weight = scale.get_units(5);

    lcd.setCursor(0, 1);
    lcd.print(weight);
    lcd.print(" kg      ");

    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" kg");
    Serial.println();

    if (digitalRead(rbutton) == LOW)
    {
        scale.set_scale();
        scale.tare(); // reset the scale to 0
    }
}
