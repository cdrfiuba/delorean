#ifndef _ADCAAB_
#define _ADCAAB_

//#include "delorean.h"
#include "board.h"
#include <avr/eeprom.h>

// Si se quiere utilizar los conversores en el modo de Interrupcion
// dejar el siguiente define. En caso de que se quiera trabajar con la
// funcion capturarADc o capturarADcPRO comentar el siguiente define
#define _ADC_MODO_INT_



volatile uint8_t analogSensorIzq;
volatile uint8_t analogSensorCen;
volatile uint8_t analogSensorDer;

// Variables del máximo que representa el blanco, el mínimo que representa el negro y cual de los dos es la linea.
// colorLinea tiene 1 si la linea es blanca y 0 si la linea es negra
uint16_t minNivelSensor, maxNivelSensor, colorLinea;

typedef enum{
    ES_33 = (3<<2) | (3<<0),
    ES_23 = (2<<2) | (3<<0),
    ES_13 = (1<<2) | (3<<0),
    ES_03 = (0<<2) | (3<<0),
    ES_02 = (0<<2) | (2<<0),
    ES_01 = (0<<2) | (1<<0),
    ES_32 = (3<<2) | (2<<0),
    ES_31 = (3<<2) | (1<<0),
    ES_30 = (3<<2) | (0<<0),
    ES_20 = (2<<2) | (0<<0),
    ES_10 = (1<<2) | (0<<0),
    ES_00 = (0<<2) | (0<<0)
    } estado_sensor_t;


void configurarADCs(void);
void capturarADc(void);
uint8_t calibrarNiveles(void);
void calcularNiveles(void);
void capturarADcPRO(void);
estado_sensor_t analizarSensores(void);


/*
#define S_NEGRO    255
#define S_BLANCO     30

#define NIVEL_MEDIO_SENSORES 	( S_BLANCO + (S_NEGRO - S_BLANCO) / 2 )

#define SDRE_NEGRO   250
#define	SDRE_BLANCO   20

#define SCRE_NEGRO   250
#define	SCRE_BLANCO   20

#define SIRE_NEGRO   250
#define	SIRE_BLANCO   20

#define SIRE_UMBRAL   ( (SIRE_NEGRO - SIRE_BLANCO) / 4 )
#define SCRE_UMBRAL   ( (SCRE_NEGRO - SCRE_BLANCO) / 4 )
#define SDRE_UMBRAL   ( (SDRE_NEGRO - SDRE_BLANCO) / 4 )

#define SIRE_MEDIO   ( (SIRE_NEGRO - SIRE_BLANCO) / 2 + SIRE_BLANCO )
#define SCRE_MEDIO   ( (SCRE_NEGRO - SCRE_BLANCO) / 2 + SCRE_BLANCO )
#define SDRE_MEDIO   ( (SDRE_NEGRO - SDRE_BLANCO) / 2 + SDRE_BLANCO )

#define SIRE_UMBRAL_P ( SIRE_MEDIO + SIRE_UMBRAL )
#define SIRE_UMBRAL_N ( SIRE_MEDIO - SIRE_UMBRAL )

#define SCRE_UMBRAL_P ( SCRE_MEDIO + SCRE_UMBRAL )
#define SCRE_UMBRAL_N ( SCRE_MEDIO - SCRE_UMBRAL )

#define SDRE_UMBRAL_P ( SDRE_MEDIO + SDRE_UMBRAL )
#define SDRE_UMBRAL_N ( SDRE_MEDIO - SDRE_UMBRAL )
*/
volatile uint8_t sdNivelMedio, sdNivelUmbralP, sdNivelUmbralN;
volatile uint8_t scNivelMedio, scNivelUmbralP, scNivelUmbralN;
volatile uint8_t siNivelMedio, siNivelUmbralP, siNivelUmbralN;

#define S_UMBRAL_CTE	3 


#define SD_NO_LINE_EEP_ADDR	2
#define SC_NO_LINE_EEP_ADDR	3
#define SI_NO_LINE_EEP_ADDR	4
#define SD_LINE_EEP_ADDR	5
#define SC_LINE_EEP_ADDR	6
#define SI_LINE_EEP_ADDR	7

#define MODO_EEPADDR	0
#define MODO_VALUE_EEPCLEAN	0
#define MODO_VALUE_START	0xFF
#define MODO_VALUE_LINEDEF	1
#define MODO_VALUE_COMPLETE	2
#define MODO_VALUE_ERROR	3

#define LINEA_BLANCA	1
#define LINEA_NEGRA	2

#endif
