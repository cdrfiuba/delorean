#include "motores.h"

void configurarTimer1(void);

inline void motoresEncender(void)
{
	SetBit(PORT_MD_EN, MD_EN_NUMBER);
	SetBit(PORT_MI_EN, MI_EN_NUMBER);
}

inline void motoresApagar(void)
{
	ClearBit(PORT_MD_EN, MD_EN_NUMBER);
	ClearBit(PORT_MI_EN, MI_EN_NUMBER);
}


inline void motorDerechoAvanzar(void)
{
#if defined _REDUCCION_A_
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
#elif defined _REDUCCION_B_
	SetBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
#else
	DEFINIR_REDUCCION
#endif
}

inline void motorDerechoRetroceder(void)
{
#if defined _REDUCCION_A_
	SetBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
#elif defined _REDUCCION_B_
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
#else
	DEFINIR_REDUCCION
#endif
}

inline void motorDerechoDetener(void)
{
	ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

inline void motorIzquierdoDetener(void)
{
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
}

inline void motorIzquierdoAvanzar(void)
{
#if defined _REDUCCION_A_
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	SetBit(PORT_MI_IN2, MI_IN2_NUMBER);
#elif defined _REDUCCION_B_
	SetBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
#else
	DEFINIR_REDUCCION
#endif
}

inline void motorIzquierdoRetroceder(void)
{
#if defined _REDUCCION_A_
	SetBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
#elif defined _REDUCCION_B_
	ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
	SetBit(PORT_MI_IN2, MI_IN2_NUMBER);
#else
	DEFINIR_REDUCCION
#endif
}

void configurarMotores(void)
{
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
	
	velocidadMD = PWM_VMEDIO;
	velocidadMI = PWM_VMEDIO;

	ICR1 = PWM_ICR1;  // Esto define al TOP
}

void configurarTimer1(void)
{
	// Configuracion del timer 1 para el PWM
	
	TCCR1A = PWM_TCCR1A;  
	TCCR1B = PWM_TCCR1B; 	

	ICR1 = PWM_ICR1; 
	//Habilitamos la interrupcion del Timer1 del overflow
	TIMSK = TIMSK_VALUE;
}


ISR(TIMER1_OVF_vect, ISR_NAKED)
{
	// Los valores de comparacion se actualizan automaticamente en BOTTOM
	motorDerechoAvanzar();
	motorIzquierdoAvanzar();
	Reti();
}

//PWM A RUEDA IZQUIERDA
ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
	motorDerechoRetroceder();
	Reti();
}

//PWM A RUEDA DERECHA
ISR(TIMER1_COMPB_vect, ISR_NAKED)
{
	motorIzquierdoRetroceder();
	Reti();
}

