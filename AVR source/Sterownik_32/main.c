///STEROWNIK
#include "AVR_Defines.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "my_uart.h"
#include "funkcje.h"
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdio.h>
#include <string.h>
#include<avr/eeprom.h>


volatile uint8_t Feedback = '-';
volatile uint8_t BUFOR_wejsciowy[64];
volatile uint8_t licznik_bufor_we=0;
volatile bool ReceiveAcces=false;
volatile uint8_t Index = 0;
uint8_t* EEMEM AdresEprom = 0x00;

int main(void)
{

	uart_init();//inicjalizacja UARTU
	sei();//zezwolenie na przewania

	AdresEprom = 0x00;

	// WE/Wy init
	struct wejWyj objekty[amount_of_devices+1];
	WE_WY_Init(objekty);

	AdresEprom = 0x01;
	for(int i=1;i<=16;i++)
		{
			objekty[i].IsOpen = eeprom_read_dword(AdresEprom);
			AdresEprom++;//+1
		}
	AdresEprom=0x00;

	///Zmienne przechowywuj¹ce informacje o danych wyjœciowych
	volatile uint8_t BUFOR_wyjsciowy[512];//deklaracja
	BUFOR_wyjsciowy[0]='\0';//zerowanie
	volatile uint8_t licznik_bufor_wy=0;

	volatile uint8_t s_help[128];
	s_help[0] = '\0';
	volatile uint8_t s_help2[128];
	s_help2[0] = '\0';
	volatile int i_help=0;

	DDRA = 0b00000001;
	SetBit(PORTA,0);

    while (1)
    {

		if(objekty[Index].IsOpen==true)
		{
				ATOMIC_BLOCK(ATOMIC_FORCEON)
				{
					licznik_bufor_we=0;
					BUFOR_wejsciowy[0]='\0';
					ReceiveAcces=true;
					uart_send_string(objekty[Index].name);
					if(objekty[Index].name[0]=='P') NegBit(PORTA,0);
				}

				WaitForResponse(25);//keyword delay//10 ms to za malo, komputer wysy³a 'g' juz do nastêpnego objektu
				ReceiveAcces=false;

				ATOMIC_BLOCK(ATOMIC_FORCEON)
				{

					if(BUFOR_wejsciowy[0] != '\0')
					{
							// <<operacje>>
						if(BUFOR_wejsciowy[0]=='r' && Index==0) //refresh //tylko komputer
						{
							objekty[Index].Command = 'r';
						}
						else if(BUFOR_wejsciowy[0]=='n' && Index==0) //new info
						{
							objekty[Index].Command = 'n';
						}
						else if(BUFOR_wejsciowy[0]=='g') //good
						{
							objekty[Index].Command = 'g';
						}
						else uart_send_string("b");//brak odpowiedzi


						BUFOR_wejsciowy[0]='\0';//czyszczenie
						licznik_bufor_we=0;
					}
					else uart_send_string("b");//brak odpowiedzi

				}//Atomic

//---------------------------------------------------------------------------------------//

				//Wykonanie komend
				if(Index==0 && objekty[Index].Command == 'n')
				{// PC>n
					objekty[Index].Command = '-';
					ReceiveAcces=true;
					uart_send_string("g");//od terazczekam na nowosci
					WaitForResponse(5000);//keyword delay
					_delay_ms(10);
					ReceiveAcces=false;
					s_help[0] = '\0';
					strcat(s_help,BUFOR_wejsciowy);
					if(s_help[0] != '\0')
					{
						if(strlen(s_help)==10 && s_help[0]=='a' && s_help[9]=='c')//otwarcie portu dla czujnika
						{//a(add)9(ID)1234567(MAX) //!!! Ostatni czujnik ma ID=15
							//Nazwy obiektow sa stale od startu programu
							i_help = s_help[1]-48;
							if(i_help<1 && i_help>16) i_help=3;
							objekty[i_help].IsOpen = true;
							objekty[i_help].Command = '-';
							objekty[i_help].Err = 0;
							s_help2[0]=s_help[2];
							s_help2[1]=s_help[3];
							s_help2[2]=s_help[4];
							s_help2[3]=s_help[5];
							s_help2[4]=s_help[6];
							s_help2[5]=s_help[7];
							s_help2[6]=s_help[8];
							s_help2[7]='\0';
							objekty[i_help].MAX = StrToUint32(s_help2);
							total++;
							uart_send_string("g");//poprawnie dodany czujnik
							BUFOR_wejsciowy[0]='\0';
							AdresEprom = i_help;
							eeprom_write_byte(AdresEprom,true);
							AdresEprom = 0;
						}
						else if(strlen(s_help)==3 && s_help[0]=='a' && s_help[2]=='r')//otwarcie portu dla regulatora
						{//a(oznaczenie add)14(id obiektu)   //!!! Ostatni regulator ma id = 16
							//Nazwy obiektow sa stale od startu programu
							i_help = s_help[1]-48;
							if(i_help<1 && i_help>16) i_help=3;
							objekty[i_help].IsOpen = true;
							objekty[i_help].Command = '-';
							objekty[i_help].Err =0;
							total++;
							uart_send_string("g");//poprawnie dodany regulator
							AdresEprom = i_help;
							eeprom_write_byte(AdresEprom,true);
							AdresEprom = 0;
						}
						else if(strlen(s_help)==2 && s_help[0]=='d')//zamkniecie portu
						{//d(delete)
							i_help = s_help[1]-48;
							if(i_help<1 && i_help>16) i_help=3;
							objekty[i_help].IsOpen = false;
							total--;
							uart_send_string("g");//poprawnie usuniêty obiekt
							AdresEprom = i_help;
							eeprom_write_byte(AdresEprom,false);
							AdresEprom = 0;
						}
						else uart_send_string("b");//Bl¹d ramki
					}
					objekty[Index].Command = '-';
				}//PC>n
				else if(Index==0 && objekty[Index].Command == 'r')
				{//PC>r
					objekty[Index].Command = '-';
					for(int i=1;i<17;i++)
					{
						if(objekty[i].IsOpen == true)
						{

						if(objekty[i].role=='c') strcat(BUFOR_wyjsciowy, "c");
						else if(objekty[i].role=='r') strcat(BUFOR_wyjsciowy, "r");
						else if(objekty[i].role=='p') strcat(BUFOR_wyjsciowy, "p");
						strcat(BUFOR_wyjsciowy, "#");

						s_help[0]='\0';
						strcat(s_help, objekty[i].name);
						s_help2[0]=s_help[0];
						s_help2[1]='_';
						s_help2[2]=s_help[1];
						s_help2[3]=s_help[2];
						s_help2[4]='\0';

						strcat(BUFOR_wyjsciowy, s_help2);


						strcat(BUFOR_wyjsciowy, "#");


							if(objekty[i].role == 'c')
							{
								strcat(BUFOR_wyjsciowy,(uint8_t*)liczba((uint32_t)objekty[i].LX));
							}
							else
							{
								strcat(BUFOR_wyjsciowy,liczba((uint32_t)objekty[i].PWM));
							}

						strcat(BUFOR_wyjsciowy, "#");
						uart_send_string(BUFOR_wyjsciowy);
						_delay_ms(10);//zapewnienie poprawnego przesy³u
						BUFOR_wyjsciowy[0]='\0';
						}
					}
					uart_send_string("e");
					_delay_ms(10);//zapewnienie poprawnego przesy³u
					BUFOR_wyjsciowy[0]='\0';
					objekty[Index].Command = '-';
				}//PC>r
				else if(Index==0 && objekty[Index].Command == 'g')
				{//PC>g
					objekty[Index].Command = '-';
				}//PC>g
				else if(Index!=0 && objekty[Index].Command == 'g' && objekty[Index].role=='c')
				{//C>g
					objekty[Index].Command='-';
					BUFOR_wejsciowy[0]='\0';
					ReceiveAcces=true;
					uart_send('l');
					WaitForResponse(1000);
					_delay_ms(10);
					ReceiveAcces=false;
					s_help[0] = '\0';
					strcat(s_help,BUFOR_wejsciowy);
					BUFOR_wejsciowy[0]='\0';

					if(s_help[0]!='\0' && strlen(s_help)==7)
					{
						objekty[Index].LX = StrToUint32(s_help);

						if( objekty[Index].LX >= objekty[Index].MAX && objekty[Index].LX <= Wm(objekty[Index].MAX) )
						{ }
						else if ( objekty[Index].LX < (objekty[Index].MAX))
						{
							if(objekty[Index+1].PWM <= 254) objekty[Index+1].PWM += 1;
						}
						else
						{
							if(objekty[Index+1].PWM >= 1) objekty[Index+1].PWM -= 1;
						}

					}
				}//C>g
				else if(Index!=0 && objekty[Index].Command == 'g' && objekty[Index].role=='r')
				{//R>g
					objekty[Index].Command = '-';
					uart_send((uint8_t)objekty[Index].PWM);

					_delay_ms(10);
				}//R>g

		}//IF
	Index++;
	if((amount_of_devices+1)==Index) Index=0;

	_delay_ms(1);
	}//while
}

ISR(USART_RXC_vect)//przerwanie dla nadchodz¹cego bajtu z RX
{

	if(ReceiveAcces==true)
	{

		while(((UCSRA) & (1 << RXC)))
		{
			if(licznik_bufor_we>63) licznik_bufor_we=0; //Zapewnienie ¿e je¿eli bufor wyjdzie poza zakres to wróci do pocz¹tku
			BUFOR_wejsciowy[licznik_bufor_we] = UDR; //Przypisanie Nades³anego bajta przez RX do nastêpnej pozycji bufora
			licznik_bufor_we++; //inkrementacja pozycji na której jest zapisywany kolejny bajt
			BUFOR_wejsciowy[licznik_bufor_we] = '\0';
		}
		END_WAIT = true;
	}
	else ClrBit(UCSRA,RXC);

}

