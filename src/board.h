#ifndef _BOARD_
#define _BOARD_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "definiciones.h"

/* Definiciones de los pines correspondientes a los motores */

/*MD_PWM = Motor Derecho Enable (Enable)*/
#define PORT_MD_PWM_NAME  B
#define MD_PWM_NUMBER     1
/*MI_WPM = Motor Izquierdo PWM (Enable) */
#define PORT_MI_PWM_NAME  B
#define MI_PWM_NUMBER     2

#define PORT_MD_PWM     def_port_reg(PORT_MD_PWM_NAME)
#define PIN_MD_PWM      def_pin_reg(PORT_MD_PWM_NAME)
#define DDR_MD_PWM      def_ddr_reg(PORT_MD_PWM_NAME)

#define PORT_MI_PWM     def_port_reg(PORT_MI_PWM_NAME)
#define PIN_MI_PWM      def_pin_reg(PORT_MI_PWM_NAME)
#define DDR_MI_PWM      def_ddr_reg(PORT_MI_PWM_NAME)


/*MI_IN1 = Motor Left IN1*/
#define PORT_MI_IN1_NAME  D
#define MI_IN1_NUMBER     0
/*MI_IN2 = Motor Left IN2*/
#define PORT_MI_IN2_NAME	 D
#define MI_IN2_NUMBER		 1

/*MD_IN1 = Motor Right IN1*/
#define PORT_MD_IN1_NAME  D
#define MD_IN1_NUMBER     3
/*MD_IN2 = Motor Right IN2*/
#define PORT_MD_IN2_NAME  D
#define MD_IN2_NUMBER     4

#define PORT_MD_IN1     def_port_reg(PORT_MD_IN1_NAME)
#define PIN_MD_IN1      def_pin_reg(PORT_MD_IN1_NAME)
#define DDR_MD_IN1      def_ddr_reg(PORT_MD_IN1_NAME)

#define PORT_MD_IN2     def_port_reg(PORT_MD_IN2_NAME)
#define PIN_MD_IN2      def_pin_reg(PORT_MD_IN2_NAME)
#define DDR_MD_IN2      def_ddr_reg(PORT_MD_IN2_NAME)

#define PORT_MI_IN1     def_port_reg(PORT_MI_IN1_NAME)
#define PIN_MI_IN1      def_pin_reg(PORT_MI_IN1_NAME)
#define DDR_MI_IN1      def_ddr_reg(PORT_MI_IN1_NAME)

#define PORT_MI_IN2     def_port_reg(PORT_MI_IN2_NAME)
#define PIN_MI_IN2      def_pin_reg(PORT_MI_IN2_NAME)
#define DDR_MI_IN2      def_ddr_reg(PORT_MI_IN2_NAME)



#define MAX_MOTOR_F	0x00FF  //revisar si estan bien los valores
#define	MAX_MOTOR_B	0x0000  //revisar si estan bien los valores


#define STOP_MOTOR 0x80  


/* Macros */

/*-----------------------------------------------*/

/* Definiciones de los pines correspondientes a los sensores */

/*S1EM = Sensor 1 Emisor*/
#define PORT_S1EM_NAME C
#define S1EM_NUMBER    3
/*S2EM = Sensor 2 Emisor*/
#define PORT_S2EM_NAME C
#define S2EM_NUMBER    4
/*S3EM = Sensor 3 Emisor*/
#define PORT_S3EM_NAME C
#define S3EM_NUMBER    5

#define PORT_S1EM     def_port_reg(PORT_S1EM_NAME)
#define PIN_S1EM      def_pin_reg(PORT_S1EM_NAME)
#define DDR_S1EM     def_ddr_reg(PORT_S1EM_NAME)

#define PORT_S2EM    def_port_reg(PORT_S2EM_NAME)
#define PIN_S2EM      def_pin_reg(PORT_S2EM_NAME)
#define DDR_S2EM      def_ddr_reg(PORT_S2EM_NAME)

