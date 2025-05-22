#include <Arduino.h>
#include <Wire.h>
#include <Q2HX711.h>

const byte hx711_data_pin = 42;
const byte hx711_clock_pin = 41;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup(void) {
  Serial.begin(115200);
  Wire.begin();

}

void loop(void) {
  Serial.println(hx711.read()/100.0);
  delay(500);

}