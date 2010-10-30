#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void set_interrupts(void);

/* ------------------------ */

volatile uint8_t arrancar = 1;


int main (void) {
	//Inicializaciones
	startup();

	while(1){
		//TestLeds();
	}

}

/* Funciones */

void startup(void) {
	
	IntArranqueInit();

	Led1Init();
	Led2Init();
	Led3Init();
	set_interrupts();
}

void set_interrupts(void){
	
	GICR |= (1<<INT0); /* Esto habilita la interrupción INT0*/
	MCUCR |= ((1<<ISC00) | (0<<ISC01)); /* Esto configura INT0 por flanco ascendente*/
	sei();
}

ISR(INT0_vect){

	if(arrancar == 1){
		Led1On();
		arrancar = 0;	
	}
	else {
		Led1Off();
		arrancar = 1;		
	}
}
