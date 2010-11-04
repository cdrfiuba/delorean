#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void set_interrupts(void);
void configurarTimer1(void);
void decidirArranque(void);

volatile uint16_t velocidadMD;
volatile uint16_t velocidadMI;

/* ------------------------ */

volatile uint8_t arrancar = 0;
volatile uint8_t flagInt0 = 0;




int main (void) {
	//Inicializaciones
	startup();
	
	arrancar = 1;
	motorDerechoAvanzar();
	motorIzquierdoAvanzar();
	
	velocidadMD = 380;
	velocidadMI = velocidadMD+15;
	
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

	configurarMotores();
	configurarTimer1();
	sei();
}

void set_interrupts(void){
	GICR |= (1<<INT0); /* Esto habilita la interrupción INT0. */	
	MCUCR |= ((0<<ISC00) | (0<<ISC01)); /* Esto configura INT0 por nivel bajo. */
	//sei();
}

void configurarTimer1(void){
	// Configuracion del timer 1 para el PWM
	
	// Estamos seteando COM1A = 11 , COM1B = 11 y WGM = 8 (para usar un TOP fijo)
	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0);
 	// y el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
	TCCR1B = (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10); 

	ICR1 = MOTORES_TOP_CUENTA;  // Esto define al TOP

	// PWM A   MOTOR DERECHO
	OCR1A = MOTORES_MAX_VEL; //50% cycle

	// PWM B   MOTOR IZQUIERDO
	OCR1B = MOTORES_MAX_VEL; //50% cycle

	//Habilitamos la interrupcion del Timer1 del overflow
	TIMSK = (1<<TOIE1);
}


void decidirArranque(void)
{
	// Esperar mientras el pin permanezca bajo.
	while (IsIntArranqueSet() == 0) Led2On();//TestLeds();
	
	Led1Off(); Led2Off(); Led3Off();
	
	velocidadMD+=5;
	
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

ISR(TIMER1_OVF_vect)
{
	//PWM A RUEDA IZQUIERDA
	OCR1A = velocidadMI;//MOTORES_MAX_VEL; //Cargamos las velocidades en los comparadores del timer

	//PWM A RUEDA DERECHA
	OCR1B = velocidadMD;  //MOTORES_MAX_VEL; //
	return;
}

