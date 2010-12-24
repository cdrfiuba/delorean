#include "adc.h" 
#include <util/delay.h>

volatile bool medicionValida;


estado_sensor_t analizarSensores(void) {
	uint8_t si=0, sc=0, sd=0;
	Led1Off();
	Led2Off();
	Led3Off();

	if (colorLinea == LINEA_NEGRA) {
		if (analogSensorIzq > siNivelUmbralP) si = 3;
		else if (analogSensorIzq > siNivelMedio) si = 2;
		else if (analogSensorIzq > siNivelUmbralN) si = 1;
		else si = 0;
		if (analogSensorCen > scNivelUmbralP) sc = 3;
		else if (analogSensorCen > scNivelMedio) sc = 2;
		else if (analogSensorCen > scNivelUmbralN) sc = 1;
		else sc = 0;
		if (analogSensorDer > sdNivelUmbralP) sd = 3;
		else if (analogSensorDer > sdNivelMedio) sd = 2;
		else if (analogSensorDer > sdNivelUmbralN) sd = 1;
		else sd = 0;
	}
	else if (colorLinea == LINEA_BLANCA) {
		if (analogSensorIzq > siNivelUmbralP) si = 0;
		else if (analogSensorIzq > siNivelMedio) si = 1;
		else if (analogSensorIzq > siNivelUmbralN) si = 2;
		else si = 3;
		if (analogSensorCen > scNivelUmbralP) sc = 0;
		else if (analogSensorCen > scNivelMedio) sc = 1;
		else if (analogSensorCen > scNivelUmbralN) sc = 2;
		else sc = 3;
		if (analogSensorDer > sdNivelUmbralP) sd = 0;
		else if (analogSensorDer > sdNivelMedio) sd = 1;
		else if (analogSensorDer > sdNivelUmbralN) sd = 2;
		else sd = 3;
	}
//	return ( (si<<2) | (sc<<0) );
	if (sd > 1) Led1On();
	if (sc > 1) Led2On();
	if (si > 1) Led3On();

	return ( (si<<4) | (sc<<2) | (sd<<0) );
}

void configurarADCs(void){
	EmisorIzqInit();
	EmisorCenInit();
	EmisorDerInit();
	analogSensorDer = 0;
	analogSensorCen = 0;
	analogSensorDer	= 0;
	
	EncenderADC();

	// Alineacion a la izquierda
	AlineacionInit('I');
	
	//lo utilizamos en el modo single conversion
	//no seteamos free run
	//
	
#ifdef _ADC_MODO_INT_
	// Modo con interrupcion
	// Seleccionamos la menor velocidad de muestreo. CK/128
	ADCPrescalerSelec(7);
	//Habilitar o no  la interrupcion de finalizacion de conversion AD
	SetBit(ADCSRA, ADIE);
	//ClearBit(ADCSRA, ADIE);
	medicionValida=false;
	IniciarConversion();
#else
	// Modo sin interrupcion (utilizamos la funcion capturarADC();
	// Seleccionamos la mayor velocidad de muestreo. CK/2
	ADCPrescalerSelec(0);
	//Habilitar o no  la interrupcion de finalizacion de conversion AD
	ClearBit(ADCSRA, ADIE);
	EmisorIzqOn();
	EmisorCenOn();
	EmisorDerOn();	
#endif
}



// se tuvo que hacer dos mediciones por sensor, ya que el tiempo de respuesta
// entre que el Emisor se enciende, y el receptor detecta algo, es mayor
// que el mayor tiempo de muestreo posible
// para utilizar interrupciones, definir la etiqueta _ADC_MODO_INT_
ISR(ADC_vect){
	// ver canal en que se termino la conversion
	char temp = ADDeterminarCanal();
	// guardar en variable correspondiente
	uint8_t temp2 = ADCH;	
	
	switch (temp){
		case ADC_NUM_SDRE:
			if (medicionValida==true) {
				// AD0 es el sensor derecho
				analogSensorDer = temp2;
				// seleccionar siguiente canal
				ADSeleccionarCanal(ADC_NUM_SCRE);
				medicionValida = false;
				IniciarConversion();
			}
			else {
				IniciarConversion();
				medicionValida = true;
				EmisorDerOff();
				EmisorCenOn();
			}
			break;
		case ADC_NUM_SCRE:
			if (medicionValida==true) {
				// AD1 es el sensor cental
				analogSensorCen = temp2;
				// seleccionar siguiente canal
				ADSeleccionarCanal(ADC_NUM_SIRE);
				medicionValida = false;
				IniciarConversion();
			}
			else {
				IniciarConversion();
				medicionValida = true;
				EmisorCenOff();
				EmisorIzqOn();
			}
			break;
		case ADC_NUM_SIRE:
			if (medicionValida==true) {
				// AD2 es el sensor izquierdo
				analogSensorIzq = temp2;
				// seleccionar siguiente canal
				ADSeleccionarCanal(ADC_NUM_SDRE);
				medicionValida = false;
				IniciarConversion();
			}
			else {
				IniciarConversion();
				medicionValida = true;
				EmisorIzqOff();
				EmisorDerOn();
			}
			break;
		default:
			// no esperado, se descarta el valor de conversion y se
			// vuelve a arrancar con el sensor derecho
			break;
	}
}

