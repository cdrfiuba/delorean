#ifndef _MOTORES_
#define _MOTORES_

#include "board.h"
#include "definiciones.h"

//volatile uint16_t velocidadMD;
//volatile uint16_t velocidadMI;

#define velocidadMD OCR1B
#define velocidadMI OCR1A

//#define MOTORES_TOP_CUENTA 		800
//#define MOTORES_MAX_VEL				400

#define PRESCALER_PWM_OFF	(0<<CS12)|(0<<CS11)|(0<<CS10)
// y el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
#define PRESCALER_PWM_ON	(0<<CS12)|(0<<CS11)|(1<<CS10)

// TCCR1A -->  COM1A = 00 , COM1B = 00 y WGM = 14 (para usar un TOP fijo)
#define PWM_TCCR1A ( (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (1<<WGM11) | (0<<WGM10) )
#define PWM_TCCR1B ( (1<<WGM13) | (1<<WGM12) | PRESCALER_PWM_OFF )

// Interrupciones en comparaciones
#define TIMSK_VALUE  ( (1<<TOIE1) | (1<<OCIE1A) | (1<<OCIE1B) )


#define PWM_FREC 20000UL // Frecuencia PWM
//#define PWM_ICR1  (F_CPU/PWM_FREC)// Calcula ICR1
#define PWM_ICR1  500UL

#define VMAX 350
#define VMEDIO 250
#define VMIN 100

#define PWM_MAX_VEL_IZQ   0.443
#define PWM_MAX_VEL_DER   0.440

// Macros para setear la vel de los motores: 0% - 100%
#define PwmMIvel(velocidad) (velocidadMI = ( (PWM_ICR1/2.0) * ( 1 +  (velocidad/100.0) * PWM_MAX_VEL_IZQ ) ) )
#define PwmMDvel(velocidad) (velocidadMD = ( (PWM_ICR1/2.0) * ( 1 +  (velocidad/100.0) * PWM_MAX_VEL_DER ) ) )

#define PwmMIvelRaw(velocidad) (OCR1A = velocidad )
#define PwmMDvelRaw(velocidad) (OCR1B = velocidad )

// Metodo para prender y apagar los PWM. Pone o saca el prescaler.
//void pwm_start(void);
//void pwm_stop(void);


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
