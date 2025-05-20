#include <Arduino.h>
//   Label GPIO     Input           Output               Notes
#define D0   16  //No interrupt     No PWM or I2C        High at boot (used to wakeup from deep sllep)
#define D1    5  //OK               OK                   Often used as SCL(I2C)     
#define D2    4  //OK               OK                   Often used as SDA(I2C)
#define D3    0  //PulledUP         OK                   Conected to flash button fails if pulled LOW
#define D4    2  //PulledUP         OK                   HIGH AT BOOT,boot fails if pulled low
#define D5   14  //OK               OK                   SPI (SCLK)
#define D6   12  //OK               OK                   SPI (MISO)
#define D7   13  //OK               OK                   SPI (MOSI)
#define D8   15  //PulledDOWN       OK    

//Para servo 
// Incluímos la librería para poder controlar el servo
#include <Servo.h>
 
// Declaramos la variable para controlar el servo
Servo myservo;
     
//Cable marron Tierra
//Cable rojo 5v
//Cable naranja o blanco digital
 
//Fin servo

//Expansor
#include <Wire.h>
#include "Adafruit_MCP23X17.h"

// Sample for usage of two MCP23017 I/O expander with an ESP32
// public domain!

Adafruit_MCP23X17 mcp;
//Fin expansor


int LedPin=0+8;//Led Excitacion Azul
int Bomba1Pin=1+8;//agua
int Bomba2Pin=2+8;//alcool
int Bomba3Pin=3+8;//aire Bomna aire para mezclar(Abajo)
int Bomba4Pin=4+8;////Bomba aire de vaciar
int Valvula1Pin=5+8;//SalidaCamera1 por abajo
int Valvula2Pin=6+8;//Salida Camera1 por arriba
int LedPin2=7+8;//Led Excitacion Rojo

int SensorAgua=D6;// solo input do proprio mini D1

#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;

#include <Wire.h>


void LeerSensor(int LedPinx){
  mcp.digitalWrite(LedPinx,HIGH);
  delay(100);
  sensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured
  //sensor.takeMeasurementsWithBulb();
  mcp.digitalWrite(LedPinx,LOW);
  float threeSensorTemp = sensor.getTemperatureAverage(); //Returns the average temperature of all three ICs
  
  Serial.print("Temperature: ");
  Serial.print(threeSensorTemp, 2);
  Serial.print(",");
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
  
  Serial.println();
  
  }
void Acercar( ){ myservo.write(180);delay(5000);}
void Alejar( ){  myservo.write(1);  delay(5000);}

void setup()
{ 
//Expansor
  while(!mcp.begin_I2C())
  {
    Serial.println("Error en la comunicacion con el MCP23017");
  }
   // use default address 0
  
//Fin expansor
  
  mcp.pinMode(LedPin,OUTPUT);mcp.digitalWrite(LedPin,LOW);
  mcp.pinMode(LedPin2,OUTPUT);mcp.digitalWrite(LedPin2,LOW);
  mcp.pinMode(Bomba1Pin,OUTPUT);mcp.digitalWrite(Bomba1Pin,LOW);
  mcp.pinMode(Bomba2Pin,OUTPUT);mcp.digitalWrite(Bomba2Pin,LOW);
  mcp.pinMode(Bomba3Pin,OUTPUT);mcp.digitalWrite(Bomba3Pin,LOW);
  mcp.pinMode(Bomba4Pin,OUTPUT);mcp.digitalWrite(Bomba4Pin,LOW);
  mcp.pinMode(Valvula1Pin,OUTPUT);mcp.digitalWrite(Valvula1Pin,LOW);
  mcp.pinMode(Valvula2Pin,OUTPUT);mcp.digitalWrite(Valvula2Pin,LOW);
  //mcp.pinMode(Valvula3Pin,OUTPUT);mcp.digitalWrite(Valvula3Pin,LOW);

  pinMode(SensorAgua,INPUT);//No usa la placa de expansion



  Serial.begin(115200);
  Serial.println("AS7265x Spectral Triad Example");
 
  if (sensor.begin() == false)
  //while (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    ESP.restart();
    while (1);
    //delay(500);  
  }

  //Once the sensor is started we can increase the I2C speed
  Wire.setClock(400000);
  delay(1000);
  sensor.disableIndicator();
  delay(500);

  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");

  // Iniciamos el servo para que empiece a trabajar con el D6
  myservo.attach(D7);
  Acercar( );
 // mcp.digitalWrite(Bomba1Pin,HIGH);
 

  
}


void Mas(){
  Serial.println("Abrir valvula arriba Camera 1");
  mcp.digitalWrite(Valvula2Pin,HIGH);
  delay(500);
   //encender Bomba1 de agua
  Serial.println("Bomba 1 agua funcionando");
  Serial.println("Llenando Camera1");
  
  digitalWrite(Bomba2Pin,HIGH);
  Serial.println("Dejar 1 segundos mas");delay(1000);
  digitalWrite(Bomba1Pin,LOW);//apagar la bomba

  Serial.println("cerrar valvula arriba Camera 1");
  mcp.digitalWrite(Valvula2Pin,LOW);
   
  
  
  }

