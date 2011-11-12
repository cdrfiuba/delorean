#ifndef _MOTORES_
#define _MOTORES_

#include "board.h"
#include "definiciones.h"

// Completar cuales reducciones corresponden a A y cuales a B
//#define _REDUCCION_A_
#define _REDUCCION_B_

#define velocidadMD OCR2A
#define velocidadMI OCR2B

#define PWM_VMEDIO  0x80

#define PRESCALER_PWM_OFF	(0<<CS22)|(0<<CS21)|(0<<CS20)
// y el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
#define PRESCALER_PWM_ON	(0<<CS22)|(1<<CS21)|(0<<CS20)

// TCCR1A -->  COM1A = 00 , COM1B = 00 y WGM = 14 (para usar un TOP fijo)
#define PWM_TCCR2A ( (0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (1<<WGM20) )
#define PWM_TCCR2B ( (0<<WGM22) | PRESCALER_PWM_OFF )

// Interrupciones en comparaciones
#define TIMSK_VALUE  ( (1<<TOIE2) | (1<<OCIE2A) | (1<<OCIE2B) )

// Metodo para prender y apagar los PWM. Pone o saca el prescaler. (OJO ESTAMOS
// PISANDO EL WMGM22. Si este no es cero hay que arreglar estas dos lineas
// El problema esta en los bits 6 y 7. Ver la hoja de datos.
#define PwmStart() (TCCR2B = PRESCALER_PWM_ON)
#define PwmStop()  (TCCR2B = PRESCALER_PWM_OFF)


void motoresApagar(void);
void motoresEncender(void);
void configurarMotores(void);

void Avanzar();
void Detenido();
void GirarIzquierda();
void GirarDerecha();
void CorreccionIzquierda();
void CorreccionDerecha();

#endif
