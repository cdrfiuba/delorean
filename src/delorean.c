#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void set_interrupts(void);

/* ------------------------ */

volatile uint8_t arrancar = 0;
volatile uint8_t flagInt0 = 0;


int main (void) {
	//Inicializaciones
	startup();
	
	arrancar = 1;

	while(1){
		//TestLeds();
		if (flagInt0 == 1) decidirArranque();
		//if (IsIntArranqueSet()) Led3On(); else Led3Off();
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
	GICR |= (1<<INT0); /* Esto habilita la interrupción INT0. */	
	MCUCR |= ((0<<ISC00) | (0<<ISC01)); /* Esto configura INT0 por nivel bajo. */
	sei();
}

void decidirArranque()
{
	// Esperar mientras el pin permanezca
	while (IsIntArranqueSet() == 0) Led2On();//TestLeds();
	Led1Off(); Led2Off(); Led3Off();
	
	if (arrancar == 1)
	{
		Led3On();
		_delay_ms(100);
		Led3Off();
		Led2On();
		_delay_ms(100);
		Led2Off();
		Led1On();
		_delay_ms(100);
		Led1Off();

		arrancar = 0;
	}
	else
	{
		Led1Off();
		arrancar = 1;
	}
	
	flagInt0 = 0;
	GICR |= (1<<INT0); /* Encendemos INT0. */
}
		
/**
	Interrupción del botón de arranque.
**/
ISR(INT0_vect)
{
	GICR &= ~(1<<INT0); /* Apagamos INT0. */	
	
	flagInt0 = 1;
	
	// Delay para debounce
	_delay_ms(50);
}
