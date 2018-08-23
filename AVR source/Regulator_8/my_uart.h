#ifndef MY_UART_H_
#define MY_UART_H_

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/pgmspace.h>
#define speed 51

void uart_init()
{
	//Enable transmiter and receiver and enable Recive interrupt
	UCSRB |= (1<<TXEN) | (1<< RXEN)| (1 << RXCIE);
	//UCSRB |= (1<< RXEN) | (1 << RXCIE);
	//SetBit(UCSRB,TXEN); SetBit(UCSRB,RXEN); SetBit(UCSRB,RXCIE);

	//Enable only receiver and enable Recive interrupt
	//UCSRB |= (1<< RXEN) | (1 << RXCIE);

	// 8 data, 1 stop, no parity
	//UCSRC |= (1<<URSEL)/*7*/ | (1<<UCSZ0)/*1*/ | (1<<UCSZ1)/*2*/;
	UCSRC = 0b10000110;


	//baudrate
	UBRRH= speed >> 8;
	UBRRL=(uint8_t) speed;
}

void uart_send(uint8_t data)
{
    while (!( UCSRA & (1 << UDRE))); // wait while register is free
    UDR = data;                    // load data into the register
}

uint8_t uart_receive()
{
	while(!((UCSRA) & (1 << RXC)));     // wait while data is being received
	return UDR;                     // return data
}

uint8_t uart_receive_NoWait()
{
	if(!((UCSRA) & (1 << RXC)))    // wait while data is being received
	return '0';
	else return UDR;// return data

}

uint8_t uart_receive_Wait(unsigned int W)
{
	while(W)
	{
		if(!((UCSRA) & (1 << RXC))) W--; // wait while data is being received
		else return UDR;// return data
	}
	 return '0';// return data
}

void uart_send_string(uint8_t * ss)
{
	int i=0;
	while(*ss!='\0')
	{
		uart_send(*ss);
		ss++;
	}

}

#endif /* MY_UART_H_ */