void Mas1(){
  Serial.println("Abrir valvula arriba Camera 1");
  mcp.digitalWrite(Valvula2Pin,HIGH);
  delay(500);
   //encender Bomba1 de agua
  Serial.println("Bomba 1 alcool funcionando");
  Serial.println("Llenando Camera1");
  
  digitalWrite(Bomba1Pin,HIGH);
  Serial.println("Dejar 1 segundos mas");delay(1000);
  digitalWrite(Bomba1Pin,LOW);//apagar la bomba

  Serial.println("cerrar valvula arriba Camera 1");
  mcp.digitalWrite(Valvula2Pin,LOW);
   
  
  
  }
  
  
  

void Paso1(){//Llenar camera 1 con agua
  Serial.println("Llenar la camera con agua del lago");
  //abrir valvula salida camera 1 por arriba
  
  //Encender bomba de agua hasta que salte el sensor.
  
  Serial.println("Abrir valvula arriba Camera 1");
  mcp.digitalWrite(Valvula2Pin,HIGH);
  delay(500);
  //encender Bomba1 de agua
  Serial.println("Bomba 1 agua funcionando");
  Serial.println("Llenando Camera1");
  
  mcp.digitalWrite(Bomba1Pin,HIGH);
  Serial.print("Estado del sensor agua:");
  Serial.println("Llenando Camera1");
  Serial.print(digitalRead(SensorAgua));
  while (digitalRead(SensorAgua)==0){
    Serial.print(".");
    //esperar mientras llena
  }//While

   //Serial.println();
   //Serial.println("Camera1 Llena");
   
   mcp.digitalWrite(Bomba1Pin,LOW);//apagar la bomba
   delay(500);
   mcp.digitalWrite(Valvula2Pin,LOW);
   
    
  
}

void Paso2(){//Mezclar
  Serial.println("Mezclar el agua con las particulas magneticas para atrapar la clorofila");
  //abrir valvula salida camera 1 por arriba
  //Encender bomba 3 de aire para mezclar
  Serial.println("Abrir valvula arriba Camera 1");
   
  mcp.digitalWrite(Valvula2Pin,HIGH);
  delay(500);
  
  //encender Bomba3 de aire
  Serial.println("Bomba 3 aire funcionando para Mezclar");
  Serial.println("Mezclando");
  
  mcp.digitalWrite(Bomba3Pin,HIGH);
  delay(10000);
  
  Serial.println("Mezclador con aire apagado");
   mcp.digitalWrite(Bomba3Pin,LOW);//apagar la bomba
  
  delay(200);
  mcp.digitalWrite(Valvula2Pin,LOW);
    
  
}

void Paso3(){//vaciarCamera
  Serial.println("Vaciar la camera");
  //abrir valvula salida camera 1 por bajo
  
 

  
  Serial.println("Abrir valvula abajo Camera 1");
  mcp.digitalWrite(Valvula1Pin,HIGH);
  mcp.digitalWrite(Valvula2Pin,HIGH);//Tambien abrir la de arriga
  delay(1000);

  
  //Encender bomba de aire de arriba//é pasado para succion abajo
  mcp.digitalWrite(Bomba4Pin,HIGH);
  //delay(5000);
  //digitalWrite(Bomba4Pin,LOW);
  //Esperar el 
  float tempo=micros();
  //while (Serial.available() == 0)
  //{}
  delay(10000);
  String aux=Serial.readString();
  //Serial.print("TiempoVaciado(s): ");
  //Serial.println((micros()-tempo)/1000000);

  mcp.digitalWrite(Bomba4Pin,LOW);
  delay(1000);
  mcp.digitalWrite(Valvula1Pin,LOW);
  mcp.digitalWrite(Valvula2Pin,LOW);
  
    
  
}
  
