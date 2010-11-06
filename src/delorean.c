#include "delorean.h"

#define NIVEL_MEDIO_SENSORES 	230

/* Definicion de prototipos */
void startup(void);
void set_interrupts(void);
void configurarTimer1(void);
void decidirArranque(void);
void configurarADCs(void);

volatile uint16_t velocidadMD;
volatile uint16_t velocidadMI;
/* ------------------------ */

volatile uint8_t arrancar = 0;
volatile uint8_t flagInt0 = 0;

//si se usan 2 sensores, utilizar solo Izquierda y derecha
char estado = 0;
unsigned char analogSensorIzq = 0;
unsigned char analogSensorCen = 0;
unsigned char analogSensorDer = 0;


int main (void) {
	//Inicializaciones
	startup();
	
	arrancar = 1;
	motorDerechoAvanzar();
	motorIzquierdoAvanzar();
	
	velocidadMD = 380;
	velocidadMI = velocidadMD+15;
	
	
	
	while(1)
	{	
		/*Led1Off(); Led2Off(); Led3Off();	
		_delay_ms(300);
		if(analogSensorIzq > NIVEL_MEDIO_SENSORES) Led1On();
		if(analogSensorCen > NIVEL_MEDIO_SENSORES) Led2On();
		if(analogSensorDer > NIVEL_MEDIO_SENSORES) Led3On();
		_delay_ms(300);*/
		// Si saltó INT0
		//if (flagInt0 == 1) decidirArranque();
	}

}

/* Funciones */

void startup(void) {
	
	IntArranqueInit();

	Led1Init();
	Led2Init();
	Led3Init();
	set_interrupts();

	configurarMotores();
	configurarTimer1();
	configurarADCs();
	sei();
}



void set_interrupts(void){
	GICR |= (1<<INT0); /* Esto habilita la interrupción INT0. */	
	MCUCR |= ((0<<ISC00) | (0<<ISC01)); /* Esto configura INT0 por nivel bajo. */
	//sei();
}


void configurarTimer1(void){
	// Configuracion del timer 1 para el PWM
	
	// Estamos seteando COM1A = 11 , COM1B = 11 y WGM = 8 (para usar un TOP fijo)
	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0);
 	// y el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
	TCCR1B = (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10); 

	ICR1 = MOTORES_TOP_CUENTA;  // Esto define al TOP

	// PWM A   MOTOR DERECHO
	OCR1A = MOTORES_MAX_VEL; //50% cycle

	// PWM B   MOTOR IZQUIERDO
	OCR1B = MOTORES_MAX_VEL; //50% cycle

	//Habilitamos la interrupcion del Timer1 del overflow
	TIMSK = (1<<TOIE1);
}


void decidirArranque(void)
{
	// Esperar mientras el pin permanezca bajo.
	while (IsIntArranqueSet() == 0) Led2On();//TestLeds();
	
	Led1Off(); Led2Off(); Led3Off();
	
	velocidadMD+=5;
	
	if (arrancar == 1)
	{
		// Juego de luces y arrancar!!!
		Led3On();
		_delay_ms(100);
		Led3Off();
		Led2On();
		_delay_ms(100);
		Led2Off();
		Led1On();
		_delay_ms(100);
		Led1Off();

		// Cambiar el estado para que la próxima vez que presionemos el botón se apague.
		arrancar = 0;
		

	}
	else
	{
		// Apagar y cambiar estado para que la próxima vez que presionemos el botón se encienda.
		arrancar = 1;
	}
	
	flagInt0 = 0;  // Apagar el flag de interrupción
	GICR |= (1<<INT0);  // Encendemos INT0.
}
		
/**
	Interrupción del botón de arranque.
**/
ISR(INT0_vect)
{
	// Apagamos INT0 para que no salte mientras mantenemos apretado.
	GICR &= ~(1<<INT0);
	
	flagInt0 = 1;  // Anunciar que la interrupción ocurrió.
	
	// Delay para debounce
	_delay_ms(50);
}

ISR(TIMER1_OVF_vect)
{
	//PWM A RUEDA IZQUIERDA
	OCR1A = velocidadMI;//MOTORES_MAX_VEL; //Cargamos las velocidades en los comparadores del timer

	//PWM A RUEDA DERECHA
	OCR1B = velocidadMD;  //MOTORES_MAX_VEL; //
	return;
}

void configurarADCs(void){
	EncenderADC();
	// Seleccionamos la mayor velocidad de conversion, o sea prescaler 0
	ADCPrescalerSelec(3);
	
	// Alineacion a la izquierda
	AlineacionInit('I');

	//lo utilizamos en el modo single conversion
	//no seteamos free run
	//
	
	//Habilitamos la interrupcion de finalizacion de conversion AD
	SetBit(ADCSRA, ADIE);

	// Inicia la primera conversion
	ADSeleccionarCanalB(0);
	EmisorIzqInit();
	EmisorCenInit();
	EmisorDerInit();
	EmisorIzqOn();
	EmisorCenOn();
	EmisorDerOn();	
	IniciarConversion();
}

ISR(ADC_vect){
	// ver canal en que se termino la conversion
	char temp = ADDeterminarCanalB();
	// guardar en variable correspondiente
	unsigned char temp2 = ADCH;	
	
	switch (temp){
		case 0:
			// AD0 es el sensor derecho
			analogSensorDer = temp2;
			if(analogSensorDer < NIVEL_MEDIO_SENSORES) Led1On();
			else Led1Off();
			// seleccionar siguiente canal
			ADSeleccionarCanalB(1);
			break;
		case 1:
			// AD1 es el sensor cental
			analogSensorCen = temp2;
			if(analogSensorCen < NIVEL_MEDIO_SENSORES) Led2On();
			else Led2Off();
			// seleccionar siguiente canal
			ADSeleccionarCanalB(2);
			break;
		case 2:
			// AD2 es el sensor izquierdo
			analogSensorIzq = temp2;
			if(analogSensorIzq < NIVEL_MEDIO_SENSORES) Led3On();
			else Led3Off();
			// seleccionar siguiente canal
			ADSeleccionarCanalB(0);
			break;
		default:
			// no esperado, se descarta el valor de conversion y se
			// vuelve a arrancar con el sensor derecho
			temp = ADCH;
			ADSeleccionarCanalB(0);
			Led1On();
			break;
	}
	// Volvemos a iniciar la conversion
	IniciarConversion();
}
