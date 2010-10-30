#ifndef _BOARD_
#define _BOARD_
#include <avr/io.h>
#include <avr/interrupt.h>

#define true	1
#define	false	0

#define concat(a,b)             a ## b
#define def_port_reg(name)      concat(PORT,name)
#define def_pin_reg(name)       concat(PIN,name)
#define def_ddr_reg(name)       concat(DDR,name)


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

#define Led1On()    PORT_LED1 |= (1<<LED1_NUMBER)
#define Led1Off()   PORT_LED1 &= ~(1<<LED1_NUMBER)
#define Led1Init()  DDR_LED1 |= (1<<LED1_NUMBER)

#define IsLed1On()    ( (PORT_LED1 & (1<<LED1_NUMBER)) == (1<<LED1_NUMBER) )
#define Led1Toggle()  {if ( IsLed1On() ) Led1Off(); else Led1On();}

#define Led2On()    PORT_LED2 |= (1<<LED2_NUMBER)
#define Led2Off()   PORT_LED2 &= ~(1<<LED2_NUMBER)
#define Led2Init()  DDR_LED2 |= (1<<LED2_NUMBER)

#define IsLed2On()    ( (PORT_LED2 & (1<<LED2_NUMBER)) == (1<<LED2_NUMBER) )
#define Led2Toggle()  {if ( IsLed2On() ) Led2Off(); else Led2On();}

#define Led3On()    PORT_LED3 |= (1<<LED3_NUMBER)
#define Led3Off()   PORT_LED3 &= ~(1<<LED3_NUMBER)
#define Led3Init()  DDR_LED3 |= (1<<LED3_NUMBER)

#define IsLed3On()    ( (PORT_LED3 & (1<<LED3_NUMBER)) == (1<<LED3_NUMBER) )
#define Led3Toggle()  {if ( IsLed3On() ) Led3Off(); else Led3On();}

#define IntArranqueInit()  DDR_INT_ARRANQUE &= ~(1<<INT_ARRANQUE_NUMBER)
#define IntArranqueOn()    PIN_INT_ARRANQUE |= (1<<INT_ARRANQUE_NUMBER)
/* ----------------------------------------------------------------- */

/* Definiciones correspondientes a los pulsadores */

/* INT_ARRANQUE = Pulsador de Arranque */
#define PORT_INT_ARRANQUE_NAME   D
#define INT_ARRANQUE_NUMBER      2

#define PORT_INT_ARRANQUE     def_port_reg(PORT_INT_ARRANQUE_NAME)
#define PIN_INT_ARRANQUE      def_pin_reg(PORT_INT_ARRANQUE_NAME)
#define DDR_INT_ARRANQUE      def_ddr_reg(PORT_INT_ARRANQUE_NAME)




/* Macros */

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

/* ----------------------------------------------------- */


#endif
