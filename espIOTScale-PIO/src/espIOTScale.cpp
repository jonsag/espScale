
/**********
 * Create a file in this directory called 'secrets.h'
 * This file must have these three lines:
 * const char *ssid = "<your SSID>"; // replace with your wifi ssid and wpa2 key
 * const char *pass = "<your pass>";
 * char auth[] = "<your blynk token>"; // you should get auth token in the Blynk app 
 **********/

#include <Arduino.h>

#include "config.h"
#include "secrets.h"

// Run the actual code
#include "blynkScale.h"
