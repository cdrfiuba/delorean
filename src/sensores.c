#include "sensores.h"

volatile bool sensor_est_nuevo;
volatile sensor_t sensores;

/* Funcionamiento con "Pin Change" */
void configurarSensores(){
  PCICR = (1<<PCIE1);
  PCMSK1 = (1<<PCINT9) | (1<<PCINT8);
  sensor_est_nuevo = false;
}

ISR(PCINT1_vect){
  sensores = PIN_SDRE & 0x03;
  sensor_est_nuevo = true;
}

