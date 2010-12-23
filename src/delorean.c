#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
void configurarTimer1(void);
estado_t evaluarEstado(estado_sensor_t );
void accionar_lento(void);
void accionar_rapido(void);
void accionar_raw(void);
/* ------------------------ */

//si se usan 2 sensores, utilizar solo Izquierda y derecha
void atras (void) {
	PwmMDvel(-130);
	PwmMIvel(-100);
	Led3On();
}

void adelante (void) {
	PwmMDvelRaw(400);
	PwmMIvelRaw(400);
	Led3On();
}

int main (void) {
	//Inicializaciones
	//fptr control = &accionar_lento;
	estado_sensor_t estadoSensores;

	startup();
	if ( IsJumper1Set() == false ) eeprom_write_byte((uint8_t*)MODO_EEPADDR,MODO_VALUE_START);
	if ( calibrarNiveles() != MODO_VALUE_COMPLETE ) while(1){};
	calcularNiveles();
	PwmMDvelRaw(VMAX);
	PwmMIvelRaw(VMAX);

	EmisorIzqOn();
	EmisorCenOn();
	EmisorDerOn();

	while(1) {	
		estadoSensores = analizarSensores();
		if ( ( ( estadoSensores & 0b00001100 ) >> 2 ) < 3 ) Led1On();
		else Led1Off();
		if ( ( estadoSensores & 0b00000011) < 3) Led2On();
		else Led2Off();
		estadoActual = evaluarEstado(estadoSensores);
		if ( IsJumper2Set() == true ) {
			accionar_raw();
		}
		else {
			adelante();
		}
		//accionar();
	}
	//while(1);
}

/* Funciones */

void startup(void)
{
	/*maxNivelSensor = 255;
	minNivelSensor = 200;
	colorLinea = 0;*/
		
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
	EmisorIzqOn();
	EmisorCenOn();
	EmisorDerOn();
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
		if (estadoActual==APAGADO) {
				estadoActual = ON_TRACK;
				motoresEncender();
		}
		else {
				estadoActual = APAGADO;
				motoresApagar();
		}
	}
	// Borramos el bit de interrupcion para no volver
	// a entrar por rebote.
	SetBit(GIFR, INTF0);
}

// Recibe el estado actual de los sensores y devuelve el futuro 
// estado de la maquina de estados
estado_t evaluarEstado(estado_sensor_t es){
	estado_t vd = estadoActual;
	switch (vd) {
		case APAGADO:
			break;
		case ON_TRACK:
			if ( es == ES_23) vd = IZ_BAJO;
			if ( es == ES_32) vd = DE_BAJO;
			break;
		case IZ_BAJO:
			if (es == ES_33) vd = ON_TRACK;
			if (es == ES_13) vd = IZ_MEDIO;
			break;
		case IZ_MEDIO:
			if (es == ES_33) vd = ON_TRACK;
			if (es == ES_23) vd = IZ_BAJO;
			if (es == ES_03) vd = IZ_ALTO;
			break;
		case IZ_ALTO:
			if(es == ES_33) vd = ON_TRACK;
			if(es == ES_13) vd = IZ_MEDIO;
			break;
		case DE_BAJO:
			if(es == ES_31) vd = DE_MEDIO;
			if(es == ES_33) vd = ON_TRACK;
			break;
		case DE_MEDIO:
			if(es == ES_32) vd = DE_BAJO;
			if(es == ES_33) vd = ON_TRACK;
			if(es == ES_30) vd = DE_ALTO;
			break;
		case DE_ALTO:
			if(es == ES_33) vd = ON_TRACK;
			if(es == ES_32) vd = DE_MEDIO;
			break;
	}
	if (estadoActual == APAGADO) return APAGADO;
	else return vd;
}

#define VEL_CRUCERO 100
#define VEL_CRUCERO_90 (VEL_CRUCERO*0.9)
#define VEL_CRUCERO_80 (VEL_CRUCERO*0.8)
#define VEL_CRUCERO_70 (VEL_CRUCERO*0.7)
#define VEL_CRUCERO_60 (VEL_CRUCERO*0.6)
#define VEL_CRUCERO_50 (VEL_CRUCERO*0.5)
#define VEL_CRUCERO_55 (VEL_CRUCERO*0.55)
#define VEL_CRUCERO_40 (VEL_CRUCERO*0.4)
#define VEL_CRUCERO_30 (VEL_CRUCERO*0.3)
#define VEL_CRUCERO_20 (VEL_CRUCERO*0.2)
#define VEL_CRUCERO_10 (VEL_CRUCERO*0.1)

