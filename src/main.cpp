#include <Arduino.h>
#include <Wire.h>
#include <Q2HX711.h>
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X


const byte hx711_data_pin = 26;
const byte hx711_clock_pin = 21;

#define PIN_BOMBA1    GPIO_NUM_5
#define PIN_BOMBA2    GPIO_NUM_4
#define PIN_BOMBA3    GPIO_NUM_3
#define PIN_BOMBA4    GPIO_NUM_2
#define PIN_VALVULA   GPIO_NUM_1
#define PIN_LED1      GPIO_NUM_7

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);
AS7265X sensor;


void setup(void) {
  Serial.begin(115200);
  Wire.begin();
  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
  
  }

  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");

  pinMode(PIN_BOMBA1, OUTPUT);
  pinMode(PIN_BOMBA2, OUTPUT);
  pinMode(PIN_BOMBA3, OUTPUT);
  pinMode(PIN_BOMBA4, OUTPUT);

  pinMode(PIN_VALVULA, OUTPUT);

  pinMode(PIN_LED1, OUTPUT);


}

void loop(void) {

  

  // sensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured

  // Serial.print(sensor.getA()); //410nm
  // Serial.print(",");
  // Serial.print(sensor.getB()); //435nm
  // Serial.print(",");
  // Serial.print(sensor.getC()); //460nm
  // Serial.print(",");
  // Serial.print(sensor.getD()); //485nm
  // Serial.print(",");
  // Serial.print(sensor.getE()); //510nm
  // Serial.print(",");
  // Serial.print(sensor.getF()); //535nm
  // Serial.print(",");

  // Serial.print(sensor.getG()); //560nm
  // Serial.print(",");
  // Serial.print(sensor.getH()); //585nm
  // Serial.print(",");
  // Serial.print(sensor.getR()); //610nm
  // Serial.print(",");
  // Serial.print(sensor.getI()); //645nm
  // Serial.print(",");
  // Serial.print(sensor.getS()); //680nm
  // Serial.print(",");
  // Serial.print(sensor.getJ()); //705nm
  // Serial.print(",");

  // Serial.print(sensor.getT()); //730nm
  // Serial.print(",");
  // Serial.print(sensor.getU()); //760nm
  // Serial.print(",");
  // Serial.print(sensor.getV()); //810nm
  // Serial.print(",");
  // Serial.print(sensor.getW()); //860nm
  // Serial.print(",");
  // Serial.print(sensor.getK()); //900nm
  // Serial.print(",");
  // Serial.print(sensor.getL()); //940nm
  // Serial.print(",");

  // Serial.println();
}