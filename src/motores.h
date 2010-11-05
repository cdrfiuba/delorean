#ifndef _MOTORES_
#define _MOTORES_

#include "board.h"
#include "definiciones.h"

#define MOTORES_MAX_VEL	400
#define MOTORES_TOP_CUENTA 800


void configurarMotores(void);
void motorDerechoDetener(void);
void motorDerechoAvanzar(void);
void motorDerechoRetroceder(void);
void motorIzquierdoDetener(void);
void motorIzquierdoAvanzar(void);
void motorIzquierdoRetroceder(void);


#endif
