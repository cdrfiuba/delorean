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


void TestADCs(void){
		capturarADc();

		if(analogSensorIzq > NIVEL_MEDIO_SENSORES) Led1On();
		else Led1Off();
		if(analogSensorCen > NIVEL_MEDIO_SENSORES) Led2On();
		else Led2Off();
		if(analogSensorDer > NIVEL_MEDIO_SENSORES) Led3On();
		else Led3Off();
}




int main2 (void) {

	//configuracion
	while(1){
/*		// si eliminamos la variable 'arrancar' no hace falta este condicional
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
	*/}
}


