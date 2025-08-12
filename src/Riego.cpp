#include "Riego.h"
#include <Arduino.h>

Riego::Riego(int pin, unsigned long intervaloMs, unsigned long duracionMs) {
  pinRelay = pin;
  intervalo = intervaloMs;
  duracion = duracionMs;
  tUltimo = millis();
  encendido = false;
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);
}

void Riego::actualizar() {
  unsigned long ahora = millis();

  if (!encendido && ahora - tUltimo >= intervalo) {
    digitalWrite(pinRelay, HIGH);
    encendido = true;
    tUltimo = ahora;
  }

  if (encendido && ahora - tUltimo >= duracion) {
    digitalWrite(pinRelay, LOW);
    encendido = false;
    tUltimo = ahora;
  }
}
