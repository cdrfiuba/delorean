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

	while(1)
	{
		// Si saltó INT0
		if (flagInt0 == 1) decidirArranque();
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
	// Esperar mientras el pin permanezca bajo.
	while (IsIntArranqueSet() == 0) Led2On();//TestLeds();
	
	Led1Off(); Led2Off(); Led3Off();
	
	if (arrancar == 1)
	{
		// Juego de luces y arrancar!!!
		Led3On();
		_delay_ms(100);
		Led3Off();
		Led2On();
		_delay_ms(100);
		Led2Off();
		Led1On();
		_delay_ms(100);
		Led1Off();

		// Cambiar el estado para que la próxima vez que presionemos el botón se apague.
		arrancar = 0;
	}
	else
	{
		// Apagar y cambiar estado para que la próxima vez que presionemos el botón se encienda.
		arrancar = 1;
	}
	
	flagInt0 = 0;  // Apagar el flag de interrupción
	GICR |= (1<<INT0);  // Encendemos INT0.
}
		
/**
	Interrupción del botón de arranque.
**/
ISR(INT0_vect)
{
	// Apagamos INT0 para que no salte mientras mantenemos apretado.
	GICR &= ~(1<<INT0);
	
	flagInt0 = 1;  // Anunciar que la interrupción ocurrió.
	
	// Delay para debounce
	_delay_ms(50);
}
