#ifndef _ADCAAB_
#define _ADCAAB_

//#include "delorean.h"
#include "board.h"

// Si se quiere utilizar los conversores en el modo de Interrupcion
// dejar el siguiente define. En caso de que se quiera trabajar con la
// funcion capturarADc o capturarADcPRO comentar el siguiente define
#define _ADC_MODO_INT_


void configurarADCs(void);
void capturarADc(void);
void calibrarNiveles(void);
void capturarADcPRO(void);

unsigned char analogSensorIzq;
unsigned char analogSensorCen;
unsigned char analogSensorDer;

// Variables del máximo que representa el blanco, el mínimo que representa el negro y cual de los dos es la linea.
// colorLinea tiene 1 si la linea es blanca y 0 si la linea es negra
uint8_t minNivelSensor, maxNivelSensor, colorLinea;

typedef enum{
    ES_000 = 0,
    ES_001 = 1,
    ES_010 = 2,
    ES_011 = 3,
    ES_100 = 4,
    ES_110 = 6 
    } estado_sensor_t;

estado_sensor_t estadoSensores;

estado_sensor_t analizarSensores(void);
#endif
