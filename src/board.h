#ifndef _BOARD_
#define _BOARD_
#include <avr/io.h>
#include <avr/interrupt.h>

/* Defines y Macros de proposito general, deberían ir en otro archivo */

#define bool	_Bool
#define true	  1
#define false   0
#define OK		true
#define ERROR	false
#define Nop()	asm volatile("nop")

#define LOW(a)		(char)(a & 0x00ff)
#define	HIGH(a)		(char)(a >> 8)

#define SetBit(Byte,Bit)	 (Byte |= (1<<Bit))
#define	ClearBit(Byte,Bit)	 (Byte &= (~(1<<Bit)))
#define IsBitSet(Byte,Bit)	 ( (Byte & (1<<Bit)) ? true : false )
//#define IsBitClear(Byte,Bit) ( (Byte & (1<<Bit)) ? false : true )
// En general no hace falta preguntar IsBitClear(), ya que se puede saber a 
// partir de IsBitSet() = false


#define concat(a,b)             a ## b
#define def_port_reg(name)      concat(PORT,name)
#define def_pin_reg(name)       concat(PIN,name)
#define def_ddr_reg(name)       concat(DDR,name)

/* ----------------------------------------------------------*/


/* Definiciones de los pines correspondientes a los motores */

/*MLWPM = Motor Left PWM (Enable) */
#define PORT_MRPWM_NAME  B
#define MRPWM_NUMBER     1
/*MRPWM = Motor Right Enable (Enable)*/
#define PORT_MLPWM_NAME  B
#define MLPWM_NUMBER     2

#define PORT_MRPWM     def_port_reg(PORT_MRPWM_NAME)
#define PIN_MRPWM      def_pin_reg(PORT_MRPWM_NAME)
#define DDR_MRPWM      def_ddr_reg(PORT_MRPWM_NAME)

#define PORT_MLPWM     def_port_reg(PORT_MLPWM_NAME)
#define PIN_MLPWM      def_pin_reg(PORT_MLPWM_NAME)
#define DDR_MLPWM      def_ddr_reg(PORT_MLPWM_NAME)


/*MLIN1 = Motor Left IN1*/
#define PORT_MLIN1_NAME  D
#define MLIN1_NUMBER     0

/*MLIN2 = Motor Left IN2*/
#define PORT_MLIN2_NAME	 D
#define MLIN2_NUMBER		 1

/*MRIN1 = Motor Right IN1*/
#define PORT_MRIN1_NAME  D
#define MRIN1_NUMBER     3
/*MRIN2 = Motor Right IN2*/
#define PORT_MRIN2_NAME  D
#define MRIN2_NUMBER     4

#define PORT_MRIN1     def_port_reg(PORT_MRIN1_NAME)
#define PIN_MRIN1      def_pin_reg(PORT_MRIN1_NAME)
#define DDR_MRIN1      def_ddr_reg(PORT_MRIN1_NAME)

#define PORT_MRIN2     def_port_reg(PORT_MRIN2_NAME)
#define PIN_MRIN2      def_pin_reg(PORT_MRIN2_NAME)
#define DDR_MRIN2      def_ddr_reg(PORT_MRIN2_NAME)

#define PORT_MLIN1     def_port_reg(PORT_MLIN1_NAME)
#define PIN_MLIN1      def_pin_reg(PORT_MLIN1_NAME)
#define DDR_MLIN1      def_ddr_reg(PORT_MLIN1_NAME)

#define PORT_MLIN2     def_port_reg(PORT_MLIN2_NAME)
#define PIN_MLIN2      def_pin_reg(PORT_MLIN2_NAME)
#define DDR_MLIN2      def_ddr_reg(PORT_MLIN2_NAME)

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
#define Led1Init()  SetBit(DDR_LED1,LED1_NUMBER)

#define IsLed1On()    IsBitSet(PORT_LED1,LED1_NUMBER)
#define Led1Toggle()  {if ( IsLed1On() ) Led1Off(); else Led1On();}

#define Led2On()    SetBit(PORT_LED2,LED2_NUMBER)
#define Led2Off()   ClearBit(PORT_LED2,LED2_NUMBER)
#define Led2Init()  SetBit(DDR_LED2,LED2_NUMBER)

#define IsLed2On()    IsBitSet(PORT_LED2,LED2_NUMBER)
#define Led2Toggle()  {if ( IsLed2On() ) Led2Off(); else Led2On();}

#define Led3On()    SetBit(PORT_LED3,LED3_NUMBER)
#define Led3Off()   ClearBit(PORT_LED3,LED3_NUMBER)
#define Led3Init()  SetBit(DDR_LED3,LED3_NUMBER)

#define IsLed3On()    IsBitSet(PORT_LED3,LED3_NUMBER)
#define Led3Toggle()  {if ( IsLed3On() ) Led3Off(); else Led3On();}

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
