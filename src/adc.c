#include "adc.h" 

void capturarADc(void){
	//Esta funcion no utiliza interrupciones
	//verificar que en configurar ADC este
	// ClearBit(ADCSRA, ADIE);
	// 

	ADSeleccionarCanal(0);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorDer	= ADCH;

	ADSeleccionarCanal(1);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);	
	analogSensorCen	= ADCH;

	ADSeleccionarCanal(2);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorIzq	= ADCH;
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
	
	//Habilitar o no  la interrupcion de finalizacion de conversion AD
	// SetBit(ADCSRA, ADIE);
	ClearBit(ADCSRA, ADIE);

	// Inicia la primera conversion
	EmisorIzqInit();
	EmisorCenInit();
	EmisorDerInit();
	EmisorIzqOn();
	EmisorCenOn();
	EmisorDerOn();	
	analogSensorDer = 0;
	analogSensorCen = 0;
	analogSensorDer	= 0;
}

ISR(ADC_vect){
	// ver canal en que se termino la conversion
	char temp = ADDeterminarCanal();
	// guardar en variable correspondiente
	unsigned char temp2 = ADCH;	
	
	switch (temp){
		case 0:
			// AD0 es el sensor derecho
			analogSensorDer = temp2;
			if(analogSensorDer < NIVEL_MEDIO_SENSORES) Led1On();
			else Led1Off();
			// seleccionar siguiente canal
			ADSeleccionarCanal(1);
			break;
		case 1:
			// AD1 es el sensor cental
			analogSensorCen = temp2;
			if(analogSensorCen < NIVEL_MEDIO_SENSORES) Led2On();
			else Led2Off();
			// seleccionar siguiente canal
			ADSeleccionarCanal(2);
			break;
		case 2:
			// AD2 es el sensor izquierdo
			analogSensorIzq = temp2;
			if(analogSensorIzq < NIVEL_MEDIO_SENSORES) Led3On();
			else Led3Off();
			// seleccionar siguiente canal
			ADSeleccionarCanal(0);
			break;
		default:
			// no esperado, se descarta el valor de conversion y se
			// vuelve a arrancar con el sensor derecho
			temp = ADCH;
			ADSeleccionarCanal(0);
			Led1On();
			break;
	}
	// Volvemos a iniciar la conversion
	IniciarConversion();
}
