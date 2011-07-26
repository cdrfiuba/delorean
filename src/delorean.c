#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
void configurarTimer1(void);
estado_t evaluarEstado(estado_sensor_t );
void accionar(void);
/* ------------------------ */

//si se usan 2 sensores, utilizar solo Izquierda y derecha
volatile estado_sensor_t estadoSensores;
volatile estado_t estadoActual;


int main (void) {
	//Inicializaciones
	startup();

	if ( IsJumper1Set() == false ) eeprom_write_byte((uint8_t*)MODO_EEPADDR,MODO_VALUE_START);
 	if ( calibrarNiveles() != MODO_VALUE_COMPLETE ) while(1){}; 	
	calcularNiveles();
	
	while(1)
	{	
	// Codigo Principal
	//
#ifndef _ADC_MODO_INT_
		capturarADc();
#endif
		estadoSensores = analizarSensores();
		estadoActual = evaluarEstado(estadoSensores);
		accionar();
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



ISR(INT0_vect) {
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
			if (estadoActual==APAGADO) {
				estadoActual = ON_TRACK;
				motoresEncender();
			}
			else {
				estadoActual = APAGADO;
				motoresApagar();
		}
	}
	SetBit(GIFR, INTF0);
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
			switch (es) {
				case ES_031:
				case ES_032:
					vd = IZ_BAJO;
					break;
				case ES_130:
				case ES_230:
					vd = DE_BAJO;
					break;
//				case ES_030:
//					break;
				default:
//					ERROR_MAC((uint8_t)ON_TRACK, (uint8_t)es);
					break;
			}
			break;
		case IZ_BAJO:
			switch (es) {
				case ES_030:
					vd = ON_TRACK;
					break;
				case ES_033:
				case ES_023:
					vd = IZ_MEDIO;
					break;
	// Lo siguiente es que sigue en el mismo estado
				case ES_031:
				case ES_032:
					break;
				default:
					ERROR_MAC((uint8_t)IZ_BAJO, (uint8_t)es);
					break;
			}
			break;
		case IZ_MEDIO:
			switch (es) {
				case ES_031:
				case ES_032:
					vd = IZ_RET_MEDIO;
					break;
				case ES_013:
				case ES_003:
				case ES_002:
					vd = IZ_ALTO;
					break;
				default:
//					ERROR_MAC((uint8_t)IZ_MEDIO);
					break;
			}
			break;
		case IZ_ALTO:
			switch (es) {
				case ES_023:
					vd = IZ_RET_ALTO;
					break;
				default:
//					ERROR_MAC((uint8_t)IZ_ALTO);
					break;
			}
			break;
		case IZ_RET_ALTO:
			switch (es) {
				case ES_031:
				case ES_032:
					vd = IZ_RET_MEDIO;
					break;
				case ES_013:
				case ES_003:
				case ES_002:
					vd = IZ_ALTO;
					break;
				default:
	//				ERROR_MAC((uint8_t)IZ_RET_ALTO);
					break;
			}
			break;
		case IZ_RET_MEDIO:
			switch (es) {
				case ES_030:
					vd = ON_TRACK;
					break;
				case ES_033:
				case ES_023:
					vd = IZ_MEDIO;
					break;
				default:
//					ERROR_MAC((uint8_t)IZ_RET_MEDIO);
					break;
			}
			break;
		case DE_BAJO:
			switch (es) {
				case ES_030:
					vd = ON_TRACK;
					break;
				case ES_330:
				case ES_320:
					vd = DE_MEDIO;
					break;
	// Lo siguiente es que sigue en el mismo estado
//				case ES_130:
//				case ES_230:
//					break;
				default:
//					ERROR_MAC((uint8_t)DE_BAJO, (uint8_t)es);
					break;
			}
			break;
		case DE_MEDIO:
			switch (es) {
				case ES_130:
				case ES_230:
					vd = DE_RET_MEDIO;
					break;
				case ES_310:
				case ES_300:
				case ES_200:
					vd = DE_ALTO;
					break;
				default:
//					ERROR_MAC((uint8_t)DE_MEDIO);
					break;
			}
			break;
		case DE_ALTO:
			switch (es) {
				case ES_320:
					vd = DE_RET_ALTO;
					break;
				default:
//					ERROR_MAC((uint8_t)DE_ALTO);
					break;
			}
			break;
		case DE_RET_ALTO:
			switch (es) {
				case ES_130:
				case ES_230:
					vd = DE_RET_MEDIO;
					break;
				case ES_310:
				case ES_300:
				case ES_200:
					vd = DE_ALTO;
					break;
				default:
//					ERROR_MAC((uint8_t)DE_RET_ALTO);
					break;
			}
			break;
		case DE_RET_MEDIO:
			switch (es) {
				case ES_030:
					vd = ON_TRACK;
					break;
				case ES_330:
				case ES_320:
					vd = DE_MEDIO;
					break;
				default:
//					ERROR_MAC((uint8_t)DE_RET_MEDIO);
					break;
			}
			break;
	}

	// Este condicional es por si cambia el estadoActual luego de evaluar el switch.
	// Esto podría pasar por el pulsador de arranque
	if (estadoActual == APAGADO) return APAGADO;
	else return vd;
}


void accionar(void) {
	switch (estadoActual) {
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
