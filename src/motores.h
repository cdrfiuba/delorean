#ifndef _MOTORES_
#define _MOTORES_

#include "board.h"
#include "definiciones.h"

// Completar cuales reducciones corresponden a A y cuales a B
//#define _REDUCCION_A_
#define _REDUCCION_B_

#define velocidadMD OCR1A
#define velocidadMI OCR1B


#define PRESCALER_PWM_OFF	(0<<CS12)|(0<<CS11)|(0<<CS10)
// y el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
#define PRESCALER_PWM_ON	(0<<CS12)|(0<<CS11)|(1<<CS10)

// TCCR1A -->  COM1A = 00 , COM1B = 00 y WGM = 14 (para usar un TOP fijo)
#define PWM_TCCR1A ( (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (1<<WGM11) | (0<<WGM10) )
#define PWM_TCCR1B ( (1<<WGM13) | (1<<WGM12) | PRESCALER_PWM_OFF )

// Interrupciones en comparaciones
#define TIMSK_VALUE  ( (1<<TOIE1) | (1<<OCIE1A) | (1<<OCIE1B) )

#define PWM_FREC 4000 // Frecuencia PWM
#define PWM_ICR1  (F_CPU/PWM_FREC)// Calcula ICR1
#if PWM_ICR1 != 2000
	#warning El fucking preprocesador hace cualquier cosa
#endif

#define PWM_VMEDIO (PWM_ICR1/2)
#if PWM_VMEDIO != 1000
	#warning El fucking preprocesador hace cualquier cosa 2
#endif

#define PWM_MAXPC_VEL_IZQ   0.4
#define PWM_MAXPC_VEL_DER   0.4

#define PWM_MAX_VEL_IZQ   (uint16_t)(PWM_VMEDIO * (1 + PWM_MAXPC_VEL_IZQ))
#define PWM_MAX_VEL_DER   (uint16_t)(PWM_VMEDIO * (1 + PWM_MAXPC_VEL_DER))

// Macros para setear la vel de los motores: 0% - 100% (con signo)
#define PwmMIvel(velocidad) (velocidadMI = (uint16_t)( PWM_VMEDIO * ( 1 + (velocidad/100.0) * PWM_MAXPC_VEL_IZQ ) ) )
#define PwmMDvel(velocidad) (velocidadMD = (uint16_t)( PWM_VMEDIO * ( 1 + (velocidad/100.0) * PWM_MAXPC_VEL_DER ) ) )

#define PwmMIvelRaw(velocidad) (velocidadMI = velocidad )
#define PwmMDvelRaw(velocidad) (velocidadMD = velocidad )

// Metodo para prender y apagar los PWM. Pone o saca el prescaler.
#define PwmStart() (TCCR1B |= PRESCALER_PWM_ON)
#define PwmStop()  (TCCR1B &=~ PRESCALER_PWM_OFF)

void motoresApagar(void);
void motoresEncender(void);
void configurarMotores(void);
void motorDerechoDetener(void);
void motorDerechoAvanzar(void);
void motorDerechoRetroceder(void);
void motorIzquierdoDetener(void);
void motorIzquierdoAvanzar(void);
void motorIzquierdoRetroceder(void);


#endif
