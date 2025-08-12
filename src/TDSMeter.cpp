#include "TDSMeter.h"
#include <Arduino.h>

TDSMeter::TDSMeter(int _pin) {
  pin = _pin;
}

float TDSMeter::leerVoltaje() {
  return analogRead(pin) * (5.0 / 1024.0);
}

float TDSMeter::leerPPM() {
  return leerVoltaje() * 500.0;
}
