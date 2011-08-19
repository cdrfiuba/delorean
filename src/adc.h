#ifndef _ADC_H_
#define _ADC_H_

#include "board.h"
#include <avr/eeprom.h>

#define S_UMBRAL_CTE 1      // no se que hace

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


void configurarADCs(void);
void capturarADc(void);
void capturarADcPRO(void);
void calibrarNiveles(void);
void calcularNiveles(void);
uint8_t analizarSensores(void);

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
