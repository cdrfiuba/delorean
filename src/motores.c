#include "motores.h"

void configurarTimer1(void);

void configurarMotores(void){
	//Configuramos como salidas los pines de PWM
	SetBit(DDR_MI_PWM, MI_PWM_NUMBER);
	SetBit(DDR_MD_PWM, MD_PWM_NUMBER);

	//Configuramos como salidas los pines "In's" del puente H
	SetBit(DDR_MI_IN1, MI_IN1_NUMBER);
	SetBit(DDR_MI_IN2, MI_IN2_NUMBER);
	SetBit(DDR_MD_IN1, MD_IN1_NUMBER);
	SetBit(DDR_MD_IN2, MD_IN2_NUMBER);

	motorDerechoDetener();
	motorIzquierdoDetener();
	configurarTimer1();


	ICR1 = MOTORES_TOP_CUENTA;  // Esto define al TOP

	// PWM A   MOTOR DERECHO
	OCR1A = 0;

	// PWM B   MOTOR IZQUIERDO
	OCR1B = 0;
}

void motorDerechoDetener(void){
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motorDerechoAvanzar(void){
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
}
void motorDerechoRetroceder(void){
	SetBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motorIzquierdoDetener(void){
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

void motorIzquierdoAvanzar(void){
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	SetBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

void motorIzquierdoRetroceder(void){
	SetBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}


void configurarTimer1(void){
	// Configuracion del timer 1 para el PWM
	
	
	TCCR1A = PWM_TCCR1A;  
	TCCR1B = PWM_TCCR1B; 	

	ICR1 = PWM_ICR1; 
	//Habilitamos la interrupcion del Timer1 del overflow
	TIMSK = (1<<TOIE1);
}
