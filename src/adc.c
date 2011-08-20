#include "adc.h" 
#include <util/delay.h>

volatile bool medicionValida;

/**
  
**/
uint8_t analizarSensores(void)
{
	uint8_t si=0, sd=0;

	if (colorLinea == LINEA_NEGRA)
	{
		if (analogSensorIzq > siNivelUmbralP) si = 3;
		else if (analogSensorIzq > siNivelMedio) si = 2;
		else if (analogSensorIzq > siNivelUmbralN) si = 1;
		else si = 0;

		if (analogSensorDer > sdNivelUmbralP) sd = 3;
		else if (analogSensorDer > sdNivelMedio) sd = 2;
		else if (analogSensorDer > sdNivelUmbralN) sd = 1;
		else sd = 0;
	}
	else if (colorLinea == LINEA_BLANCA)
	{
		if (analogSensorIzq > siNivelUmbralP) si = 0;
		else if (analogSensorIzq > siNivelMedio) si = 1;
		else if (analogSensorIzq > siNivelUmbralN) si = 2;
		else si = 3;
		
		if (analogSensorDer > sdNivelUmbralP) sd = 0;
		else if (analogSensorDer > sdNivelMedio) sd = 1;
		else if (analogSensorDer > sdNivelUmbralN) sd = 2;
		else sd = 3;
	}
	return ( (si<<2) | (sd<<0) );
//	return ( (si<<4) | (sc<<2) | (sd<<0) );
}

void configurarADCs(void)
{
	EmisorIzqInit();
	EmisorDerInit();

	analogSensorIzq = 0;
	analogSensorDer = 0;
	
	EncenderADC();

	// Alineamos a la izquierda los 10 bits de la conversion,
    // y nos quedamos solo con los 8bits del byte alto [ADCH] (pagina 208)
    SetBit(ADMUX, ADLAR);

	//lo utilizamos en el modo single conversion
	//no seteamos free run
	
#ifdef _ADC_MODO_INT_
	// Modo con interrupcion
	// Seleccionamos la menor velocidad de muestreo. CK/128
	ADCPrescalerSelec(7);
	
	// Habilitar o no  la interrupcion de finalizacion de conversion AD
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
	EmisorDerOn();	
#endif
}



// se tuvo que hacer dos mediciones por sensor, ya que el tiempo de respuesta
// entre que el Emisor se enciende, y el receptor detecta algo, es mayor
// que el mayor tiempo de muestreo posible
// para utilizar interrupciones, definir la etiqueta _ADC_MODO_INT_
ISR(ADC_vect)
{
	// ver canal en que se termino la conversion
	char temp = ADDeterminarCanal();
	// guardar en variable correspondiente
	uint8_t temp2 = ADCH;	
	
	switch (temp)
	{
		case ADC_NUM_SDRE:
			if (medicionValida==true)
			{
				// AD0 es el sensor derecho
				analogSensorDer = temp2;
				// seleccionar siguiente canal
				ADSeleccionarCanal(ADC_NUM_SCRE);
				medicionValida = false;
				IniciarConversion();
			}
			else
			{
				IniciarConversion();
				medicionValida = true;
			}
			break;
		case ADC_NUM_SCRE:
			if (medicionValida==true)
			{
				// AD1 es el sensor cental
				// analogSensorCen = temp2;  // ya no hay sensor central
				// seleccionar siguiente canal
				ADSeleccionarCanal(ADC_NUM_SIRE);
				medicionValida = false;
				IniciarConversion();
			}
			else
			{
				IniciarConversion();
				medicionValida = true;
			}
			break;
		case ADC_NUM_SIRE:
			if (medicionValida==true)
			{
				// AD2 es el sensor izquierdo
				analogSensorIzq = temp2;
				// seleccionar siguiente canal
				ADSeleccionarCanal(ADC_NUM_SDRE);
				medicionValida = false;
				IniciarConversion();
			}
			else
			{
				IniciarConversion();
				medicionValida = true;
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
void calibrarNiveles(void)
{
	// Guardar valores de nivel para la LINEA
    Led3On();
	_delay_ms(50);
	eeprom_write_byte((uint8_t*)SI_LINE_EEP_ADDR,analogSensorIzq);
	eeprom_write_byte((uint8_t*)SD_LINE_EEP_ADDR,analogSensorDer);
	_delay_ms(50);
	Led3Off();
    
    while(!leerBoton1());  // esperar el que aprete el botón para pasar a la próxima fase
    
    // Guardar valores de nivel para NO_LINEA
	Led2On();
	_delay_ms(50);
	eeprom_write_byte((uint8_t*)SI_NO_LINE_EEP_ADDR,(uint8_t)analogSensorIzq);
	eeprom_write_byte((uint8_t*)SD_NO_LINE_EEP_ADDR,(uint8_t)analogSensorDer);
	_delay_ms(50);
	Led2Off();
}

/*
  calcularNiveles(void)
  Calcula las estadísticas para cada sensor.
*/
void calcularNiveles(void)
{
	uint16_t maxsi=0, maxsd=0, minsi=0, minsd=0, linea=0, nlinea=0;
	uint8_t temp;

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

	
//	eeprom_write_byte((uint8_t*)16,(uint8_t)linea);
//	eeprom_write_byte((uint8_t*)17,(uint8_t)nlinea);
	// Si el sensor central vale menos que la media, lee blanco, sino negro.	
	if (nlinea > linea)
	{
		colorLinea = LINEA_BLANCA;
		maxsi = eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR);
		maxsd = eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR);
		minsi = eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR);
		minsd = eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR);
	}
	else
	{
		colorLinea = LINEA_NEGRA;
		minsi = eeprom_read_byte((uint8_t*)SI_NO_LINE_EEP_ADDR);
		minsd = eeprom_read_byte((uint8_t*)SD_NO_LINE_EEP_ADDR);
		maxsi = eeprom_read_byte((uint8_t*)SI_LINE_EEP_ADDR);
		maxsd = eeprom_read_byte((uint8_t*)SD_LINE_EEP_ADDR);
	}
	sdNivelMedio = minsd + (maxsd-minsd)/2;	
	sdNivelUmbralP = sdNivelMedio + (maxsd-minsd)/S_UMBRAL_CTE;
	sdNivelUmbralN = sdNivelMedio - (maxsd-minsd)/S_UMBRAL_CTE;

	eeprom_write_byte((uint8_t*)10,(uint8_t)sdNivelUmbralP);
	eeprom_write_byte((uint8_t*)11,(uint8_t)sdNivelMedio);
	eeprom_write_byte((uint8_t*)12,(uint8_t)sdNivelUmbralN);

	siNivelMedio = minsi + (maxsi-minsi)/2;	
	siNivelUmbralP = siNivelMedio + (maxsi-minsi)/S_UMBRAL_CTE;
	siNivelUmbralN = siNivelMedio - (maxsi-minsi)/S_UMBRAL_CTE;

	eeprom_write_byte((uint8_t*)17,(uint8_t)siNivelUmbralP);
	eeprom_write_byte((uint8_t*)18,(uint8_t)siNivelMedio);
	eeprom_write_byte((uint8_t*)19,(uint8_t)siNivelUmbralN);
}