/**
	Calibra los niveles de blanco y negro y define el color de la linea.
**/
uint8_t calibrarNiveles(void) {
	uint8_t modo = 0;
//	uint16_t sd=0,si=0,sc=0;

	modo = eeprom_read_byte(MODO_EEPADDR);
	if (modo == MODO_VALUE_START) {
		Led3On();
		eeprom_write_byte((uint8_t*)MODO_EEPADDR,MODO_VALUE_EEPCLEAN);
	}
	else if (modo == MODO_VALUE_EEPCLEAN){
		_delay_ms(2);
		eeprom_write_byte((uint8_t*)SI_LINE_EEP_ADDR,analogSensorIzq);
		eeprom_write_byte((uint8_t*)SC_NO_LINE_EEP_ADDR,analogSensorCen);
		eeprom_write_byte((uint8_t*)SD_LINE_EEP_ADDR,analogSensorDer);
		Led3On();
		_delay_ms(50);
		Led3Off();
		Led2On();
		eeprom_write_byte(MODO_EEPADDR,MODO_VALUE_LINEDEF);
	}
	else if (modo == MODO_VALUE_LINEDEF) {
		_delay_ms(2);
		eeprom_write_byte((uint8_t*)SI_NO_LINE_EEP_ADDR,(uint8_t)analogSensorIzq);
		eeprom_write_byte((uint8_t*)SC_LINE_EEP_ADDR,(uint8_t)analogSensorCen);
		eeprom_write_byte((uint8_t*)SD_NO_LINE_EEP_ADDR,(uint8_t)analogSensorDer);
		Led3On();
		_delay_ms(50);
		Led3Off();
		Led1On();

		if ( eeprom_read_byte((uint8_t*)SC_LINE_EEP_ADDR) < eeprom_read_byte((uint8_t*)SC_NO_LINE_EEP_ADDR) ) {
			eeprom_write_byte((uint8_t*)LINEA_EEPADDR,LINEA_BLANCA);
			if ( eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR) > eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR) ) Led3On(); 
			if ( eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR) > eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR) ) Led3On();
		}
		else {
			eeprom_write_byte((uint8_t*)LINEA_EEPADDR,LINEA_NEGRA);
			if ( eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR) < eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR) ) Led3On(); 
			if ( eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR) < eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR) ) Led3On(); 
		}
		eeprom_write_byte((uint8_t*)MODO_EEPADDR,MODO_VALUE_COMPLETE);
	}
	else if (modo != MODO_VALUE_COMPLETE) {
		while(1) {
			Led3On();
			_delay_ms(100);
			Led3Off();
			_delay_ms(100);
		}
	}
	return modo;
}

void calcularNiveles(void) {
	uint8_t maxsi=0, maxsc=0, maxsd=0, minsi=0, minsc=0, minsd=0;
//	uint8_t temp, linea=0, nlinea=0;

	/*
	temp = eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR);
//	eeprom_write_byte((uint8_t*)9,temp);
	linea += temp;
	temp = eeprom_read_byte((uint8_t*)SC_LINE_EEP_ADDR);
//	eeprom_write_byte((uint8_t*)10,temp);
	linea += temp;
	temp = eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR);
//	eeprom_write_byte((uint8_t*)11,temp);
	linea += temp;
	linea = linea/3;

	temp = eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR);
//	eeprom_write_byte((uint8_t*)12,temp);
	nlinea += temp;
	temp = eeprom_read_byte((uint8_t*)SC_NO_LINE_EEP_ADDR);
//	eeprom_write_byte((uint8_t*)13,temp);
	nlinea += temp;
	temp = eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR);
//	eeprom_write_byte((uint8_t*)14,temp);
	nlinea += temp;
	nlinea = nlinea/3;
*/
	
	colorLinea = eeprom_read_byte((uint8_t*)LINEA_EEPADDR);
	// Si el sensor central vale menos que la media, lee blanco, sino negro.	
	if (colorLinea == LINEA_BLANCA) {
		maxsi = eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR);
		maxsc = eeprom_read_byte((uint8_t*)SC_NO_LINE_EEP_ADDR);
		maxsd = eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR);
		minsi = eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR);
		minsc = eeprom_read_byte((uint8_t*)SC_LINE_EEP_ADDR);
		minsd = eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR);
	}
	else {
		minsi = eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR);
		minsc = eeprom_read_byte((uint8_t*)SC_NO_LINE_EEP_ADDR);
		minsd = eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR);
		maxsi = eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR);
		maxsc = eeprom_read_byte((uint8_t*)SC_LINE_EEP_ADDR);
		maxsd = eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR);
	}
	sdNivelMedio = minsd + ((maxsd-minsd)>>1);	
	sdNivelUmbralP = sdNivelMedio + ((maxsd-minsd)>>2);
	sdNivelUmbralN = sdNivelMedio - ((maxsd-minsd)>>2);

//	eeprom_write_byte((uint8_t*)10,(uint8_t)sdNivelUmbralP);
//	eeprom_write_byte((uint8_t*)11,(uint8_t)sdNivelMedio);
//	eeprom_write_byte((uint8_t*)12,(uint8_t)sdNivelUmbralN);

	scNivelMedio = minsc + ((maxsc-minsc)>>1);	
	scNivelUmbralP = scNivelMedio + ((maxsc-minsc)>>2);
	scNivelUmbralN = scNivelMedio - ((maxsc-minsc)>>2);

//	eeprom_write_byte((uint8_t*)13,scNivelUmbralP);
//	eeprom_write_byte((uint8_t*)14,scNivelMedio);
//	eeprom_write_byte((uint8_t*)15,scNivelUmbralN);

	siNivelMedio = minsi + ((maxsi-minsi)>>1);	
	siNivelUmbralP = siNivelMedio + ((maxsi-minsi)>>2);
	siNivelUmbralN = siNivelMedio - ((maxsi-minsi)>>2);

//	eeprom_write_byte((uint8_t*)17,siNivelUmbralP);
//	eeprom_write_byte((uint8_t*)18,siNivelMedio);
//	eeprom_write_byte((uint8_t*)19,siNivelUmbralN);
}
