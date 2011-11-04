#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <stdbool.h>
#include "board.h"

typedef enum {
  LINEA = 0b00,
  DESVIO_IZQ = 0b01,
  DESVIO_DER = 0b10,
  AFUERA = 0b11
} sensor_t;

extern volatile bool sensor_est_nuevo;
extern volatile sensor_t sensores;

void configurarSensores();
#endif
