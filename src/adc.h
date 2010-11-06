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

unsigned char analogSensorIzq;
unsigned char analogSensorCen;
unsigned char analogSensorDer;

typedef enum{
    ES_010,
    ES_011,
    ES_001,
    ES_110,
    ES_100,
    ES_000
    } estado_sensor_t;

estado_sensor_t estadoSensores;

estado_sensor_t analizarSensores(void);
#endif
