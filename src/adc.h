#ifndef _ADCAAB_
#define _ADCAAB_

//#include "delorean.h"
#include "board.h"

#define NIVEL_MEDIO_SENSORES 	230

void configurarADCs(void);
void capturarADc(void);

unsigned char analogSensorIzq;
unsigned char analogSensorCen;
unsigned char analogSensorDer;

#endif
