#include "boxes.h"

void TestLeds(void){
	while(1){
		Led1On();
		_delay_ms(200);
		Led2On();
		_delay_ms(200);
		Led3On();
		_delay_ms(200);
		Led1Off();
		_delay_ms(200);
		Led2Off();
		_delay_ms(200);
		Led3Off();
		_delay_ms(200);
	}
}

//si se usan 2 sensores, utilizar solo Izquierda y derecha
char estado = 0;
char analogSensorI = 0;
char analogSensorC = 0;
char analogSensorD = 0;

//ISR(INT0_vect)
void interupINT0(void) {
	// Apagamos INT0 para que no salte mientras mantenemos apretado.
	// (creo que no hace falta. Cuando salta una interrupcion hay un 'cli'
	// automatico, y cuando se termina este ISR se clerea el flag de INT0
	// VERIFICAR
//	ClearBit(GICR, INT0);

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
		if (estado==0) estado = 1;
		else estado = 0;
	}
	else {
		// significa que fue un flanco ascendente producto del ruido de haber 
		// soltado el pulsador, se ignora
		// Aca se apagaria todo y se lo pone a dormir
	}
	
	// Creo que no hace falta por lo mismo de arriba, VERIFICAR
//	SetBit(GICR,INT0);
}


void configurarPulsadorArranque(void){
	IntArranqueInit();
	// Convifugacion de modo de interrupcion (pagina 66)
	// MCUCR |= ((0<<ISC01) | (0<<ISC00)); // Nivel bajo. 
	// MCUCR |= ((0<<ISC01) | (1<<ISC00)); // Cualquier cambio de nivel
	// MCUCR |= ((1<<ISC01) | (0<<ISC00)); // Flanco descendente 
	MCUCR |= ((1<<ISC01) | (1<<ISC00)); // Flanco ascendente.

	// Esto habilita la interrupción INT0 escribiendo un '1' en el bit INT0
	// del registro global de interrupcions GICR
	SetBit(GICR, INT0); 
}


int main2 (void) {

	//configuracion
	while(1){
		// si eliminamos la variable 'arrancar' no hace falta este condicional
		switch (estado){
			case 0:
				//motor detenido
				motorDerechoDetener();
				motorIzquierdoDetener();
				break;
			case 1:
				// Evaluar estados AD
				//
				motorDerechoAvanzar();
				motorIzquierdoAvanzar();
				break;
			case 2:
				break;
			default:
				break;
		}
	}
}


void configurarADCs(void){
	EncenderADC();
	// Seleccionamos la mayor velocidad de conversion, o sea prescaler 0
	ADCPrescalerSelec(0);
	
	// Alineacion a la izquierda
	AlineacionInit('I');

	//lo utilizamos en el modo single conversion
	//no seteamos free run
	//
	
	//Habilitamos la interrupcion de finalizacion de conversion AD
	SetBit(ADCSRA, ADIE);
}

ISR(ADC_vect){
	// ver canal en que se termino la conversion
	char temp = ADDeterminarCanalB();
	// guardar en variable correspondiente
	switch (temp){
		case 0:
			// AD0 es el sensor derecho
			analogSensorD = ADCH;
			// seleccionar siguiente canal
			ADSeleccionarCanalB(1);
			break;
		case 1:
			// AD1 es el sensor cental
			analogSensorC = ADCH;
			// seleccionar siguiente canal
			ADSeleccionarCanalB(2);
			break;
		case 2:
			// AD2 es el sensor izquierdo
			analogSensorI = ADCH;
			// seleccionar siguiente canal
			ADSeleccionarCanalB(0);
			break;
		default:
			// no esperado, se descarta el valor de conversion y se
			// vuelve a arrancar con el sensor derecho
			temp = ADCH;
			ADSeleccionarCanalB(0);
			break;
	}
}