#define PORT_S3EM     def_port_reg(PORT_S3EM_NAME)
#define PIN_S3EM      def_pin_reg(PORT_S3EM_NAME)
#define DDR_S3EM      def_ddr_reg(PORT_S3EM_NAME)

/*S1RE = Sensor 1 Receptor*/
#define PORT_S1RE_NAME C
#define S1RE_NUMBER    0
/*S2RE= Sensor 2 Receptor*/
#define PORT_S2RE_NAME C
#define S2RE_NUMBER    1
/*S3RE = Sensor 3 Receptor*/
#define PORT_S3RE_NAME C
#define S3RE_NUMBER    2

#define PORT_S1RE     def_port_reg(PORT_S1RE_NAME)
#define PIN_S1RE      def_pin_reg(PORT_S1RE_NAME)
#define DDR_S1RE     def_ddr_reg(PORT_S1RE_NAME)

#define PORT_S2RE    def_port_reg(PORT_S2RE_NAME)
#define PIN_S2RE      def_pin_reg(PORT_S2RE_NAME)
#define DDR_S2RE      def_ddr_reg(PORT_S2RE_NAME)

#define PORT_S3RE     def_port_reg(PORT_S3RE_NAME)
#define PIN_S3RE      def_pin_reg(PORT_S3RE_NAME)
#define DDR_S3RE      def_ddr_reg(PORT_S3RE_NAME)

/* Macros */

/* 
//Prende los conversores
SetBit(ADCSRA,ADEN);

// define que los 10 bits de la conversion se alinean a la izquierda
// esto hace que ADCH tenga los 8 bits mas significativos y 
// ADCL tengo los 2 menos significativos en sus bits 7 y 6.
// Si no se setea ADLAR, ADCH tiene los 2 bits mas significativos de la
// conversion y ADCL los 8 menos significativos. (pagina 197)
SetBit(ADMUX,ADLAR);




*/



/* ---------------------------------------------- */

/* Definiciones correspondientes a los pines de los LEDs */

/*LED1 = LED 1 */
#define PORT_LED1_NAME	D
#define LED1_NUMBER	    5

/*LED2 = LED 2 */
#define PORT_LED2_NAME	D
#define LED2_NUMBER	    6

/*LED3 = LED 3 */
#define PORT_LED3_NAME	D
#define LED3_NUMBER	    7

#define PORT_LED1     def_port_reg(PORT_LED1_NAME)
#define PIN_LED1      def_pin_reg(PORT_LED1_NAME)
#define DDR_LED1      def_ddr_reg(PORT_LED1_NAME)

#define PORT_LED2	def_port_reg(PORT_LED2_NAME)
#define PIN_LED2	def_pin_reg(PORT_LED2_NAME)
#define DDR_LED2	def_ddr_reg(PORT_LED2_NAME)

#define PORT_LED3	def_port_reg(PORT_LED3_NAME)
#define PIN_LED3	def_pin_reg(PORT_LED3_NAME)
#define DDR_LED3	def_ddr_reg(PORT_LED3_NAME)

/* Macros */

//Definimos una MACRO que primero toma una comparación entre entre el bit del 
//puerto que contiene el pin sobre el que queremos actuar, y una máscara. 
//Y en base al resultado de esa comparación pone un cero o un uno en el pin.

#define Led1On()    SetBit(PORT_LED1,LED1_NUMBER)
#define Led1Off()   ClearBit(PORT_LED1,LED1_NUMBER)

#define IsLed1On()    IsBitSet(PORT_LED1,LED1_NUMBER)
#define Led1Toggle()  {if ( IsLed1On() ) Led1Off(); else Led1On();}

#define Led2On()    SetBit(PORT_LED2,LED2_NUMBER)
#define Led2Off()   ClearBit(PORT_LED2,LED2_NUMBER)

#define IsLed2On()    IsBitSet(PORT_LED2,LED2_NUMBER)
#define Led2Toggle()  {if ( IsLed2On() ) Led2Off(); else Led2On();}

