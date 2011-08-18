#ifndef _ADC_H_
#define _ADC_H_

#include "board.h"
#include <avr/eeprom.h>

/**
  Define para utilizar los conversores AD en el modo por interrupción.
  Quitar para trabajar en modo polling mediante las funciones
  @see capturarADc, capturarADcPRO
**/
#define _ADC_MODO_INT_

/**
  Variables globales que almacenan el último valor de los sensores infrarrojos.
  Declaradas como volatil porque pueden cambiar en cualquier momento en una interrupcion.
**/
volatile uint8_t analogSensorIzq;
volatile uint8_t analogSensorDer;

/**
  colorLinea tiene 1 si la linea es blanca y 0 si la linea es negra.
**/
volatile uint8_t colorLinea;

/**
  Variables con los umbrales para la lectura de los sensores.
  Media, UmbralP por arriba de la media y UmbralN por debajo de la media.
**/
volatile uint8_t sdNivelMedio, sdNivelUmbralP, sdNivelUmbralN;
volatile uint8_t siNivelMedio, siNivelUmbralP, siNivelUmbralN;

typedef enum{
		ES_333 = SI(3) | SC(3) | SD(3),
		ES_332 = SI(3) | SC(3) | SD(2),
		ES_331 = SI(3) | SC(3) | SD(1),
		ES_330 = SI(3) | SC(3) | SD(0),
		ES_323 = SI(3) | SC(2) | SD(3),
		ES_322 = SI(3) | SC(2) | SD(2),
		ES_321 = SI(3) | SC(2) | SD(1),
		ES_320 = SI(3) | SC(2) | SD(0),
		ES_313 = SI(3) | SC(1) | SD(3),
		ES_312 = SI(3) | SC(1) | SD(2),
		ES_311 = SI(3) | SC(1) | SD(1),
		ES_310 = SI(3) | SC(1) | SD(0),
		ES_303 = SI(3) | SC(0) | SD(3),
		ES_302 = SI(3) | SC(0) | SD(2),
		ES_301 = SI(3) | SC(0) | SD(1),
		ES_300 = SI(3) | SC(0) | SD(0),
		ES_233 = SI(2) | SC(3) | SD(3),
		ES_232 = SI(2) | SC(3) | SD(2),
		ES_231 = SI(2) | SC(3) | SD(1),
		ES_230 = SI(2) | SC(3) | SD(0),
		ES_223 = SI(2) | SC(2) | SD(3),
		ES_222 = SI(2) | SC(2) | SD(2),
		ES_221 = SI(2) | SC(2) | SD(1),
		ES_220 = SI(2) | SC(2) | SD(0),
		ES_213 = SI(2) | SC(1) | SD(3),
		ES_212 = SI(2) | SC(1) | SD(2),
		ES_211 = SI(2) | SC(1) | SD(1),
		ES_210 = SI(2) | SC(1) | SD(0),
		ES_203 = SI(2) | SC(0) | SD(3),
		ES_202 = SI(2) | SC(0) | SD(2),
		ES_201 = SI(2) | SC(0) | SD(1),
		ES_200 = SI(2) | SC(0) | SD(0),
		ES_133 = SI(1) | SC(3) | SD(3),
		ES_132 = SI(1) | SC(3) | SD(2),
		ES_131 = SI(1) | SC(3) | SD(1),
		ES_130 = SI(1) | SC(3) | SD(0),
		ES_123 = SI(1) | SC(2) | SD(3),
		ES_122 = SI(1) | SC(2) | SD(2),
		ES_121 = SI(1) | SC(2) | SD(1),
		ES_120 = SI(1) | SC(2) | SD(0),
		ES_113 = SI(1) | SC(1) | SD(3),
		ES_112 = SI(1) | SC(1) | SD(2),
		ES_111 = SI(1) | SC(1) | SD(1),
		ES_110 = SI(1) | SC(1) | SD(0),
		ES_103 = SI(1) | SC(0) | SD(3),
		ES_102 = SI(1) | SC(0) | SD(2),
		ES_101 = SI(1) | SC(0) | SD(1),
		ES_100 = SI(1) | SC(0) | SD(0),
		ES_033 = SI(0) | SC(3) | SD(3),
		ES_032 = SI(0) | SC(3) | SD(2),
		ES_031 = SI(0) | SC(3) | SD(1),
		ES_030 = SI(0) | SC(3) | SD(0),
		ES_023 = SI(0) | SC(2) | SD(3),
		ES_022 = SI(0) | SC(2) | SD(2),
		ES_021 = SI(0) | SC(2) | SD(1),
		ES_020 = SI(0) | SC(2) | SD(0),
		ES_013 = SI(0) | SC(1) | SD(3),
		ES_012 = SI(0) | SC(1) | SD(2),
		ES_011 = SI(0) | SC(1) | SD(1),
		ES_010 = SI(0) | SC(1) | SD(0),
		ES_003 = SI(0) | SC(0) | SD(3),
		ES_002 = SI(0) | SC(0) | SD(2),
		ES_001 = SI(0) | SC(0) | SD(1),
		ES_000 = SI(0) | SC(0) | SD(0)
    } estado_sensor_t;


void configurarADCs(void);
void capturarADc(void);
void capturarADcPRO(void);
uint8_t calibrarNiveles(void);
void calcularNiveles(void);
estado_sensor_t analizarSensores(void);


#define SD_NO_LINE_EEP_ADDR 2
#define SC_NO_LINE_EEP_ADDR 3
#define SI_NO_LINE_EEP_ADDR 4
#define SD_LINE_EEP_ADDR 5
#define SC_LINE_EEP_ADDR 6
#define SI_LINE_EEP_ADDR 7

#define MODO_EEPADDR 0
#define MODO_VALUE_EEPCLEAN 0
#define MODO_VALUE_START 0xFF
#define MODO_VALUE_LINEDEF 1
#define MODO_VALUE_COMPLETE 2
#define MODO_VALUE_ERROR 3

#define LINEA_EEPA DDR 1
#define LINEA_BLANCA 1
#define LINEA_NEGRA 2

#endif
