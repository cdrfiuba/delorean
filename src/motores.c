#include "motores.h"

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
}

void motorDerechoDetener(void){
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motorDerechoAvanzar(void){
	SetBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}
void motorDerechoRetroceder(void){
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motorIzquierdoDetener(void){
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

void motorIzquierdoAvanzar(void){
	SetBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

void motorIzquierdoRetroceder(void){
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	SetBit(PORT_MI_IN2, MI_IN2_NUMBER);
}
