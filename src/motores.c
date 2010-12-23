#include "motores.h"

void configurarTimer1(void);

inline void motoresEncender(void){
	SetBit(PORT_MD_EN, MD_EN_NUMBER);
	SetBit(PORT_MI_EN, MI_EN_NUMBER);
}

inline void motoresApagar(void){
	ClearBit(PORT_MD_EN, MD_EN_NUMBER);
	ClearBit(PORT_MI_EN, MI_EN_NUMBER);
}

inline void motorDerechoAvanzar(void){
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
}
inline void motorDerechoRetroceder(void){
	SetBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

inline void motorDerechoDetener(void){
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

inline void motorIzquierdoDetener(void){
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

inline void motorIzquierdoAvanzar(void){
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	SetBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

inline void motorIzquierdoRetroceder(void){
	SetBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

void configurarMotores(void){
	//Configuramos como salidas los pines de PWM
	SetBit(DDR_MI_EN, MI_EN_NUMBER);
	SetBit(DDR_MD_EN, MD_EN_NUMBER);

	//Configuramos como salidas los pines "In's" del puente H
	SetBit(DDR_MI_IN1, MI_IN1_NUMBER);
	SetBit(DDR_MI_IN2, MI_IN2_NUMBER);
	SetBit(DDR_MD_IN1, MD_IN1_NUMBER);
	SetBit(DDR_MD_IN2, MD_IN2_NUMBER);

	motoresApagar();
	configurarTimer1();
	

	ICR1 = PWM_ICR1;  // Esto define al TOP

	// PWM A   MOTOR DERECHO
//	OCR1A = 0;
//	velocidadMD = (ICR1/2);

	// PWM B   MOTOR IZQUIERDO
//	OCR1B = 0;
//	velocidadMI = (ICR1/2);
}




void configurarTimer1(void){
	// Configuracion del timer 1 para el PWM
	
	
	TCCR1A = PWM_TCCR1A;  
	TCCR1B = PWM_TCCR1B; 	

	ICR1 = PWM_ICR1; 
	//Habilitamos la interrupcion del Timer1 del overflow
	TIMSK = TIMSK_VALUE;
}

ISR(TIMER1_OVF_vect)
{
	// Los valores de comparacion se actualizan automaticamente en BOTTOM
	motorDerechoAvanzar();
	motorIzquierdoAvanzar();
}

//PWM A RUEDA IZQUIERDA
ISR(TIMER1_COMPA_vect)
{	
	motorIzquierdoRetroceder();
}

//PWM A RUEDA DERECHA
ISR(TIMER1_COMPB_vect)
{
	motorDerechoRetroceder();
}
