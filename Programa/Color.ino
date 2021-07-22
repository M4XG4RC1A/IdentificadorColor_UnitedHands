#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
 
SoftwareSerial DFPlayerSerial(6, 7); // RX, TX //10,11

//
// Cableado de TCS3200 a Arduino
//
#define S0 8
#define S1 9
#define S2 12
#define S3 11
#define salidaSensor 10

// Para guardar las frecuencias de los fotodiodos
float frecuenciaRojo = 0;
float frecuenciaVerde = 0;
float frecuenciaAzul = 0;
float colorRojo;
float colorVerde;
float colorAzul;

void setup() {
  // Definiendo las Salidas
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Definiendo salidaSensor como entrada
  pinMode(salidaSensor, INPUT);
  
  // Definiendo la escala de frecuencia a 20%
  digitalWrite(S1,HIGH);
  digitalWrite(S0,LOW);
  pinMode(2,INPUT);
  
   // Iniciar la comunicacion serie 
  Serial.begin(9600);
  Serial.begin(9600);
   DFPlayerSerial.begin(9600);
   mp3_set_serial(DFPlayerSerial);
   mp3_set_volume(30);
}

void loop() {
  if(digitalRead(2)){
  // Definiendo la lectura de los fotodiodos con filtro rojo
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Leyendo la frecuencia de salida del sensor
  frecuenciaRojo = pulseIn(salidaSensor, LOW);

  // Mapeando el valor de la frecuencia del ROJO (RED = R) de 0 a 255
  // Usted debe colocar los valores que registro. Este es un ejemplo: 
  // colorRojo = map(frecuenciaRojo, 70, 120, 255,0);
  colorRojo = map(frecuenciaRojo, 320, 2750, 255,0);
  
  // Mostrando por serie el valor para el rojo (R = Red)
  Serial.print("R = ");
  Serial.print(colorRojo);
  delay(100);
  
  // Definiendo la lectura de los fotodiodos con filtro verde
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frecuenciaVerde = pulseIn(salidaSensor, LOW);
  colorVerde = map(frecuenciaVerde, 773, 3400, 255,0);
  Serial.print("G = ");
  Serial.print(colorVerde);
  delay(100);
 
  // Definiendo la lectura de los fotodiodos con filtro azul
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frecuenciaAzul = pulseIn(salidaSensor, LOW);
  colorAzul = map(frecuenciaAzul, 1080, 3500, 255, 0);
  Serial.print("B = ");
  Serial.print(colorAzul);
  delay(100);
/*
 * 1-Rojo-255
 * 2-Verde-255
 * 3-Azul-255
 */
  if(colorRojo > colorVerde && colorRojo < colorAzul){
      Serial.println(" - Detectado ROJO");
      mp3_play(1);
   delay(6000);
  }else if (colorVerde > colorRojo && colorVerde < colorAzul){
    Serial.println(" - Detectado VERDE");
    mp3_play(2);
   delay(6000);
  }else{
    Serial.println(" - Detectado AZUL");
    mp3_play(3);
   delay(6000);
  }
  }else{
    Serial.println(" - No color");
    mp3_stop();
}

}
