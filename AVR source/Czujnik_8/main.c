///Czujnik

#include "AVR_Defines.h"
#include <avr/io.h>
#include <avr/delay.h>
#include<avr/eeprom.h>
#include "Charakt.h"
#include "my_uart.h"
#include "funkcje.h"
#include <avr/interrupt.h>
#include <util/atomic.h>



typedef enum //zmienna boolowska
{
        false,//0
        true//1
} bool;

volatile uint8_t odebrano=0;//zmienna przechowywuj¹ca nadchodz¹cy bajt
volatile const uint8_t * CPU_name = "C05"; // C01 ; R12 ; C23 ;
volatile bool wait = false;
volatile bool blad = false;
volatile uint16_t PelnyWynik=0;
volatile uint8_t L=0;
volatile uint8_t H=0;
volatile uint16_t sum=0;
volatile uint16_t lastResult=0;
volatile uint16_t actualResult=0;
volatile uint16_t workResult=0;
volatile uint8_t workCounter=0;
volatile uint8_t actualCounter=0;
volatile uint8_t state=0;



int main(void)
{

	//Start = eeprom_read_word(&start_eep);

	uart_init();//inicjalizacja UARTU
	SetBit(DDRB,DDB0);
	SetBit(PORTB,PB0);
	SetBit(DDRD,DDD2);
	SetBit(PORTD,PD2);
	ADMUX  |= 0b01100000;//Avcc/ Left/ ADC0
	ADCSRA |= 0b10000111;//ON /not started conversion/ single measure mode / interrupt disable / /8 prescaller

	MCUCR |= (1<<SE) | (1<<SM0);
	ADCSRA |= 0b01000111;
	while((ADCSRA & 0b00010000) == 0b00010000) {  }
	L = ADCL;
	L >>= 6;
	H=ADCH;
	sum = H;
	sum <<= 2;
	sum+=L;
	lastResult=(sum<<2);
	ClrBit(MCUCR,SE);

sei();//zezwolenie na przewania
while (1)
{
	
	//If the ADC is enabled, a conversion starts
	//automatically when this mode is entered
	ATOMIC_BLOCK(ATOMIC_FORCEON)//ATOMIC_FORCEON//ATOMIC_RESTORESTATE
	{
		MCUCR |= (1<<SE) | (1<<SM0);
		ADCSRA |= 0b01000111;//start
		while((ADCSRA & 0b00010000) == 0b00010000) {  }
		ClrBit(MCUCR,SE);
	}
	_delay_ms(20);
	L = ADCL;
	L >>= 6;
	H=ADCH;
	sum = H;
	sum <<= 2;
	sum+=L;
	workResult+=sum+1;
	workCounter++;

	if(workCounter>=4)//rozdzielczosc poprawiona o 1 bit
	{
		workCounter=0;
		actualResult+=(workResult>>1);
		workResult=0;
		actualCounter++;
		if(actualCounter>=4)//roz. poprawiona o 2 bity
		{
			actualCounter=0;
			lastResult=(actualResult>>1)-1;
			actualResult=0;
			workResult=0;
			//uart_send_string(liczba(AdcToLux(lastResult)));
			//uart_send_string(" ");
		}
	}

	if(odebrano >= 3)
	{
		NegBit(PORTB,PB0);
		wait=true;
		uart_send_string("g");
		while(wait==true) { _delay_us(1); }

		//
		//wersja testowa  if(!blad) uart_send_string(liczba(lastResult));
		//
		if(!blad) uart_send_string(liczba(AdcToLux(lastResult))); //Dobra wersja
		else
		{
			uart_send_string("b");
			blad = false;
		}
		odebrano = 0;
	}
}

}

ISR(USART_RXC_vect)//przerwanie dla nadchodz¹cego bajtu z RX
{
	uint8_t bajcik;

	bajcik = UDR;
	if(wait==false)
	{
		if(odebrano == 0 && bajcik == CPU_name[0]) odebrano++;
		else if(odebrano == 1 && bajcik == CPU_name[1]) odebrano++;
		else if(odebrano == 2 && bajcik == CPU_name[2]) odebrano++;
		else odebrano=0;
	}
	else
	{
		if(bajcik == 'l') wait=false;
		else
			{
			blad = true; wait=false;
			}
	}
}

ISR(ADC_vect)
{

}
