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
  sensores = (PIN_SDRE & PIN_SENSORES_MASK);

}


ISR(PCINT1_vect){ //,ISR_NAKED
  sensores = (PIN_SDRE & PIN_SENSORES_MASK);
  sensor_est_nuevo = true;
//  Reti();
}

