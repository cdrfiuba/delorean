#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <stdbool.h>
#include "board.h"

typedef uint8_t sensor_t;
enum sensor_t_values{
  AMBOS_BLANCO = 0x00,  // Ambos sensores estan sobre BLANCO
  DER_BLANCO = 0x01, // El sensor derecho esta sobre blanco y el izq sobre negro
  IZQ_BLANCO = 0x02, // El sensor derecho esta sobre negro y el izq sobre blanco
  AMBOS_NEGRO = 0x03  // ambos sensores estan sobre negro
};

extern volatile bool sensor_est_nuevo;
extern volatile sensor_t sensores;

void configurarSensores();
#endif
