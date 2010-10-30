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
	IntArranqueOn();
	set_interrupts();

	Led1Init();
	Led2Init();
	Led3Init();
}

void set_interrupts(void){
	
	GICR |= (1<<INT0); /* Esto habilita la interrupcion */
	MCUCR |= ((1<<ISC00) | (0<<ISC01)); /* Esto habilida la interrupcion por flanco ascendente*/
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