void AbrirAbajo(){
  Serial.println("Abriendo valvula abajo por 10 segundos");
  mcp.digitalWrite(Valvula1Pin,HIGH);
  delay(10000);
  mcp.digitalWrite(Valvula1Pin,LOW);
  Serial.println("Valvula Cerrada");
  delay(500);
  
  }
  void AbrirArriba(){
    Serial.println("Abriendo valvula Arriba por 10 segundos");
  mcp.digitalWrite(Valvula2Pin,HIGH);
  delay(10000);
  mcp.digitalWrite(Valvula2Pin,LOW);
  Serial.println("Valvula Cerrada");
  delay(500);
  
  }
  void Paso4(){//Llenar camera 1 con alcool
    
   Serial.println("Llenar la camera con alcool para disolver la clorofila");
   //abrir valvula salida camera 1 por arriba
  
  //Encender bomba de agua hasta que salte el sensor.
  
  Serial.println("Abrir valvula arriba Camera 1");
  
  mcp.digitalWrite(Valvula2Pin,HIGH);
  delay(500);
  //encender Bomba1 de agua
  Serial.println("Bomba 2 agua funcionando");
  Serial.println("Llenando Camera");
  
  mcp.digitalWrite(Bomba2Pin,HIGH);
  //Serial.print("Estado del sensor agua:");
  //Serial.println("Llenando Camera1");
  //Serial.print(digitalRead(SensorAgua));
 // while (digitalRead(SensorAgua)==0){ }//While
delay(7000);
   //Serial.println();
   //Serial.println("Camera1 Llena");
   
   mcp.digitalWrite(Bomba2Pin,LOW);//apagar la bomba
   delay(500);
   mcp.digitalWrite(Valvula2Pin,LOW);
    
  
}
void loop()
{
  //while (Serial.available() == 0)
  //{}

  if (Serial.available() > 0) {
    String aux=Serial.readString();
    Serial.println("Orden recibida: " + aux);

  if (aux == "LeerA")
  {  Serial.println("410*435*460*485*510*535*560*585*610*645*680*705*730*760*810*860*900*940 ");
    LeerSensor(LedPin);//Azul
  }
  if (aux == "LeerR")
  {  Serial.println("410*435*460*485*510*535*560*585*610*645*680*705*730*760*810*860*900*940 ");
    LeerSensor(LedPin2);//Rojo
  }

  if (aux == "Leer5")
  {
    Serial.println("410*435*460*485*510*535*560*585*610*645*680*705*730*760*810*860*900*940 ");
    //LeerSensor();
    Paso2();
    delay(1000);
    //LeerSensor();
    Paso2();
    delay(1000);
    //LeerSensor();
    Paso2();
    delay(1000);
    //LeerSensor();
    Paso2();
    delay(1000);
    //LeerSensor();
    
  }

  if (aux == "Arriba")
  {
    AbrirArriba();
  }

  if (aux == "Abajo")
  {
    AbrirAbajo();
  }
  if (aux == "Limpiar")
  {
    Paso3();
    Paso1();
    Paso2();
    Paso3();
    Paso1();
    Paso2();
    Paso3();
    Paso1();
    Paso2();
    Paso3();
    
  }

  

  if (aux ==  "Paso1")//Llenar Agua
  {
    
    Serial.println("Llenando con agua");
    Paso1();
  }

  if (aux ==  "Paso2") //Mezclar
  {
    Paso2();
  }
 if (aux ==  "Paso3") //Vaciar
  {
    Paso3();
  }

  if (aux ==  "Mas") //
  {
    Mas();
  }

  if (aux ==  "Mas1") //
  {
    Mas1();
  }

   if (aux ==  "Paso4") //Llenar alcool
  {
    Paso4();
  }
  if (aux ==  "Todo") //
  { Serial.println("Acercar Iman para capturar las particulas magneticas");
    Acercar( );
    Serial.println("LLenar de agua del lago");
    Paso1();//LLenar de agua
    Serial.println("Alejar Iman para liberar las particulas magneticas");
    Alejar( );
    Serial.println("Mezclar las particulas magneticas con el agua para capturar clorofila");
    Paso2();//Mezclar
    Serial.println("Acercar Iman para Capturar las particulas magneticas");
    Acercar( );delay(5000);
    Serial.println("Mover el agua para capturar todas las particulas magneticas");
    Paso2();//Mezclar
    delay(5000);
    Serial.println("Vaciar la camara ");
    Paso3();//Vaciar (Hay que retener las particulas magneticas)
    Serial.println("Volver a llenar con agua del lago ");
    Paso1();//LLenar de agua
    Serial.println("Alejar Inan para liberar las particulas magneticas");
    Alejar( );
    Serial.println("Mezclar las particulas magneticas con el agua para capturar clorofila");
    Paso2();//Mezclar
    Serial.println("Acercar Iman para Capturar las particulas magneticas");
    Acercar( );delay(5000);
    Serial.println("Mover el agua para capturar todas las particulas magneticas");
    Paso2();//Mezclar
    Serial.println("Vaciar la camara ");
    Paso3();//Vaciar
    Serial.println("LLenar la camera con alcool para disolver la clorofila de las particulas magneticas en el allcool");
    Paso4();//Llenar de alcool
    Serial.println("Alejar Inan para liberar las particulas magneticas");
    Alejar( );
    Serial.println("Mezclar las particulas magneticas con el alcool  para disolver la clorofila en el allcool");
    Paso2();//Mezclar
    Serial.println("Acercar Iman para Capturar las particulas magneticas");
    Acercar( );delay(5000);
    Serial.println("Mover el alcool para capturar todas las particulas magneticas");
    Paso2();//Mezclar
    Serial.println("Leer el sensor");
    //LeerSensor();//Leer
    delay(500);
    Serial.println("Leer el sensor");
    //LeerSensor();//Leer
    delay(500);
    Serial.println("Leer el sensor");
    ////LeerSensor();//Leer
    delay(500);
    Serial.println("Vaciar la camara mirar si hay que limpiarla con alcool o agua");
    Paso3();//Vaciar
    //EnviarDatos();
    
    
  }

   if (aux ==  "0") 
  {
    Acercar( );
    Serial.println("Acercando Iman");
  }
   if (aux ==  "1") 
  {
    Alejar( );
    Serial.println("Alejando Iman");
  }
  
    }
  
  

 
}//loop