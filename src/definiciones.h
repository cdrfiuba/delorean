#ifndef _DEFINICIONES_
#define _DEFINICIONES_
/* Defines y Macros de proposito general */

#define Nop()	  asm volatile("nop")
#define Reti()	asm volatile("reti")

#define LOW(a)    (char)(a & 0x00ff)
#define	HIGH(a)   (char)(a >> 8)

#define SetBit(Byte,Bit)   (  Byte |= (1<<Bit) )
#define	ClearBit(Byte,Bit) (  Byte &= (~(1<<Bit)) )
#define IsBitSet(Byte,Bit) ( (Byte >> Bit) & 0x01 )
#define GetBit(Byte,Bit)   ( (Byte >> Bit) & 0x01 )
//#define IsBitClear(Byte,Bit) ( (Byte & (1<<Bit)) ? false : true )
// En general no hace falta preguntar IsBitClear(), ya que se puede saber a 
// partir de IsBitSet() = false

#define max(a,b)			( a>b ? a : b)
#define min(a,b)		  ( a>b ? a : b)

#define concat(a,b)             a ## b
#define def_port_reg(name)      concat(PORT,name)
#define def_pin_reg(name)       concat(PIN,name)
#define def_ddr_reg(name)       concat(DDR,name)

/* ----------------------------------------------------------*/

#endif
