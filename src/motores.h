#ifndef _MOTORES_
#define _MOTORES_

#include "board.h"
#include "definiciones.h"

volatile uint16_t velocidadMD;
volatile uint16_t velocidadMI;


//#define MOTORES_TOP_CUENTA 		800
//#define MOTORES_MAX_VEL				400

// TCCR1A -->  COM1A = 11 , COM1B = 11 y WGM = 8 (para usar un TOP fijo)
#define PWM_TCCR1A (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10)
// TCCR1B = (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10); 
#define PWM_TCCR1B (1<<WGM13)|(0<<WGM12)|PRESCALER_PWM_OFF

#define PRESCALER_PWM_OFF	(0<<CS12)|(0<<CS11)|(0<<CS10)
// y el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
#define PRESCALER_PWM_ON	(0<<CS12)|(0<<CS11)|(1<<CS10)

#define PWM_FREC 5000 // Frecuencia PWM
#define PWM_ICR1  (F_CPU/(2*1*PWM_FREC) )// Calcula ICR1

#define PWM_MAX_VEL   (PWM_ICR1 * 0.55)

// Macros para setear la vel de los motores: 0% - 100%
#define PwmMIvel(velocidad) (velocidadMI = (velocidad)*PWM_MAX_VEL/100)
#define PwmMDvel(velocidad) (velocidadMD = (velocidad)*PWM_MAX_VEL/100)


// Metodo para prender y apagar los PWM. Pone o saca el prescaler.
void pwm_start(void);
void pwm_stop(void);


#define PwmStart() (TCCR1B |= PRESCALER_PWM_ON)
#define PwmStop()	 (TCCR1B &=~ PRESCALER_PWM_OFF)

void configurarMotores(void);
void motorDerechoDetener(void);
void motorDerechoAvanzar(void);
void motorDerechoRetroceder(void);
void motorIzquierdoDetener(void);
void motorIzquierdoAvanzar(void);
void motorIzquierdoRetroceder(void);


#endif
