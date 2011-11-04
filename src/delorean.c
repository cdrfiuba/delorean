#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
/* ------------------------ */

//si se usan 2 sensores, utilizar solo Izquierda y derecha
volatile uint8_t estadoSensores;
volatile estado_t estadoActual;

uint8_t si, sd;

int main (void)
{
	//Inicializaciones
	startup();
	
  velocidadMD = 200;
  velocidadMI = 20;
  Led2On();
 	while(1)
	{	
	}
}

/* Funciones */
void startup(void)
{
	estadoActual = APAGADO;

	Led1Init();
	Led2Init();
	Led3Init();
	
	Jumper1Init();
	Jumper2Init();
	
	configurarPulsadorArranque();
	configurarMotores();
	//configurarADCs();

	sei();
}


void configurarPulsadorArranque(void){
	IntArranqueInit();
	// Configuracion de modo de interrupcion (pagina 66)
	EICRA |= ((1<<ISC01) | (1<<ISC00)); // Flanco ascendente.

	// Esto habilita la interrupción INT0 escribiendo un '1' en el bit INT0
	// del registro de control de interrupciones externas.
	SetBit(EIMSK, INT0); 
}

ISR(INT0_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);
	if (IsIntArranqueSet()==true)
	{ 
		// significa que esta en 1 y hubo flanco ascendente genuino
		// se podria reemplazar la variable por poner apagar todo, poner 
		// el micro a dormir esperando solo esta interrupcion y luego
		// despertalo. Aca se lo despertaria
			if (estadoActual==APAGADO)
			{
				estadoActual = ON_TRACK;
				motoresEncender();
      	Led1On();
			}
			else {
				estadoActual = APAGADO;
				motoresApagar();
        Led1Off();
		}
	}
	SetBit(EIFR, INTF0);
}

