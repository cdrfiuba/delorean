#include "boxes.h"

void TestLeds(void){
	while(1){
		Led1On();
		_delay_ms(200);
		Led2On();
		_delay_ms(200);
		Led3On();
		_delay_ms(200);
		Led1Off();
		_delay_ms(200);
		Led2Off();
		_delay_ms(200);
		Led3Off();
		_delay_ms(200);
	}
}


