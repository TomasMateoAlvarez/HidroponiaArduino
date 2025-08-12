#ifndef RIEGO_H
#define RIEGO_H

class Riego {
private:
  int pinRelay;
  unsigned long intervalo;
  unsigned long duracion;
  unsigned long tUltimo;
  bool encendido;

public:
  Riego(int pin, unsigned long intervaloMs, unsigned long duracionMs);
  void actualizar();
};

#endif
