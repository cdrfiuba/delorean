#include "sensores.h"

volatile bool sensor_est_nuevo;
volatile sensor_t sensores;

/* Funcionamiento con "Pin Change" */
void configurarSensores(){
  EmisorDerInit();
  EmisorIzqInit();

  EmisorIzqOn();
  EmisorDerOn();

  PCICR = (1<<PCIE1); //Habilita interrupcion de pin change
  PCMSK1 = (1<<PCINT9) | (1<<PCINT8); //Indica que solo estos dos pines disparan la interrupcion
  sensor_est_nuevo = false;
  sensores = LINEA;
}

ISR(PCINT1_vect,ISR_NAKED){ //,ISR_NAKED
  sensores = (PIN_SDRE & PIN_SENSORES_MASK);
/*  Led3Off();
  Led2Off();
  switch(sensores){
    case DESVIO_IZQ:
      Led3On();
      Led2Off();
      break;
    case DESVIO_DER:
      Led2On();
      Led3Off();
      break;
    case LINEA:
      Led2On();
      Led3On();
      break;
    case AFUERA:
      Led3Off();
      Led2Off();
      break;
    default:
      Led1Off();
      break;
  }
*/
  sensor_est_nuevo = true;
  Reti();
}

