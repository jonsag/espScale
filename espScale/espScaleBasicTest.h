#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D2;
const int LOADCELL_SCK_PIN = D1;

HX711 scale;

int i = 0;

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  i += 1;
  
  if (scale.is_ready()) {
    long reading = scale.read();

    Serial.print(i);
    Serial.print(": ");
    
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000);
  
}
