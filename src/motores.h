#include "board.h"
#include "definiciones.h"

#define MOTORES_MAX_VEL	0x00FF



void configurarMotores(void);
void motorDerechoDetener(void);
void motorDerechoAvanzar(void);
void motorDerechoRetroceder(void);
void motorIzquierdoDetener(void);
void motorIzquierdoAvanzar(void);
void motorIzquierdoRetroceder(void);
