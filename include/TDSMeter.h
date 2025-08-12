#ifndef TDSMETER_H
#define TDSMETER_H

class TDSMeter {
private:
  int pin;

public:
  TDSMeter(int _pin);
  float leerVoltaje();
  float leerPPM();
};

#endif