void accionar_lento(void) {
	switch (estadoActual) {
		case ON_TRACK:
			PwmMDvel(VEL_CRUCERO);
			PwmMIvel(VEL_CRUCERO);
			break;
		case IZ_BAJO:
			PwmMDvel(VEL_CRUCERO_80);
			PwmMIvel(VEL_CRUCERO);
			break;
		case IZ_MEDIO:
			PwmMDvel(0);
			PwmMIvel(VEL_CRUCERO_90);
			break;
   		case IZ_ALTO:
			PwmMDvel(-VEL_CRUCERO_70);
			PwmMIvel(VEL_CRUCERO_90);
			_delay_ms(50);
			PwmMDvel(VEL_CRUCERO_80);
			PwmMIvel(VEL_CRUCERO);
			break;
		case DE_BAJO:
			PwmMDvel(VEL_CRUCERO);
			PwmMIvel(VEL_CRUCERO_80);
			break;
		case DE_MEDIO:
			PwmMDvel(VEL_CRUCERO_90);
			PwmMIvel(0);
			break;
		case DE_ALTO:
			PwmMDvel(VEL_CRUCERO_90);
			PwmMIvel(-VEL_CRUCERO_70);
			_delay_ms(50);
			PwmMDvel(VEL_CRUCERO);
			PwmMIvel(VEL_CRUCERO_80);

			break;
		case APAGADO:
			break;
	}
}

void accionar_rapido(void) {
	switch (estadoActual) {
		case ON_TRACK:
			PwmMDvel(VEL_CRUCERO*1.2);
			PwmMIvel(VEL_CRUCERO*1.2);
			break;
		case IZ_BAJO:
			//PwmMDvel(VEL_CRUCERO_80);
			//PwmMIvel(VEL_CRUCERO);
			break;
		case IZ_MEDIO:
			//PwmMDvel(0);
			//PwmMIvel(VEL_CRUCERO);
			break;
   		case IZ_ALTO:
			PwmMDvel(-VEL_CRUCERO_55);
			PwmMIvel(VEL_CRUCERO);
			//_delay_ms(50);
			//PwmMDvel(VEL_CRUCERO);
			//PwmMIvel(0);
			_delay_ms(20);
			break;
		case DE_BAJO:
			//PwmMDvel(VEL_CRUCERO);
			//PwmMIvel(VEL_CRUCERO_80);
			break;
		case DE_MEDIO:
			//PwmMDvel(VEL_CRUCERO_90);
			//PwmMIvel(0);
			break;
		case DE_ALTO:
			PwmMDvel(VEL_CRUCERO);
			PwmMIvel(-VEL_CRUCERO_55);
			//_delay_ms(50);
			//PwmMDvel(VEL_CRUCERO);
			//PwmMIvel(0);
			break;
		case APAGADO:
			break;
	}
}


void accionar_raw(void) {
	switch (estadoActual) {
		case ON_TRACK:
			PwmMDvelRaw(VMAX);
			PwmMIvelRaw(VMAX);
			break;
		case IZ_BAJO:
			PwmMDvelRaw(VMAX-5);
			PwmMIvelRaw(VMAX);
			break;
		case IZ_MEDIO:
			PwmMDvelRaw(VMAX-10);
			PwmMIvelRaw(VMAX);
			break;
   		case IZ_ALTO:
			PwmMDvelRaw(VMIN+20);
			PwmMIvelRaw(VMAX);
			break;
		case DE_BAJO:
			PwmMDvelRaw(VMAX);
			PwmMIvelRaw(VMAX-5);
			break;
		case DE_MEDIO:
			PwmMDvelRaw(VMAX);
			PwmMIvelRaw(VMIN+20);
			break;
		case DE_ALTO:
			PwmMDvelRaw(VMAX);
			PwmMIvelRaw(VMAX-30);
			break;
		case APAGADO:
			break;
	}
}
