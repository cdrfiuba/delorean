#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
void configurarTimer1(void);
estado_t evaluarEstado(estado_sensor_t );
void accionar(void);
/* ------------------------ */

//si se usan 2 sensores, utilizar solo Izquierda y derecha


int main (void) {
	//Inicializaciones
	startup();
	
	calibrarNiveles();
	
	while(1)
	{	
	// Codigo Principal
	//
		capturarADc();
		//capturarADcPRO();
		estadoSensores = analizarSensores();
		estadoActual = evaluarEstado(estadoSensores);
		accionar();
	}
}

/* Funciones */

void startup(void)
{
	/*maxNivelSensor = 255;
	minNivelSensor = 200;
	colorLinea = 0;*/
		
	estadoActual = APAGADO;
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
		if (estadoActual==APAGADO) estadoActual = ON_TRACK;
		else estadoActual = APAGADO;
	}
	SetBit(GIFR, INTF0);
	// Creo que no hace falta por lo mismo de arriba, VERIFICAR
//	SetBit(GICR,INT0);
}




// Recibe el estado actual de los sensores y devuelve el futuro 
// estado de la maquina de estados
estado_t evaluarEstado(estado_sensor_t es){
	estado_t vd = estadoActual;
	switch (vd) {
		case APAGADO:
			motorDerechoDetener();
			motorIzquierdoDetener();
			break;
		case ON_TRACK:
			if (es == ES_011) vd = IZ_BAJO;
			if (es == ES_110) vd = DE_BAJO;
			if (es == ES_100) vd = DE_MEDIO;
			if (es == ES_001) vd = IZ_MEDIO;
			break;
		case IZ_BAJO:
			if (es == ES_010) vd = ON_TRACK;
			if (es == ES_110) vd = DE_BAJO;
			if (es == ES_001) vd = IZ_MEDIO;
			if (es == ES_000) vd = IZ_ALTO;
			break;
		case IZ_MEDIO:
			if (es == ES_011) vd = IZ_BAJO;
			if (es == ES_010) vd = ON_TRACK;
			if (es == ES_000) vd = IZ_ALTO;
			break;
		case IZ_ALTO:
			if(es == ES_010) vd = ON_TRACK;
			if(es == ES_001) vd = IZ_MEDIO;
			break;
		case DE_BAJO:
			if(es == ES_110) vd = DE_MEDIO;
			if(es == ES_000) vd = DE_ALTO;
			if(es == ES_011) vd = IZ_BAJO;
			if(es == ES_010) vd = ON_TRACK;
			break;
		case DE_MEDIO:
			if(es == ES_110) vd = DE_BAJO;
			if(es == ES_010) vd = ON_TRACK;
			if(es == ES_000) vd = DE_ALTO;
			break;
		case DE_ALTO:
			if(es == ES_010) vd = ON_TRACK;
			if(es == ES_100) vd = DE_MEDIO;
			break;
	}
	if (estadoActual == APAGADO) return APAGADO;
	else return vd;
}

#define VEL_CRUCERO 100

void accionar(void) {
	switch (estadoActual) {
		case ON_TRACK:
			motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO);
			break;
		case IZ_BAJO:
			motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO-35);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO);
			break;
		case IZ_MEDIO:
			motorDerechoRetroceder();
			PwmMDvel(VEL_CRUCERO-25);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO-25);
			/*motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO-35);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO);*/
			break;
    	case IZ_ALTO:
			motorDerechoRetroceder();
			PwmMDvel(VEL_CRUCERO-10);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO-10);
			break;
		case DE_BAJO:
			motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO-20);
			break;
		case DE_MEDIO:
			motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO-25);
			motorIzquierdoRetroceder();
			PwmMIvel(VEL_CRUCERO-25);
			/*motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO);
			motorIzquierdoAvanzar();
			PwmMIvel(VEL_CRUCERO-35);*/
			break;
		case DE_ALTO:
			motorDerechoAvanzar();
			PwmMDvel(VEL_CRUCERO-10);
			motorIzquierdoRetroceder();
			PwmMIvel(VEL_CRUCERO-10);
			break;
		case APAGADO:
			break;
	}
}
