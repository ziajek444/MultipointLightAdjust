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
	// 'a' (add) 'd' (delete) 'b' (bug/b³ad)
	uint8_t Err;
	bool IsOpen;
	uint32_t MAX;// maksymalny poziom LX (swiatlo bedzie utrzymywane w przedziale MAX : MAX-100)
	bool IsChanged;
};

volatile uint8_t total;

void WE_WY_Init(struct wejWyj objekty[])
{

		objekty[PC_0].Err = 0;
		objekty[PC_0].name = "PC0";
		objekty[PC_0].role = 'p';
		objekty[PC_0].Command = '-';
		objekty[PC_0].IsChanged = false;
		objekty[PC_0].IsOpen = true;
		//total = 1; //PC0
		objekty[C_01].Err = 0;
		objekty[C_01].name = "C01";
		objekty[C_01].role = 'c';
		objekty[C_01].LX = 10000;
		objekty[C_01].Command = '-';
		objekty[C_01].IsChanged = false;
		objekty[C_01].IsOpen = true;
		objekty[C_01].MAX = 10000;
		//total++;
		objekty[R_10].Err = 0;
		objekty[R_10].name = "R01";
		objekty[R_10].role = 'r';
		objekty[R_10].PWM = 125;
		objekty[R_10].Command = '-';
		objekty[R_10].IsChanged = false;
		objekty[R_10].IsOpen = true;
		//total++;
		objekty[3].Err = 0;
		objekty[3].role = 'c';
		objekty[3].LX = 10000;
		objekty[3].Command = '-';
		objekty[3].IsChanged = false;
		objekty[3].IsOpen = false;
		objekty[3].name = "C02";

		objekty[4].Err = 0;
		objekty[4].role = 'r';
		objekty[4].PWM = 125;
		objekty[4].Command = '-';
		objekty[4].IsChanged = false;
		objekty[4].IsOpen = false;
		objekty[4].name = "R02";

		objekty[5].Err = 0;
		objekty[5].role = 'c';
		objekty[5].LX = 10000;
		objekty[5].Command = '-';
		objekty[5].IsChanged = false;
		objekty[5].IsOpen = false;
		objekty[5].name = "C03";

		objekty[6].Err = 0;
		objekty[6].role = 'r';
		objekty[6].PWM = 125;
		objekty[6].Command = '-';
		objekty[6].IsChanged = false;
		objekty[6].IsOpen = false;
		objekty[6].name = "R03";

		objekty[7].Err = 0;
		objekty[7].role = 'c';
		objekty[7].LX = 10000;
		objekty[7].Command = '-';
		objekty[7].IsChanged = false;
		objekty[7].IsOpen = false;
		objekty[7].name = "C04";

		objekty[8].Err = 0;
		objekty[8].role = 'r';
		objekty[8].PWM = 125;
		objekty[8].Command = '-';
		objekty[8].IsChanged = false;
		objekty[8].IsOpen = false;
		objekty[8].name = "R04";

		objekty[9].Err = 0;
		objekty[9].role = 'c';
		objekty[9].LX = 10000;
		objekty[9].Command = '-';
		objekty[9].IsChanged = false;
		objekty[9].IsOpen = false;
		objekty[9].name = "C05";

		objekty[10].Err = 0;
		objekty[10].role = 'r';
		objekty[10].PWM = 125;
		objekty[10].Command = '-';
		objekty[10].IsChanged = false;
		objekty[10].IsOpen = false;
		objekty[10].name = "R05";

		objekty[11].Err = 0;
		objekty[11].role = 'c';
		objekty[11].LX = 10000;
		objekty[11].Command = '-';
		objekty[11].IsChanged = false;
		objekty[11].IsOpen = false;
		objekty[11].name = "C06";

		objekty[12].Err = 0;
		objekty[12].role = 'r';
		objekty[12].PWM = 125;
		objekty[12].Command = '-';
		objekty[12].IsChanged = false;
		objekty[12].IsOpen = false;
		objekty[12].name = "R06";

		objekty[13].Err = 0;
		objekty[13].role = 'c';
		objekty[13].LX = 10000;
		objekty[13].Command = '-';
		objekty[13].IsChanged = false;
		objekty[13].IsOpen = false;
		objekty[13].name = "C07";

		objekty[14].Err = 0;
		objekty[14].role = 'r';
		objekty[14].PWM = 125;
		objekty[14].Command = '-';
		objekty[14].IsChanged = false;
		objekty[14].IsOpen = false;
		objekty[14].name = "R07";

		objekty[15].Err = 0;
		objekty[15].role = 'c';
		objekty[15].LX = 10000;
		objekty[15].Command = '-';
		objekty[15].IsChanged = false;
		objekty[15].IsOpen = false;
		objekty[15].name = "C08";

		objekty[16].Err = 0;
		objekty[16].role = 'r';
		objekty[16].PWM = 125;
		objekty[16].Command = '-';
		objekty[16].IsChanged = false;
		objekty[16].IsOpen = false;
		objekty[16].name = "R08";

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

///Funkcja zwracaj¹ca zasiêg w jakim ma byc regulowane swiatlo, od 50 do 150 lx
int Wm(int Wb) //Wm wartoœc maksymalna //Wb wartosc bezpieczna
{
	int Wm = 0;
	int Wb20pr = Wb / 5;

	if 		(Wb20pr <= 50) 					Wm = Wb + 50;
    else if (Wb20pr > 50 && Wb20pr <= 200) 	Wm = Wb + Wb20pr;
    else if (Wb20pr > 200) 					Wm = Wb + 200;
    else return -1;

    return Wm;
}


#endif /* FUNKCJE_H_ */
