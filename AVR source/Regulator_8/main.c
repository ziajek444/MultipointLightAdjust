///Regulator
#include "AVR_Defines.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "my_uart.h"
#include "funkcje.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile uint8_t odebrano=0;//zmienna przechowywuj¹ca nadchodz¹cy bajt
volatile const uint8_t * CPU_name = "R04"; // C01 ; R12 ; C23 ;

int main(void)
{
	SetBit(DDRB,1);//W³¹czenie PB1/OC1A
	// initialize timer1a in PWM mode
	TCCR1A |= (1<<WGM10)|(1<<COM1A1); //Fast PWM, 8-bit 0x00FF BOTTOM TOP ; non inverting mode
	TCCR1B |= (1<<CS11)|(1<<WGM12); //preskaler /1(CS10) /8(CS11)


	uart_init();//inicjalizacja UARTU
	_delay_ms(100);
	uint8_t i_help = 255;
	OCR1A = 255;
	SetBit(DDRC,5);
	SetBit(PORTC,5);
	sei();//zezwolenie na przewania
	int kierunek=0;

	while(1)
	{


		if(odebrano==3)
		{
			NegBit(PORTC,5);
			uart_send('g');
			odebrano=4;
		}

		if(odebrano==5)
		{
			//tryb odpowiedzi na zmiane,
			//uart_send(OCR1A);
			odebrano=0;
		}
	}


}

ISR(USART_RXC_vect)//przerwanie dla nadchodz¹cego bajtu z RX
{
	uint8_t bajcik;
	bajcik = UDR;

	if(odebrano<3)
	{

		if(odebrano == 0 && bajcik == CPU_name[0]) odebrano++;
		else if(odebrano == 1 && bajcik == CPU_name[1]) odebrano++;
		else if(odebrano == 2 && bajcik == CPU_name[2]) odebrano++;
		else odebrano=0;
	}
	else if(odebrano==4)
	{
			OCR1A=bajcik;
			odebrano=5;
	}

}


