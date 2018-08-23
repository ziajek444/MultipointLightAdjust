#ifndef FUNKCJE_H_
#define FUNKCJE_H_

typedef enum //zmienna boolowska
{
        false,//0
        true//1
} bool;

struct wejWyj
{
	volatile char * name; //C01, R12, PC0
	unsigned char role; //r (regulator), c (czujnik), p (pc)
	uint32_t LX; //dla czujnikow
	uint8_t PWM; //dla regulatorów, wartoœc od razu przeliczona zeby regulator nie wykonywal obliczen
	uint8_t Command; //'g' (good) ; 'r' (refresh) ; 'l' (get lux) ; 'n' (new info for driver) ; 'e' (end transmision)
	// 'a' (add) 'd' (delete) 'b' (bug/b³¹d)
	uint8_t Err;
	bool IsOpen;
	uint32_t MAX;// maksymalny poziom LX (swiatlo bedzie utrzymywane w przedziale MAX : MAX-100)
	bool IsChanged;
};

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

uint32_t StrToUint32(uint8_t str[])
{
	//max 9 999 999
	volatile uint32_t zwrot = (str[0]-48)*1000000;
	zwrot += (str[1]-48)*100000;
	zwrot += (str[2]-48)*10000;
	zwrot += (str[3]-48)*1000;
	zwrot += (str[4]-48)*100;
	zwrot += (str[5]-48)*10;
	zwrot += (str[6]-48)*1;

	return zwrot;
}

/*uint8_t CharToDigital(uint8_t character)
{
	uint8_t digital=character-48;
	return digital;
}*/

volatile bool END_WAIT = false;
void WaitForResponse(uint16_t ms)
{
	END_WAIT = false;
	while(END_WAIT==false && ms>0)
	{
		ms--;
		_delay_ms(1);
	}
	_delay_ms(1);
	END_WAIT = true;
}

/*uint8_t IDtoDigital(uint8_t ID)
{
	uint8_t Digital;
	if(ID==0x01) Digital='1';
	else if(ID==0x02) Digital='2';
	else if(ID==0x03) Digital='3';
	else if(ID==0x04) Digital='4';
	else if(ID==0x05) Digital='5';
	else if(ID==0x06) Digital='6';
	else if(ID==0x07) Digital='7';
	else if(ID==0x08) Digital='8';
	else if(ID==0x09) Digital='9';
	else Digital = 0;

	return Digital;
}*/

#endif /* FUNKCJE_H_ */
