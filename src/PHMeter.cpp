#include "PHMeter.h"
#include <Arduino.h>

PHMeter::PHMeter(int _pin, float _neutral, float _slope) {
  pin = _pin;
  voltageNeutral = _neutral;
  slope = _slope;
}

float PHMeter::leerVoltaje() {
  return analogRead(pin) * (5.0 / 1023.0);
}

float PHMeter::leerPH() {
  return slope * (leerVoltaje() - voltageNeutral) + 7.0;
}
