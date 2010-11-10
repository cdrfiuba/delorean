#ifndef _BOXES_
#define _BOXES_

/* Tiene funciones para testear independientemente los distintos
 * perifericos 
 */

#include "delorean.h"
#include "board.h"
#include "motores.h"

void TestLeds (void);
void TestADcNoInt (void);
void TestCerebroSimple(void);

#define S_NEGRO    255
#define S_BLANCO     0
#define NIVEL_MEDIO_SENSORES 	( S_BLANCO + (S_NEGRO - S_BLANCO) / 2 )
void TestADcInt (void);

#endif
