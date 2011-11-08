#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <stdbool.h>
#include "board.h"

typedef enum {
  AFUERA = 0x00,
  DESVIO_IZQ = 0x01,
  DESVIO_DER = 0x02,
  LINEA = 0x03
} sensor_t;

extern volatile bool sensor_est_nuevo;
extern volatile sensor_t sensores;

void configurarSensores();
#endif
