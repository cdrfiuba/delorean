#ifndef _DELOREAN_
#define _DELOREAN_

// No hace falta definir F_CPU, esta en el makefile
// #define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

#include "board.h"
#include "motores.h"
#include "adc.h"

//#include "boxes.h"

typedef enum{
    APAGADO,
    ON_TRACK,
    IZ_BAJO,
    IZ_MEDIO,
    IZ_ALTO,
    DE_BAJO,
    DE_MEDIO,
    DE_ALTO
    } estado_t;

estado_t estadoActual;

#endif
