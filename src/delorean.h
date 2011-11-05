#ifndef _DELOREAN_
#define _DELOREAN_

// No hace falta definir F_CPU, esta en el makefile
// #define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include <avr/sleep.h>
//#include <avr/eeprom.h>

#include "board.h"
#include "motores.h"
#include "sensores.h"

typedef enum
{
    APAGADO, ON_TRACK,
    CORREGIR_IZ,
//    IZ_BAJO, IZ_MEDIO, IZ_ALTO, IZ_RET_MEDIO, IZ_RET_ALTO,
    CORREGIR_DE
//    DE_BAJO, DE_MEDIO, DE_ALTO, DE_RET_MEDIO, DE_RET_ALTO
} estado_t;


#endif
