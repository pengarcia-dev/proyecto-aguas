#include <Arduino.h>
#include <Wire.h>
#include <Q2HX711.h>
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
#include "ESP32Servo.h"

#define PIN_BOMBA1    GPIO_NUM_5
#define PIN_BOMBA2    GPIO_NUM_4
#define PIN_BOMBA3    GPIO_NUM_3
#define PIN_BOMBA4    GPIO_NUM_2
#define PIN_VALVULA   GPIO_NUM_1
#define PIN_LED1      GPIO_NUM_7
#define PIN_LED2      GPIO_NUM_6
#define PIN_LED3      GPIO_NUM_38
#define PIN_SERVO     GPIO_NUM_40

const byte hx711_data_pin = 26;
const byte hx711_clock_pin = 21;
String command = "";

float p0 = 0.0;
float p1 = 0.0;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);
AS7265X sensor;
Servo myServo;





void Wave_Lenght_Sensor(void) {
  sensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured

  Serial.print(sensor.getA()); //410nm
  Serial.print(",");
  Serial.print(sensor.getB()); //435nm
  Serial.print(",");
  Serial.print(sensor.getC()); //460nm
  Serial.print(",");
  Serial.print(sensor.getD()); //485nm
  Serial.print(",");
  Serial.print(sensor.getE()); //510nm
  Serial.print(",");
  Serial.print(sensor.getF()); //535nm
  Serial.print(",");

  Serial.print(sensor.getG()); //560nm
  Serial.print(",");
  Serial.print(sensor.getH()); //585nm
  Serial.print(",");
  Serial.print(sensor.getR()); //610nm
  Serial.print(",");
  Serial.print(sensor.getI()); //645nm
  Serial.print(",");
  Serial.print(sensor.getS()); //680nm
  Serial.print(",");
  Serial.print(sensor.getJ()); //705nm
  Serial.print(",");

  Serial.print(sensor.getT()); //730nm
  Serial.print(",");
  Serial.print(sensor.getU()); //760nm
  Serial.print(",");
  Serial.print(sensor.getV()); //810nm
  Serial.print(",");
  Serial.print(sensor.getW()); //860nm
  Serial.print(",");
  Serial.print(sensor.getK()); //900nm
  Serial.print(",");
  Serial.print(sensor.getL()); //940nm
  Serial.print(",");

  Serial.println();
}

void Leer_Led_1(void) {
  digitalWrite(PIN_LED1, HIGH);
  delay(2000);
  Wave_Lenght_Sensor();
  digitalWrite(PIN_LED1, LOW);
}

void Leer_Led_2(void) {
  digitalWrite(PIN_LED2, HIGH);
  delay(2000);
  Wave_Lenght_Sensor();
  digitalWrite(PIN_LED2, LOW);
}

void Leer_Led_3(void) {
  digitalWrite(PIN_LED3, HIGH);
  delay(2000);
  Wave_Lenght_Sensor();
  digitalWrite(PIN_LED3, LOW);
}

void Leer_Presion(void) {
  Serial.println(hx711.read()/100.0);
  delay(500);
}

float Presion(void) {
  float presion = hx711.read() / 1000;
  Serial.println(presion);
  return presion;

  delay(100);
}


void setup(void) {
  Serial.begin(115200);
  Wire.begin(42,41);
  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
  }
  sensor.disableIndicator();

  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");

  pinMode(PIN_BOMBA1, OUTPUT);
  pinMode(PIN_BOMBA2, OUTPUT);
  pinMode(PIN_BOMBA3, OUTPUT);
  pinMode(PIN_BOMBA4, OUTPUT);

  pinMode(PIN_VALVULA, OUTPUT);

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  myServo.attach(PIN_SERVO);

  Serial.println("Write the command to any action");


}

void Llenar_Agua(void) {
  float p0 = Presion();
  Serial.println("La presion inicial es: " + String(p0));
  delay(1000);
  while((Presion() - p0) <= 284) {
    digitalWrite(PIN_BOMBA1, HIGH);
    delay(10);
  }
  digitalWrite(PIN_BOMBA1, LOW);
  delay(100);
}

void Vaciar_Agua(void) {
  float p0 = Presion();
  Serial.println("La presion inicial es: " + String(p0));
  while((p0 - Presion()) < 276 ) {
    digitalWrite(PIN_BOMBA2, HIGH);
    delay(10);
  }
  delay(5000);
  digitalWrite(PIN_BOMBA2, LOW);
  delay(100);
}

void Llenar_Alcohol(void) {
  float p0 = Presion();
  Serial.println("La presion inicial es: " + String(p0));
  delay(1000);
  while((Presion() - p0) <= 102 ) {
    digitalWrite(PIN_BOMBA3, HIGH);
    delay(10);
  }
  digitalWrite(PIN_BOMBA3, LOW);
  delay(100);
}

void Vaciar_Alcohol(void) {
  digitalWrite(PIN_BOMBA2, HIGH);
  delay(7000);
  digitalWrite(PIN_BOMBA2, LOW);
}

void Aire(void) {
  Serial.println("Echando aire");
  digitalWrite(PIN_BOMBA4, HIGH);
  delay(3000);
  digitalWrite(PIN_BOMBA4, LOW);
}



void loop(void) {
  if(Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    if(command.equalsIgnoreCase("Leer")) Wave_Lenght_Sensor();
    else if(command.equalsIgnoreCase("LedA")) {
      digitalWrite(PIN_LED1, HIGH);
      delay(1000);
      digitalWrite(PIN_LED1, LOW);
    }
    else if(command.equalsIgnoreCase("LedR")) {
      digitalWrite(PIN_LED2, HIGH);
      delay(1000);
      digitalWrite(PIN_LED2, LOW);
    }
    else if(command.equalsIgnoreCase("LedIR")) {
      digitalWrite(PIN_LED3, HIGH);
      delay(1000);
      digitalWrite(PIN_LED3, LOW);
    }
    else if(command.equalsIgnoreCase("LeerT")) {
      Leer_Led_1();
      Leer_Led_2();
      Leer_Led_3();      
    }
    else if(command.equalsIgnoreCase("Presion")) {
      Leer_Presion();
    }
    else if(command.equalsIgnoreCase("0")) {
      myServo.write(170);
    }
    else if(command.equalsIgnoreCase("1")) {
      myServo.write(45);
    }
    else if(command.equalsIgnoreCase("Bomba1")) {
      digitalWrite(PIN_BOMBA1, HIGH);
      Serial.println("Llenando");
      delay(2000);
      digitalWrite(PIN_BOMBA1, LOW);
    }
    else if(command.equalsIgnoreCase("Vaciar")) {
      digitalWrite(PIN_BOMBA2, HIGH);
      Serial.println("Vaciado");
      delay(2000);
      digitalWrite(PIN_BOMBA2, LOW);
    }
    else if(command.equalsIgnoreCase("LlenarA")){
      Llenar_Agua();
    }
    else if(command.equalsIgnoreCase("VaciarA")) {
      Vaciar_Agua();
    }
    else if(command.equalsIgnoreCase("LlenarAl"))
    Llenar_Alcohol();
    else if(command.equalsIgnoreCase("VaciarAl"))
    Vaciar_Alcohol();
    else if(command.equalsIgnoreCase("Aire")) 
    Aire();
  }

}