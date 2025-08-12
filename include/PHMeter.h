#ifndef PHMETER_H
#define PHMETER_H

class PHMeter {
private:
  int pin;
  float voltageNeutral;
  float slope;

public:
  PHMeter(int _pin, float _neutral, float _slope);
  float leerPH();
  float leerVoltaje();
};

#endif
