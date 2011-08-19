#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
void configurarTimer1(void);
estado_t evaluarEstado(estado_sensor_t );
void accionar(void);
/* ------------------------ */

//si se usan 2 sensores, utilizar solo Izquierda y derecha
volatile uint8_t estadoSensores;
volatile estado_t estadoActual;

uint8_t si, sd;

int main (void)
{
	//Inicializaciones
	startup();
	
	// Entra al modo calibración
	//if (IsJumper1Set() == false) calibrarNiveles();

 	motoresEncender();
 	
 	while(1)
	{	
	// Codigo Principal
#ifndef _ADC_MODO_INT_
		capturarADc();
#endif
		//estadoSensores = analizarSensores();
		//estadoActual = evaluarEstado(estadoSensores);
		//accionar();

   	    //motorIzquierdoAvanzar();
   	    //motorDerechoAvanzar();
   	    
		PwmMDvel(100);
		PwmMIvel(100);

/*		
    	if (analogSensorIzq > 127)
    	{
    	    motorIzquierdoAvanzar();
	    }
	    
    	if (analogSensorDer > 127)
    	{
    	    motorDerechoAvanzar();
	    }
*/
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
	
	//configurarPulsadorArranque();
	configurarMotores();
	configurarTimer1();
	configurarADCs();
	PwmStart();

	sei();
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

bool leerBoton1(void)
{
    if (IsIntArranqueSet())
    {
        _delay_ms(50);
        if (IsIntArranqueSet())
            return true;
    }
    return false;
}

ISR(INT0_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer y dejar
	//  que
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
				//motoresEncender();
			}
			else {
				estadoActual = APAGADO;
				//motoresApagar();
		}
	}
	SetBit(GIFR, INTF0);
}




void accionar(void)
{
	switch (estadoActual)
	{
		case ON_TRACK:
			PwmMDvel(100);
			PwmMIvel(100);
			break;
		case IZ_BAJO:
			PwmMDvel(80);
			PwmMIvel(100);
			break;
		case IZ_MEDIO:
			PwmMDvel(0);
			PwmMIvel(100);
			break;
    case IZ_ALTO:
			PwmMDvel(-100);
			PwmMIvel(100);
			break;
		case IZ_RET_MEDIO:
			PwmMDvel(90);
			PwmMIvel(100);
			break;
    case IZ_RET_ALTO:
			PwmMDvel(50);
			PwmMIvel(100);
			break;
		case DE_BAJO:
			PwmMDvel(100);
			PwmMIvel(80);
			break;
		case DE_MEDIO:
			PwmMDvel(100);
			PwmMIvel(0);
			break;
		case DE_ALTO:
			PwmMDvel(-100);
			PwmMIvel(100);
			break;
		case DE_RET_MEDIO:
			PwmMDvel(100);
			PwmMIvel(90);
			break;
		case DE_RET_ALTO:
			PwmMDvel(100);
			PwmMIvel(50);
			break;
		case APAGADO:
			break;
	}
}
