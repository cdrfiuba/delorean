#include "board.h"
#include "definiciones.h"

#define MOTORES_MAX_VEL	0x02F0F
#define MOTORES_TOP_CUENTA 0X02FF


void configurarMotores(void);
void motorDerechoDetener(void);
void motorDerechoAvanzar(void);
void motorDerechoRetroceder(void);
void motorIzquierdoDetener(void);
void motorIzquierdoAvanzar(void);
void motorIzquierdoRetroceder(void);
