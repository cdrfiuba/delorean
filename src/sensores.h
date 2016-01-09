#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <stdbool.h>
#include "board.h"

typedef uint8_t sensor_t;

#define LINEA_BLANCA

#ifdef LINEA_BLANCA
  enum sensor_t_values{
    AMBOS_LINEA = 0x00,  // Ambos sensores estan sobre BLANCO
    DER_LINEA = 0x01, // El sensor derecho esta sobre blanco y el izq sobre negro
    IZQ_LINEA = 0x02, // El sensor derecho esta sobre negro y el izq sobre blanco
    AMBOS_OUT = 0x03  // ambos sensores estan sobre negro
  };
#else
  enum sensor_t_values{
    AMBOS_LINEA = 0x03,  // Ambos sensores estan sobre negro
    DER_LINEA = 0x02, // El sensor derecho esta sobre negro y el izq sobre blanco
    IZQ_LINEA = 0x01, // El sensor derecho esta sobre blancoy el izq sobre negro
    AMBOS_OUT = 0x00  // ambos sensores estan sobre blanco
  };
#endif

extern volatile bool sensor_est_nuevo;
extern volatile sensor_t sensores;

void configurarSensores();

#endif
