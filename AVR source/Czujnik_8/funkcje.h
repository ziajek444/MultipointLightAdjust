#ifndef FUNKCJE_H_
#define FUNKCJE_H_


uint16_t AdcToLux(uint16_t result)
{
	return Luxy2_2k(result);
}

void sensownaWiad()
{
	uart_send_string("Wiad testowa");
}

int CompareStrings8(const uint8_t *s1,const uint8_t *s2)
{
	for(int i=0;i<8;i++)
	{
		if(s1[i] != s2[i]) return 0;
		else continue;
	}
	return 1;
}

uint8_t *liczba(uint32_t liczb)
{
	//Max 9 999 999
	volatile uint8_t zwrot[8];
	uint32_t i_help = 10;

	for(int i=6;i>=0;i--)
		{
			zwrot[i] = (liczb%i_help)+48;
			liczb /= 10;

		}
	zwrot[7]='\0';
    return zwrot;
}

#endif /* FUNKCJE_H_ */
