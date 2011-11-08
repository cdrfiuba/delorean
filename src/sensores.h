#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <stdbool.h>
#include "board.h"

typedef enum {
  AMBOSBLANCO = 0x00,  // Los dos sensores estan sobre blanco
  DESVIO_IZQ = 0x01, // El sensor derecho esta sobre blanco y el izq sobre negro
  DESVIO_DER = 0x02, // El sensor derecho esta sobre negro y el izq sobre blanco
  LINEA = 0x03  // Ambos sensores estan sobre negro
} sensor_t;

extern volatile bool sensor_est_nuevo;
extern volatile sensor_t sensores;

void configurarSensores();
#endif
