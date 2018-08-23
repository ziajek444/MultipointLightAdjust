#ifndef AVR_DEFINES_H_
#define AVR_DEFINES_H_

// Defs
#define F_CPU 8000000UL
#define SetBit(rejestr,bit) rejestr|=(1<<bit)
#define ClrBit(rejestr,bit) rejestr&=~(1<<bit)
#define NegBit(rejestr,bit) rejestr^=(1<<bit)
#define PC_0 0
#define C_01 1
#define R_10 2
#define C_02 3
#define R_20 4
#define C_03 5
#define R_30 6
#define C_04 7
#define R_40 8
#define C_05 9
#define R_50 10
#define C_06 11
#define R_60 12
#define C_07 13
#define R_70 14
#define C_08 15
#define R_80 16
#define amount_of_devices 16
//end Defs

#endif /* AVR_DEFINES_H_ */




