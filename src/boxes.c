#include "boxes.h"



void ERROR_MAC(uint8_t estadomaq, uint8_t estadosens) {
	cli();
	motoresApagar();
	uint8_t i;
	while (1) {
		for(i=0;i<estadomaq;i++) {
			Led3On();
			_delay_ms(250);
			Led3Off();
			_delay_ms(250);
		}
		_delay_ms(1000);
		for(i=0;i<estadosens;i++) {
			Led2On();
			_delay_ms(250);
			Led2Off();
			_delay_ms(250);
		}
		_delay_ms(1000);
	}
}
		

/*
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


void TestEEPROM() {

	uint8_t i;

	if ( IsJumper1Set() == false ) eeprom_write_byte((uint8_t*)MODO_EEPADDR,MODO_VALUE_START);
	else {
		if ( IsJumper2Set() == false) {
			uint8_t tempo;
			tempo = eeprom_read_byte((uint8_t *) MODO_EEPADDR);
			Led1On();
			for (i=0;i<tempo;i++) {
				_delay_ms(200);
				Led1Off();
				_delay_ms(200);
				Led1On();
			}
//			if ( tempo == MODO_VALUE_ERROR ) Led1On();
//			else Led2On();
		}
		else {
			eeprom_write_byte((uint8_t *) MODO_EEPADDR, MODO_VALUE_ERROR);
			Led3On();
		}
	}
	while (1);

}


*/


