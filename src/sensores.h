#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <stdbool.h>
#include "board.h"

typedef enum {
  LINEA = 3,
  DESVIO_IZQ = 1,
  DESVIO_DER = 2,
  AFUERA = 0
} sensor_t;

extern volatile bool sensor_est_nuevo;
extern volatile sensor_t sensores;

void configurarSensores();
#endif
