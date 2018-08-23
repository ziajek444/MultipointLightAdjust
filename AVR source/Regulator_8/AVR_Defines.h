#ifndef AVR_DEFINES_H_
#define AVR_DEFINES_H_

//Ziajek definy
#define F_CPU 8000000UL
#define SetBit(rejestr,bit) rejestr|=(1<<bit)
#define ClrBit(rejestr,bit) rejestr&=~(1<<bit)
#define NegBit(rejestr,bit) rejestr^=(1<<bit)
//end Ziajek definy

#endif /* AVR_DEFINES_H_ */
