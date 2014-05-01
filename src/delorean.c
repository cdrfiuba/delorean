#include "delorean.h"

/* Definicion de prototipos */
void startup(void);
void configurarPulsadorArranque(void);
void accion(void);
/* ------------------------ */


#define DELAY 20

int main (void) {
	//Inicializaciones
	startup();

  LedAOff();
  LedBOff();
  LedCOff();

  while(1) {
    ClearBit(PIN_MD_IN1,MD_IN1_NUMBER);
    ClearBit(PIN_MD_IN2,MD_IN2_NUMBER);
    
    _delay_ms(DELAY);

    SetBit(PIN_MD_IN1,MD_IN1_NUMBER);
    ClearBit(PIN_MD_IN2,MD_IN2_NUMBER);

    _delay_ms(DELAY);

    ClearBit(PIN_MI_IN1,MI_IN1_NUMBER);
    ClearBit(PIN_MI_IN2,MI_IN2_NUMBER);

    _delay_ms(DELAY);

    SetBit(PIN_MI_IN1,MI_IN1_NUMBER);
    ClearBit(PIN_MI_IN2,MI_IN2_NUMBER);

    _delay_ms(DELAY);

    ClearBit(PIN_MD_IN1,MD_IN1_NUMBER);
    ClearBit(PIN_MD_IN2,MD_IN2_NUMBER);

    _delay_ms(DELAY);

    ClearBit(PIN_MD_IN1,MD_IN1_NUMBER);
    SetBit(PIN_MD_IN2,MD_IN2_NUMBER);

    _delay_ms(DELAY);

    ClearBit(PIN_MI_IN1,MI_IN1_NUMBER);
    ClearBit(PIN_MI_IN2,MI_IN2_NUMBER);

    _delay_ms(DELAY);

    ClearBit(PIN_MI_IN1,MI_IN1_NUMBER);
    SetBit(PIN_MI_IN2,MI_IN2_NUMBER);

    _delay_ms(DELAY);

  }
}

/* Funciones */
void startup(void){

	LedAInit();
	LedBInit();
	LedCInit();
	
	configurarPulsadorArranque();
	configurarMotores();
  motoresEncender();

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
      LedAToggle();
	}

//  Esto borra el flag por el tema del debounce
  SetBit(EIFR, INTF0);
}
