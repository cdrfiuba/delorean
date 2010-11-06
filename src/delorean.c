#include "delorean.h"


/* Definicion de prototipos */
void startup(void);
//void set_interrupts(void);
void configurarPulsadorArranque(void);
void configurarTimer1(void);
//void decidirArranque(void);

/* ------------------------ */

//volatile uint8_t arrancar = 0;
//volatile uint8_t flagInt0 = 0;

//si se usan 2 sensores, utilizar solo Izquierda y derecha
char estadoActual = 0;


int main (void) {
	//Inicializaciones
	startup();
	
//	arrancar = 1;
//	motorDerechoAvanzar();
//	motorIzquierdoAvanzar();
	
	
	
	
	while(1)
	{	
		if (estadoActual == 0){
						motorDerechoDetener();
						motorIzquierdoDetener();
	//					sleep_mode();
		}
		else if (estadoActual == 1){
			motorDerechoAvanzar();
			motorIzquierdoAvanzar();
			TestADCs();
			capturarADc();
		}
		// Si saltó INT0
		//if (flagInt0 == 1) decidirArranque();
	}

}

/* Funciones */

void startup(void) {
	
	estadoActual = 0;
	velocidadMD = MOTORES_MAX_VEL;
	velocidadMI = MOTORES_MAX_VEL;
	//IntArranqueInit();

	Led1Init();
	Led2Init();
	Led3Init();
	//set_interrupts();
	configurarPulsadorArranque();
	configurarMotores();
	configurarTimer1();
	configurarADCs();
	PwmStart();
//	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}



void set_interrupts(void){
	GICR |= (1<<INT0); /* Esto habilita la interrupción INT0. */	
	MCUCR |= ((0<<ISC00) | (0<<ISC01)); /* Esto configura INT0 por nivel bajo. */
	//sei();
}

void configurarPulsadorArranque(void){
	IntArranqueInit();
	// Configuracion de modo de interrupcion (pagina 66)
	// MCUCR |= ((0<<ISC01) | (0<<ISC00)); // Nivel bajo. 
	// MCUCR |= ((0<<ISC01) | (1<<ISC00)); // Cualquier cambio de nivel
	// MCUCR |= ((1<<ISC01) | (0<<ISC00)); // Flanco descendente 
	MCUCR |= ((1<<ISC01) | (1<<ISC00)); // Flanco ascendente.

	// Esto habilita la interrupción INT0 escribiendo un '1' en el bit INT0
	// del registro global de interrupcions GICR
	SetBit(GICR, INT0); 
}


/*
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
*/


/**
	Interrupción del botón de arranque.
ISR(INT0_vect)
{
	// Apagamos INT0 para que no salte mientras mantenemos apretado.
	GICR &= ~(1<<INT0);
	
	flagInt0 = 1;  // Anunciar que la interrupción ocurrió.
	
	// Delay para debounce
//	_delay_ms(50);
}
**/


ISR(INT0_vect) {
//void interupINT0(void) {
	// Apagamos INT0 para que no salte mientras mantenemos apretado.
	// (creo que no hace falta. Cuando salta una interrupcion hay un 'cli'
	// automatico, y cuando se termina este ISR se clerea el flag de INT0
	// VERIFICAR
	// ClearBit(GICR, INT0);

	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer y dejar
	//  que
	_delay_ms(50);
	
	if (IsIntArranqueSet()==true) { 
		// significa que esta en 1 y hubo flanco ascendente genuino
		// se podria reemplazar la variable por poner apagar todo, poner 
		// el micro a dormir esperando solo esta interrupcion y luego
		// despertalo. Aca se lo despertaria
		if (estadoActual==0) estadoActual = 1;
		else estadoActual = 0;
	}
	SetBit(GIFR, INTF0);
	// Creo que no hace falta por lo mismo de arriba, VERIFICAR
//	SetBit(GICR,INT0);
}


ISR(TIMER1_OVF_vect)
{
	//PWM A RUEDA IZQUIERDA
	////MOTORES_MAX_VEL; //Cargamos las velocidades en los comparadores del timer
	OCR1A = velocidadMI;
	
	//PWM A RUEDA DERECHA
	OCR1B = velocidadMD;  //MOTORES_MAX_VEL; //
	return;
}

