#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
estado_t analizarEstado(void);
void accion(void);
void MuerteSubita();
/* ------------------------ */

volatile estado_t estadoActual;


void testeoDinamica(){
//  Avanzar();
//  _delay_ms(2000);
  GirarDerecha();
  _delay_ms(5000);
  GirarIzquierda();
  _delay_ms(5000);

}


int main (void)
{
	//Inicializaciones
	startup();
	while(estadoActual == APAGADO);

 	while(1) {
    sensores = (PIN_SDRE & PIN_SENSORES_MASK);
    switch(sensores){
      case DESVIO_IZQ:
        GirarDerecha();
        break;
      case DESVIO_DER:
        GirarIzquierda();
        break;
      case LINEA:
        Avanzar();
        break;
      case AMBOSBLANCO:
        Led2On();
        break;
        default:
          MuerteSubita(); //No deberia llegar nunca
      }
	}
}

/* Funciones */
void startup(void)
{
	estadoActual = APAGADO;

	Led1Init();
	Led2Init();
	Led3Init();
	
	Jumper1Init();
	Jumper2Init();
	
	configurarPulsadorArranque();
	configurarMotores();
  configurarSensores();

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
      estadoActual = ON_TRACK;
      motoresEncender();
      Led1On();
    }
    else {
      estadoActual = APAGADO;
      motoresApagar();
      Led1Off();
    }
	}

//  Esto borra el flag por el tema del debounce
  SetBit(EIFR, INTF0);
}

/*
estado_t analizarEstado(void){
  switch(estadoActual){
    case APAGADO:
      return APAGADO;
//      break;
    case ON_TRACK:
      switch(sensores){
        case DESVIO_IZQ:
          return CORREGIR_IZ;
          break;
        case DESVIO_DER:
          return CORREGIR_DE;
          break;
        case LINEA:
          return ON_TRACK;
          break;
        case AMBOSBLANCO:
          Led2On();
          return APAGADO;
          break;
        default:
          MuerteSubita(); //No deberia llegar nunca
          return ON_TRACK;
      }
      break;
    case CORREGIR_DE:
      switch(sensores){
        case DESVIO_IZQ:
          return CORREGIR_IZ;
          break;
        case DESVIO_DER:
          return CORREGIR_DE;
          break;
        case LINEA:
          return ON_TRACK;
          break;
        case AMBOSBLANCO:
          Led2On();
          return APAGADO;
          break;
        default:
          MuerteSubita(); //No deberia llegar nunca
          return ON_TRACK;
      }
      break;
    case CORREGIR_IZ:
      switch(sensores){
        case DESVIO_IZQ:
          return CORREGIR_IZ;
          break;
        case DESVIO_DER:
          return CORREGIR_DE;
          break;
        case LINEA:
          return ON_TRACK;
          break;
        case AMBOSBLANCO:
          Led2On();
          return APAGADO;
          break;
        default:
          MuerteSubita(); //No deberia llegar nunca
          return ON_TRACK;
      }
      break;
    default:
      MuerteSubita(); //No deberia llegar nunca
      return ON_TRACK;
  }
}


void accion(void){   
  switch(estadoActual){
    case APAGADO:
      Detenido();  
      break;
    case ON_TRACK:
      Avanzar();
      break;
    case CORREGIR_IZ:
      GirarDerecha();
      break;
    case CORREGIR_DE:
      GirarIzquierda();
      break;
    case AFUERA_IZ:
      GirarDerecha();
      break;
    case AFUERA_DE:
      GirarIzquierda();
      break;
    default:
      MuerteSubita(); //no debería llegar nunca
      break;
  }
}
*/
void MuerteSubita(){
  cli();
  Led1Off();
  Led2Off();
  Led3Off();
  while(1){
    Led1On();
    _delay_ms(100);
    Led1Off();
    Led2On();
    _delay_ms(100);
    Led2Off();
    Led3On();
    _delay_ms(100);
    Led3Off();
  }
}
