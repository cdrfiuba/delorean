#ifndef _BOXES_
#define _BOXES_

/* Tiene funciones para testear independientemente los distintos
 * perifericos 
 */

#include "delorean.h"
#include "board.h"
#include "motores.h"
#include "adc.h"

void TestLeds (void);
void TestLeds2 (void);
void TestADcNoInt (void);
void TestCerebroSimple(void);

void TestADcInt (void);

#endif
