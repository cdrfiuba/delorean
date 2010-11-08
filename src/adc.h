#ifndef _ADCAAB_
#define _ADCAAB_

//#include "delorean.h"
#include "board.h"


#define SENSOR_NIVEL_NEGRO		255
#define SENSOR_NIVEL_BLANCO		200

//#define NIVEL_MAYOR 		max(SENSOR_NIVEL_NEGRO,SENSOR_NIVEL_BLANCO)
//#define NIVEL_MENOR 		min(SENSOR_NIVEL_NEGRO,SENSOR_NIVEL_BLANCO)

#define NIVEL_BLANCO_INDET		SENSOR_NIVEL_BLANCO + (SENSOR_NIVEL_NEGRO - SENSOR_NIVEL_BLANCO)/3 
#define NIVEL_NEGRO_INDET		  SENSOR_NIVEL_NEGRO  - (SENSOR_NIVEL_NEGRO - SENSOR_NIVEL_BLANCO)/3
#define NIVEL_MEDIO_SENSORES 	SENSOR_NIVEL_BLANCO + (SENSOR_NIVEL_NEGRO - SENSOR_NIVEL_BLANCO)/2

void configurarADCs(void);
void capturarADc(void);
void calibrarNiveles();


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