#define Led3On()    SetBit(PORT_LED3,LED3_NUMBER)
#define Led3Off()   ClearBit(PORT_LED3,LED3_NUMBER)

#define IsLed3On()    IsBitSet(PORT_LED3,LED3_NUMBER)
#define Led3Toggle()  {if ( IsLed3On() ) Led3Off(); else Led3On();}


#define Led1Init()  SetBit(DDR_LED1,LED1_NUMBER)
#define Led2Init()  SetBit(DDR_LED2,LED2_NUMBER)
#define Led3Init()  SetBit(DDR_LED3,LED3_NUMBER)

//#define LedInit(MAC_NUM) SetBit(DDR_LED##MAC_NUM,LED##MAC_NUM_NUMBER)
/* ----------------------------------------------------------------- */

/* Definiciones correspondientes a los pulsadores */

/* INT_ARRANQUE = Pulsador de Arranque */
#define PORT_INT_ARRANQUE_NAME   D
#define INT_ARRANQUE_NUMBER      2

#define PORT_INT_ARRANQUE     def_port_reg(PORT_INT_ARRANQUE_NAME)
#define PIN_INT_ARRANQUE      def_pin_reg(PORT_INT_ARRANQUE_NAME)
#define DDR_INT_ARRANQUE      def_ddr_reg(PORT_INT_ARRANQUE_NAME)

/* Macros */
// Se setea como entrada y se pone el pin en '1'. Esto último hace que se 
// active el pull-up interno
#define IntArranqueInit()  {ClearBit(DDR_INT_ARRANQUE,INT_ARRANQUE_NUMBER);SetBit(PORT_INT_ARRANQUE,INT_ARRANQUE_NUMBER);}

//#define IntArranqueOn()    PIN_INT_ARRANQUE |= (1<<INT_ARRANQUE_NUMBER)

#define IsIntArranqueSet()      IsBitSet(PIN_INT_ARRANQUE,INT_ARRANQUE_NUMBER)
//#define IsIntArranqueClear()    IsBitClear(PIN_INT_ARRANQUE,INT_ARRANQUE_NUMBER)

/* ----------------------------------------------------- */

/* Definiciones correspondientes a los jumpers */
/*JP1 = Jumper 1 */
#define PORT_JMP1_NAME	B
#define JMP1_NUMBER	    6
/*JP2 = Jumper 2 */
#define PORT_JMP2_NAME	B
#define JMP2_NUMBER	    7

#define PORT_JMP1     def_port_reg(PORT_JMP1_NAME)
#define PIN_JMP1      def_pin_reg(PORT_JMP1_NAME)
#define DDR_JMP1      def_ddr_reg(PORT_JMP1_NAME)

#define PORT_JMP2     def_port_reg(PORT_JMP2_NAME)
#define PIN_JMP2      def_pin_reg(PORT_JMP2_NAME)
#define DDR_JMP2      def_ddr_reg(PORT_JMP2_NAME)

/* Macros */

// Se configuran los pines de los jumpers como entrada. Al setear los pines en '1'
// y estando configurados como entradas, se activan los pull-up internos
#define Jumper1Init()  {ClearBit(PORT_JMP1,JMP1_NUMBER);SetBit(PORT_JMP1,JMP1_NUMBER);}
#define Jumper2Init()  {ClearBit(PORT_JMP2,JMP2_NUMBER);SetBit(PORT_JMP2,JMP2_NUMBER);}

#define IsJumper1Set()     IsBitSet(PIN_JMP1,JMP1_NUMBER)
//#define IsJumper1Clear()   IsBitClear(PIN_JMP1,JMP1_NUMBER)
#define IsJumper2Set()     IsBitSet(PIN_JMP1,JMP1_NUMBER)
//#define IsJumper2Clear()   IsBitClear(PIN_JMP1,JMP1_NUMBER)

/* ----------------------------------------------------- */


#endif
