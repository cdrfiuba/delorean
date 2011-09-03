#include "adc.h" 
#include <util/delay.h>

volatile bool medicionValida;

/**
	
**/
uint8_t analizarSensores(void)
{
	uint8_t si=0, sd=0;
	if (analogSensorIzq > siNivelUmbralP) si = 0;
	else if (analogSensorIzq > siNivelUmbralN) si = 1;
	else si = 2;
	
	if (analogSensorDer > sdNivelUmbralP) sd = 0;
	else if (analogSensorDer > sdNivelUmbralN) sd = 1;
	else sd = 2;

	return ( (si<<2) | (sd<<0) );
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

void capturarADc(void) {
	//Esta funcion no utiliza interrupciones
	//verificar que no este el define _ADC_MODO_INT_ en adc.h
	ADSeleccionarCanal(ADC_NUM_SDRE);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
//	SetBit(ADCSRA,ADIF);
	analogSensorDer = ADCH;

	ADSeleccionarCanal(ADC_NUM_SIRE);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorIzq = ADCH;
}
