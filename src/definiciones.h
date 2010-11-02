#ifndef _DEFINICIONES_
#define _DEFINICIONES_
/* Defines y Macros de proposito general */

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

#endif
