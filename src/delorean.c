#include "delorean.h"

/* Definicion de prototipos */
void startup(void);

/* ------------------------ */

int main (void) {
	//Inicializaciones
	startup();

	while(1){
		TestLeds();
	}

}


void startup(void) {
				Led1Init();
				Led2Init();
				Led3Init();
}
