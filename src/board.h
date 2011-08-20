#ifndef _BOARD_
#define _BOARD_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "definiciones.h"

/* Definiciones de los pines correspondientes a los motores */

/*MD_PWM = Motor Derecho Enable (Enable)*/
#define PORT_MD_EN_NAME  B
#define MD_EN_NUMBER     1
/*MI_WPM = Motor Izquierdo PWM (Enable) 
*/
#define PORT_MI_EN_NAME  B
#define MI_EN_NUMBER     2

#define PORT_MD_EN     def_port_reg(PORT_MD_EN_NAME)
#define PIN_MD_EN      def_pin_reg(PORT_MD_EN_NAME)
#define DDR_MD_EN      def_ddr_reg(PORT_MD_EN_NAME)

#define PORT_MI_EN     def_port_reg(PORT_MI_EN_NAME)
#define PIN_MI_EN      def_pin_reg(PORT_MI_EN_NAME)
#define DDR_MI_EN      def_ddr_reg(PORT_MI_EN_NAME)


/*MI_IN1 = Motor Left IN1*/
#define PORT_MI_IN1_NAME  D
#define MI_IN1_NUMBER     3
/*MI_IN2 = Motor Left IN2*/
#define PORT_MI_IN2_NAME	 D
#define MI_IN2_NUMBER		 4

/*MD_IN1 = Motor Right IN1*/
#define PORT_MD_IN1_NAME  D
#define MD_IN1_NUMBER     0
/*MD_IN2 = Motor Right IN2*/
#define PORT_MD_IN2_NAME  D
#define MD_IN2_NUMBER     1

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



//#define MAX_MOTOR_F	0x00FF  //revisar si estan bien los valores
//#define	MAX_MOTOR_B	0x0000  //revisar si estan bien los valores


//#define STOP_MOTOR 0x80  


/* Macros */

/*-----------------------------------------------*/

/* Definiciones de los pines correspondientes a los sensores */

/*SIEM = Sensor Izquierdo Emisor*/
#define PORT_SIEM_NAME C
#define SIEM_NUMBER    4
/*SDEM = Sensor Derecho Emisor*/
#define PORT_SDEM_NAME C
#define SDEM_NUMBER    3

#define PORT_SIEM     def_port_reg(PORT_SIEM_NAME)
#define PIN_SIEM      def_pin_reg(PORT_SIEM_NAME)
#define DDR_SIEM     def_ddr_reg(PORT_SIEM_NAME)

#define PORT_SCEM    def_port_reg(PORT_SCEM_NAME)
#define PIN_SCEM      def_pin_reg(PORT_SCEM_NAME)
#define DDR_SCEM      def_ddr_reg(PORT_SCEM_NAME)

#define PORT_SDEM     def_port_reg(PORT_SDEM_NAME)
#define PIN_SDEM      def_pin_reg(PORT_SDEM_NAME)
#define DDR_SDEM      def_ddr_reg(PORT_SDEM_NAME)

/*SDRE = Sensor Derecho Receptor*/
#define PORT_SDRE_NAME C
#define SDRE_NUMBER    0
#define ADC_NUM_SDRE	 0

#define ADC_NUM_SCRE	 1 //No se usa porque ya no hay sensor central

/*SIRE = Sensor Izquierdo Receptor*/
#define PORT_SIRE_NAME C
#define SIRE_NUMBER    1
#define ADC_NUM_SIRE	 2

#define PORT_SDRE     def_port_reg(PORT_SDRE_NAME)
#define PIN_SDRE      def_pin_reg(PORT_SDRE_NAME)
#define DDR_SDRE     def_ddr_reg(PORT_SDRE_NAME)

#define PORT_SCRE    def_port_reg(PORT_SCRE_NAME)
#define PIN_SCRE      def_pin_reg(PORT_SCRE_NAME)
#define DDR_SCRE      def_ddr_reg(PORT_SCRE_NAME)

#define PORT_SIRE     def_port_reg(PORT_SIRE_NAME)
#define PIN_SIRE      def_pin_reg(PORT_SIRE_NAME)
#define DDR_SIRE      def_ddr_reg(PORT_SIRE_NAME)

/* Macros */

#define EmisorIzqOn()    ClearBit(PORT_SIEM, SIEM_NUMBER)
#define EmisorIzqOff()   SetBit(PORT_SIEM, SIEM_NUMBER)

#define EmisorDerOn()    ClearBit(PORT_SDEM, SDEM_NUMBER)
#define EmisorDerOff()   SetBit(PORT_SDEM, SDEM_NUMBER)

#define EmisorDerInit()    SetBit(DDR_SDEM, SDEM_NUMBER)
#define EmisorIzqInit()    SetBit(DDR_SIEM, SIEM_NUMBER)

