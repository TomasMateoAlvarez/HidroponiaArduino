#include <Arduino.h>
#include "PHMeter.h"
#include "TDSMeter.h"
#include "Riego.h"

// Pines de sensores y relés
#define PH_PIN A0
#define TDS_PIN A1

#define RELAY_PH 4      // Bomba para ajustar pH
#define RELAY_TDS 2     // Bomba nutrientes para TDS
#define RELAY_WATER 5   // Bomba de agua (riego)

// Umbrales para control automático
const float PH_MIN = 6.5;
const float PH_MAX = 7.5;

const float TDS_MIN = 700.0;
const float TDS_MAX = 800.0;

PHMeter phSensor(PH_PIN, 1.29, -5.7);
TDSMeter tdsSensor(TDS_PIN);
Riego riego(RELAY_WATER, 3600000UL, 480000UL);  // intervalo: 1h, duración: 8 min

void setup() {
  Serial.begin(9600);

  // Configurar pines de salida para relés
  pinMode(RELAY_PH, OUTPUT);
  pinMode(RELAY_TDS, OUTPUT);
  pinMode(RELAY_WATER, OUTPUT);

  // Apagar relés al inicio
  digitalWrite(RELAY_PH, LOW);
  digitalWrite(RELAY_TDS, LOW);
  digitalWrite(RELAY_WATER, LOW);
}

void loop() {
  // Leer sensores
  float ph = phSensor.leerPH();
  float tds = tdsSensor.leerPPM();

  // Control automático pH
  if (ph < PH_MIN) {
    digitalWrite(RELAY_PH, HIGH); 
    Serial.println("pH bajo: activando bomba para subir pH");
  } else if (ph > PH_MAX) {
    digitalWrite(RELAY_PH, HIGH);  
    Serial.println("pH alto: activando bomba para bajar pH");
  } else {
    digitalWrite(RELAY_PH, LOW);   // Apagar bombas de pH si está dentro del rango
    Serial.println("pH dentro del rango ideal");
  }

  // Control automático TDS
  if (tds < TDS_MIN) {
    digitalWrite(RELAY_TDS, HIGH); // Activar bomba nutrientes
    Serial.println("TDS bajo: activando bomba nutrientes");
  } else if (tds > TDS_MAX) {
    digitalWrite(RELAY_TDS, LOW); 
    Serial.println("TDS alto: bomba nutrientes apagada");
  } else {
    digitalWrite(RELAY_TDS, LOW);  // Apagar bomba si TDS está en rango
    Serial.println("TDS dentro del rango ideal");
  }

  // Control de riego por tiempo (cada 1 hora activa bomba 8 min)
  riego.actualizar();

  // Mostrar valores por Serial
  Serial.print("Lecturas -> pH: ");
  Serial.print(ph, 2);
  Serial.print(" | TDS: ");
  Serial.print(tds, 0);
  Serial.println(" ppm");

  Serial.println("-------------------------------");

  delay(2000);  // Esperar 2 segundos antes de la próxima lectura
}
