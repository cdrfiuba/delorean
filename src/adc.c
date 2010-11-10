#include "adc.h" 
#include <util/delay.h>


/*bool  getSensor (unsigned char analogSensor)
{
	if (analogSensor > NIVEL_MEDIO_SENSORES) return false;
	if (analogSensor < NIVEL_MEDIO_SENSORES) return true;
	return false;
}*/

/*bool  getSensor (unsigned char analogSensor, bool s)
{
	if (analogSensor > NIVEL_MEDIO_SENSORES) return false;
	if (analogSensor < NIVEL_MEDIO_SENSORES) return true;
	return false;
}*/

/**
	Retorna 1 si está sobre la línea y 0 si no lo esta
**/
bool getSensor(uint8_t analogSensor, bool s)
{
	uint8_t media = (minNivelSensor + maxNivelSensor) / 2;
	bool v = s;
	
	uint8_t umbral = (maxNivelSensor - minNivelSensor)/4;
	
	if (analogSensor < (media-umbral)) v = colorLinea;
	if (analogSensor > (media+umbral)) v = !colorLinea;
	
	return v;
}

estado_sensor_t analizarSensores(void) {
   // 0------88------168------255
   // | bajo |  medio  |  alto  |
	bool si, sm, sd;

	si = getSensor(analogSensorIzq, estadoSensores & ES_100);
	sm = getSensor(analogSensorCen, estadoSensores & ES_010);
	sd = getSensor(analogSensorDer, estadoSensores & ES_001);

	if (si) Led1On(); else Led1Off();
	if (sm) Led2On(); else Led2Off();
	if (sd) Led3On(); else Led3Off();
	
	if (!si && !sm && !sd) return ES_000;
	if ( si && !sm && !sd) return ES_100;
	if (!si &&  sm && !sd) return ES_010;
	if (!si && !sm &&  sd) return ES_001;
	if ( si &&  sm && !sd) return ES_110;
	if (!si &&  sm &&  sd) return ES_011;
	return ES_000;
}

void capturarADc(void){
	//Esta funcion no utiliza interrupciones
	//verificar que no este el define _ADC_MODO_INT_ en adc.h

	ADSeleccionarCanal(ADC_NUM_SDRE);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorDer	= ADCH;

	ADSeleccionarCanal(ADC_NUM_SCRE);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);	
	analogSensorCen	= ADCH;

	ADSeleccionarCanal(ADC_NUM_SIRE);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorIzq	= ADCH;
}


void capturarADcPRO(void){
	//Esta funcion no utiliza interrupciones
	//verificar que no este el define _ADC_MODO_INT_ en adc.h
	EmisorDerOn();
	ADSeleccionarCanal(ADC_NUM_SDRE);
	//se debería utilizar un timer o algo
	_delay_us(300);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorDer	= ADCH;
	EmisorDerOff();

	EmisorCenOn();
	ADSeleccionarCanal(ADC_NUM_SCRE);
	_delay_us(300);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);	
	analogSensorCen	= ADCH;
	EmisorCenOff();

	EmisorIzqOn();
	ADSeleccionarCanal(ADC_NUM_SIRE);
	_delay_us(300);
	IniciarConversion();
	while (IsBitSet(ADCSRA,ADIF)==false);
	SetBit(ADCSRA,ADIF);
	analogSensorIzq	= ADCH;
	EmisorIzqOff();
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

volatile bool medicionValida;


// se tuvo que hacer dos mediciones por sensor, ya que el tiempo de respuesta
// entre que el Emisor se enciende, y el receptor detecta algo, es mayor
// que el mayor tiempo de muestreo posible
// para utilizar interrupciones, definir la etiqueta _ADC_MODO_INT_
ISR(ADC_vect){
	// ver canal en que se termino la conversion
	char temp = ADDeterminarCanal();
	// guardar en variable correspondiente
	unsigned char temp2 = ADCH;	
	
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
void calibrarNiveles()
{
	uint16_t s1=0, s2=0, s3=0;
	uint8_t i;
	
	for (i=0; i<20; i++)
	{
		capturarADc();
		//capturarADcPRO();
		
		s1 += analogSensorIzq;
		s2 += analogSensorCen;
		s3 += analogSensorDer;
	}
	s1 = s1 / 20;
	s2 = s2 / 20;
	s3 = s3 / 20;
	s1 = (s1 + s3) / 2;

	// Si el sensor central vale menos que la media, lee blanco, sino negro.	
	if (s2 < (s1 + s2) / 2)
	{
		maxNivelSensor = s1;
		minNivelSensor = s2;
		colorLinea = 1;
	}
	else
	{
		colorLinea = 0;
		maxNivelSensor = s2;
		minNivelSensor = s1;
	}
}
