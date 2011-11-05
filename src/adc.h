#ifndef _ADC_H_
#define _ADC_H_

#include "board.h"

/**
  Define para utilizar los conversores AD en el modo por interrupción.
  Quitar para trabajar en modo polling mediante las funciones
  @see capturarADc
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

void configurarADCs(void);
void capturarADc(void);
uint8_t analizarSensores(void);

#endif
