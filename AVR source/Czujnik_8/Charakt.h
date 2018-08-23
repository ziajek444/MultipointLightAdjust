#ifndef CHARAKT_H_
#define CHARAKT_H_


uint16_t EEMEM Luksy[245];
uint16_t AdcTab[245] = {275,426,574,686,785,878,970,1055,1115,1174,1231,1296,1361,1398,1435,1481,1524,1563,1599,1633,1665,1698,1729,1759,1787,1817,1845,1868,1891,1913,1938,1967,1989,2011,2030,2050,2079,2094,2107,2123,2138,2153,2168,2183,2198,2213,2228,2243,2259,2276,2292,2305,2317,2329,2341,2349,2355,2362,2368,2374,2381,2387,2394,2400,2406,2413,2419,2426,2432,2439,2445,2451,2458,2464,2471,2477,2483,2490,2496,2503,2509,2515,2522,2528,2535,2541,2547,2553,2559,2565,2571,2577,2583,2589,2595,2601,2607,2613,2619,2625,2631,2637,2643,2649,2655,2661,2667,2673,2679,2685,2691,2697,2703,2709,2715,2721,2727,2733,2739,2745,2751,2757,2763,2769,2775,2781,2787,2793,2799,2805,2811,2817,2823,2829,2835,2841,2847,2853,2859,2865,2871,2877,2883,2889,2895,2901,2907,2913,2919,2925,2931,2937,2943,2949,2955,2961,2967,2973,2979,2985,2991,2997,3003,3009,3015,3021,3027,3033,3039,3045,3051,3057,3063,3069,3075,3081,3087,3093,3099,3105,3111,3117,3123,3129,3135,3141,3147,3153,3159,3165,3171,3177,3183,3189,3195,3201,3207,3213,3219,3225,3231,3237,3243,3249,3255,3261,3267,3273,3279,3285,3291,3297,3303,3309,3315,3321,3327,3333,3339,3345,3351,3357,3363,3369,3375,3381,3387,3393,3399,3405,3411,3417,3423,3429,3435,3441,3447,3453,3459,3465,3471,3477,3483,3489,3495}; //1 - 20 - 50 - 75 - 100 - 150 - 200 - 300 - 500 - 750 - 1000 - 1500 - 2000 - 3000 - 5000 - 6863
//uint16_t EEMEM start_eep;
uint8_t Start=0;


//-----------------2,2k---------------------------------
uint16_t Luxy2_2k(uint16_t Adc) //2,2k
{

	if(Start!=1)
	{
		uint16_t LX;
		uint16_t ik=0;
		LX = 1; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 11; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 21; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 31; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 41; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 51; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 61; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 70; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 80; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 90; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 100; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 110; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 120; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 130; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 140; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 150; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 160; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 169; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 179; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 189; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 199; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 209; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 219; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 229; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 239; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 249; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 259; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 268; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 278; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 288; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 298; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 308; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 318; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 328; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 338; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 348; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 358; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 367; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 377; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 387; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 397; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 407; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 417; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 427; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 437; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 447; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 457; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 466; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 476; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 486; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 496; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 506; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 516; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 526; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 536; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 546; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 556; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 565; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 575; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 585; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 595; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 605; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 615; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 625; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 635; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 645; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 655; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 664; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 674; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 684; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 694; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 704; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 714; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 724; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 734; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 744; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 754; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 763; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 773; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 783; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 793; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 803; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 813; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 823; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 836; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 849; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 864; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 879; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 892; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 907; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 922; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 935; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 950; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 965; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 978; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 993; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1006; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1021; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1036; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1049; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1064; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1079; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1092; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1107; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1122; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1135; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1151; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1168; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1184; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1201; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1217; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1235; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1252; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1268; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1285; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1303; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1320; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1336; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1353; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1369; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1387; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1404; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1420; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1437; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1453; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1471; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1488; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1504; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1521; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1537; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1565; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1592; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1618; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1645; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1673; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1699; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1725; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1752; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1778; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1806; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1833; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1859; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1885; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1912; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1940; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1966; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 1993; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2019; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2046; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2080; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2115; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2149; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2184; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2219; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2253; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2288; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2323; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2357; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2392; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2427; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2461; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2496; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2531; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2565; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2600; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2635; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2669; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2704; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2739; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2773; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2808; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2842; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2877; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2912; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2946; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 2981; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3014; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3073; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3131; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3191; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3248; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3306; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3366; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3423; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3483; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3540; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3598; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3646; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3681; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3717; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3752; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3787; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3823; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3858; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3894; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3929; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 3964; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4000; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4035; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4070; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4106; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4141; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4177; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4212; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4247; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4283; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4331; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4393; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4455; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4517; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4579; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4641; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4703; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4765; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4827; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4889; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 4951; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5013; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5075; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5137; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5199; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5261; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5323; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5385; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5447; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5509; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5571; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5633; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5695; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5771; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5863; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 5955; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6047; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6138; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6230; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6322; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6413; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6505; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6614; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6725; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6837; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 6949; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 7061; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 7172; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		LX = 7267; eeprom_write_block(&LX,&Luksy[ik],2); ik++;
		Start=1;
	}



    int i;
	float roznica;
	float dzielnik;
	float dodajnik = 0;
	float Wynik = 0;
	uint16_t Zwrot = 0;

	if(Adc<AdcTab[0]) return 0;
	else if (Adc>AdcTab[244]) return 7500;


	for(i=1;i<245;i++)
    {
        if(Adc<=AdcTab[i])
        {
             roznica = AdcTab[i] - AdcTab[i-1];
             dzielnik = (uint16_t)eeprom_read_word(&Luksy[i]) - (uint16_t)eeprom_read_word(&Luksy[i-1]);//(uint16_t)eeprom_read_dword(&Luksy[i]) - (uint16_t)eeprom_read_dword(&Luksy[i-1]);
             if(dzielnik==0) return 1111;
             dodajnik = roznica / dzielnik;
             Wynik = AdcTab[i-1];
             Zwrot = (uint16_t)eeprom_read_word(&Luksy[i]);
             while(Wynik<Adc)
             {
                 Wynik += dodajnik;
                 Zwrot++;
             }
             return Zwrot;
        }
    }
	return 0;
};
//----------------------------------2,2k-------------------------------

#endif /* CHARAKT_H_ */
