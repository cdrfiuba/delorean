#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
void accion(void);
/* ------------------------ */

volatile estado_t estadoActual;
volatile estado_t estadoAnterior;

int main (void) {
	//Inicializaciones
	startup();

	while(estadoActual == APAGADO){
    Led1Toggle();
    _delay_ms(5);
  }

 	while(1) {
    
    while(sensor_est_nuevo == false);
    sensor_est_nuevo = false;

    estadoAnterior = estadoActual;
    switch(sensores){
      case AMBOS_LINEA:
        Avanzar();
        estadoActual = ENLINEA;
        break;
      case IZQ_LINEA:
        if (estadoAnterior==AFUERA_DER) {
          CorreccionDerecha();
        }
        else{
          CorreccionIzquierda();
          estadoActual = DESVIO_DER;
        }
        break;    
      case DER_LINEA:
        if (estadoAnterior==AFUERA_IZQ) {
          CorreccionIzquierda();
        }
        else{
          CorreccionDerecha();
          estadoActual = DESVIO_IZQ;
        }
        break;
      case AMBOS_OUT:
        if ((estadoAnterior==DESVIO_IZQ) || (estadoAnterior==AFUERA_IZQ)) {
          GirarDerecha();
          estadoActual = AFUERA_IZQ;
        }
        else if ((estadoAnterior==DESVIO_DER) || (estadoAnterior==AFUERA_DER)) {
          GirarIzquierda();
          estadoActual = AFUERA_DER;
        }
        else Led2On();
        break;
      default:
        Led3On();
        break;
    }   
	}
}

/* Funciones */
void startup(void){

	Led1Init();
	Led2Init();
	Led3Init();
	
	Jumper1Init();
	Jumper2Init();
	
	configurarPulsadorArranque();
	configurarMotores();
  configurarSensores();

	estadoActual = APAGADO;
	sei();
}


void configurarPulsadorArranque(void){
	IntArranqueInit();
	// Configuracion de modo de interrupcion (pagina 66)
	EICRA |= ((1<<ISC01) | (1<<ISC00)); // Flanco ascendente.

	// Esto habilita la interrupción INT0 escribiendo un '1' en el bit INT0
	// del registro de control de interrupciones externas.
	SetBit(EIMSK, INT0); 
}

ISR(INT0_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);

	if (IsIntArranqueSet()==true)	{ 
    // significa que esta en 1 y hubo flanco ascendente genuino
    // se podria reemplazar la variable por poner apagar todo, poner 
    // el micro a dormir esperando solo esta interrupcion y luego
    // despertalo. Aca se lo despertaria
    if (estadoActual==APAGADO) {
      estadoActual = ENLINEA;
      motoresEncender();
      Led1On();
    }
	}

//  Esto borra el flag por el tema del debounce
  SetBit(EIFR, INTF0);
}