/*Configuracion ADC*/

// Para elegir la referencia se usan los bits REFS1 y REFS0. Pero como 
// por default vienen en cero y ese es el modo AREF (que vamos a usar),
// no hacemos nada con ellos.

// Prende los conversores seteando bit en el ADCSRA
#define EncenderADC() SetBit(ADCSRA, ADEN)

// Clearemos el bit ADPS para NO tener el prescaler del clock activo (pag 198)
#define ADCPrescalerSelec(PN) (ADCSRA = (ADCSRA & 0xF8) | PN)


// Modo de funcionamiento (pag 198)

// Modo Single Conversion: Para empezar la conversion se debe poner en alto 
// el bit ADSC (ADC Start Conversion) en el Reg: ADCSRA
// Modo Free Runing: En este modo el ADC toma datos todo el tiempo, 
// se debe setear el bit ADFR en el Reg: ADCSRA
// Cuando una conversion termina, se escribe en el ADC Register, y se pone 
// en alto el bit ADIF. Si se trabaja en Single Conversion, el bit ADSC se
// clarea automaticamente.

#define IniciarConversion()      SetBit(ADCSRA, ADSC)

// La siguiente funcion setea los 4 bits menos significativos del registro
// ADMUX. Con esos bits se selecciona el canal de muestreo (NUM va de 0 a 7).
// ATENCION! Utilizar estafuncion con NUM > 7 puede ocasionar 
// malfuncionamiento de los AD
// ANALIZAR LA DIFERENCIA ENTRE MACRO y static inline function

#define ADSeleccionarCanal(CN) 			(ADMUX = (ADMUX & 0xF0) | CN)

#define ADDeterminarCanal()					(ADMUX & 0x07)
/* ---------------------------------------------- */

/* Definiciones correspondientes a los pines de los LEDs */

/*LED1 = LED 1 (Verde)*/
#define PORT_LED1_NAME	D
#define LED1_NUMBER	    5

/*LED2 = LED 2 (Amarillo)*/
#define PORT_LED2_NAME	D
#define LED2_NUMBER	    6

/*LED3 = LED 3 (Rojo)*/
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

#define Led1On()    SetBit(PORT_LED1, LED1_NUMBER)
#define Led1Off()   ClearBit(PORT_LED1, LED1_NUMBER)

#define IsLed1On()    IsBitSet(PORT_LED1, LED1_NUMBER)
#define Led1Toggle()  {if ( IsLed1On() ) Led1O4ff(); else Led1On();}

#define Led2On()    SetBit(PORT_LED2, LED2_NUMBER)
#define Led2Off()   ClearBit(PORT_LED2, LED2_NUMBER)

#define IsLed2On()    IsBitSet(PORT_LED2, LED2_NUMBER)
#define Led2Toggle()  {if ( IsLed2On() ) Led2Off(); else Led2On();}

#define Led3On()    SetBit(PORT_LED3, LED3_NUMBER)
#define Led3Off()   ClearBit(PORT_LED3, LED3_NUMBER)

#define IsLed3On()    IsBitSet(PORT_LED3, LED3_NUMBER)
#define Led3Toggle()  {if ( IsLed3On() ) Led3Off(); else Led3On();}


#define Led1Init()  SetBit(DDR_LED1, LED1_NUMBER)
#define Led2Init()  SetBit(DDR_LED2, LED2_NUMBER)
#define Led3Init()  SetBit(DDR_LED3, LED3_NUMBER)

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
#define IntArranqueInit()  {ClearBit(DDR_INT_ARRANQUE, INT_ARRANQUE_NUMBER); SetBit(PORT_INT_ARRANQUE, INT_ARRANQUE_NUMBER);}


// lee el pin del boton de arranque
#define IsIntArranqueSet()      IsBitSet(PIN_INT_ARRANQUE, INT_ARRANQUE_NUMBER)


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

// Se configuran los pines de los jumpers como entrada. Al setear los pines en
// '1' y estando configurados como entradas, se activan los pull-up internos
#define Jumper1Init()  {ClearBit(PORT_JMP1, JMP1_NUMBER); SetBit(PORT_JMP1, JMP1_NUMBER);}
#define Jumper2Init()  {ClearBit(PORT_JMP2, JMP2_NUMBER); SetBit(PORT_JMP2, JMP2_NUMBER);}

#define IsJumper1Set()     IsBitSet(PIN_JMP1, JMP1_NUMBER)
//#define IsJumper1Clear()   IsBitClear(PIN_JMP1,JMP1_NUMBER)
#define IsJumper2Set()     IsBitSet(PIN_JMP2, JMP2_NUMBER)
//#define IsJumper2Clear()   IsBitClear(PIN_JMP1,JMP1_NUMBER)

/* ----------------------------------------------------- */


#endif
