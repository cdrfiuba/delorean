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

// para testear los adc cuanto 
void TestADcNoInt(void){
		capturarADc();
		//capturarADcPRO();
		if(analogSensorIzq > NIVEL_MEDIO_SENSORES) Led1On();
		else Led1Off();
		if(analogSensorCen > NIVEL_MEDIO_SENSORES) Led2On();
		else Led2Off();
		if(analogSensorDer > NIVEL_MEDIO_SENSORES) Led3On();
		else Led3Off();
}

void TestADcInt(void){
//		uint8_t media = (minNivelSensor + maxNivelSensor) / 2;
//		if(analogSensorIzq > media) Led1On();
		if(analogSensorIzq > NIVEL_MEDIO_SENSORES) Led1On();
		else Led1Off();
//		if(analogSensorCen > media) Led2On();
		if(analogSensorCen > NIVEL_MEDIO_SENSORES) Led2On();
		else Led2Off();
//		if(analogSensorDer > media) Led3On();
		if(analogSensorDer > NIVEL_MEDIO_SENSORES) Led3On();
		else Led3Off();
}

void TestCerebroSimple(void) {

		if (estadoActual == APAGADO){
						motorDerechoDetener();
						motorIzquierdoDetener();
		}
		else if (estadoActual == ON_TRACK){
			motorDerechoAvanzar();
			PwmMDvel(100);
			motorIzquierdoAvanzar();
			PwmMIvel(100);
			TestADcNoInt();
			capturarADc();
		}
}

