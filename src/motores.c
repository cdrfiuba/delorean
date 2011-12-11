#include "motores.h"

void configurarTimer2(void);

inline void motoresEncender(void) {
  // En el primer ciclo, solo hace la comparación en el flanco descendente
  // Con lo cual, si en la comparacion se usa toggle habrá que considerar este
  // cambio de fase
  // Si queremos que en la base de la rampa In1 este en cero, entonces aca
  // debemos ponerlo en 1
  // El TCNT2 Tuvimos que ponerlo en 255 porque sino en el primer ciclo (luego
  // del reset) tenia una comparacion de menos.
	SetBit(PORT_MI_IN1, MI_IN1_NUMBER);
	ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);
	SetBit(PORT_MD_IN1, MD_IN1_NUMBER);
	ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);
  TCNT2 = 255;
	SetBit(PORT_MD_EN, MD_EN_NUMBER);
	SetBit(PORT_MI_EN, MI_EN_NUMBER);
  PwmStart();
}

inline void motoresApagar(void) {
	ClearBit(PORT_MD_EN, MD_EN_NUMBER);
	ClearBit(PORT_MI_EN, MI_EN_NUMBER);
  PwmStop();
}

void configurarMotores(void) {
	//Configuramos como salidas los pines de PWM
	SetBit(DDR_MI_EN, MI_EN_NUMBER);
	SetBit(DDR_MD_EN, MD_EN_NUMBER);

	//Configuramos como salidas los pines "In's" del puente H
	SetBit(DDR_MI_IN1, MI_IN1_NUMBER);
	SetBit(DDR_MI_IN2, MI_IN2_NUMBER);
	SetBit(DDR_MD_IN1, MD_IN1_NUMBER);
	SetBit(DDR_MD_IN2, MD_IN2_NUMBER);

	motoresApagar();
	configurarTimer2();
  
	velocidadMD = PWM_VMEDIO;
	velocidadMI = PWM_VMEDIO;
}

void configurarTimer2(void) {
	// Configuracion del timer 2 para el PWM
	TCCR2A = PWM_TCCR2A;  
	TCCR2B = PWM_TCCR2B; 	

	//Habilitamos la interrupcion del Timer2 de comparacion
	TIMSK2 = TIMSK_VALUE;
}

//PWM A RUEDA DERECHA
ISR(TIMER2_COMPA_vect, ISR_NAKED) {
  SetBit(PIN_MD_IN1,MD_IN1_NUMBER);
  SetBit(PIN_MD_IN2,MD_IN2_NUMBER);
  Reti();
}

//PWM A RUEDA IZQUIERDA
ISR(TIMER2_COMPB_vect,ISR_NAKED) {
  SetBit(PIN_MI_IN1,MI_IN1_NUMBER);
  SetBit(PIN_MI_IN2,MI_IN2_NUMBER);
  Reti();
}


void Avanzar(){
  velocidadMD = 128 + 90;
  velocidadMI = 128 + 90;
}

void GirarIzquierda(){
  velocidadMD = 128 + 60;
  velocidadMI = 128 - 60;
}

void GirarDerecha(){
  velocidadMD = 128 - 60;
  velocidadMI = 128 + 60;
}

void Detenido(){
  velocidadMD = 128;
  velocidadMI = 128;
}

void CorreccionIzquierda(){
  velocidadMD = 128 + 90;
  velocidadMI = 128 + 60;
}

void CorreccionDerecha(){
  velocidadMD = 128 + 60;
  velocidadMI = 128 + 90;
}
