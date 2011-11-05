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
}

ISR(PCINT1_vect){
  //sensores = PIN_SDRE & 0x03;

   if(IsBitSet(PIN_SIRE, SIRE_NUMBER)){
     Led3On();
     Led2Off();
   }
   else{
     Led3Off();
     Led2On();
   }

  sensor_est_nuevo = true;
}

