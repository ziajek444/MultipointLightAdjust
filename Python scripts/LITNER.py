def Vector(arg,n):
    odczyt = ""
    #name = "C05REF_Led" #"LuxREF_cz" #"C06REF_cz"  Statyczna nazwa
    name = arg # dynamiczna nazwa
    with open(name+".txt",'r') as F:
        #print(F.read())
        odczyt = F.read() 
    #print(odczyt[:50])

    liczba = ""
    lista = []
    odczyt+=" "

    for c in odczyt:
        if c >= '0' and c<= '9':
            liczba+=c
        elif liczba != "":  #Jezeli na koncu pliku bedzie za duzo \r lub \n, program sie nie zepsuje, poprostu nie wezmie pod uwage pustej linii.
            lista.append(liczba)
            liczba = ""

    l = []
    l = [int(i) for i in lista]

    dodajnik = 0 #liczba ktora bedziemy dodawac do poprzedniej wartosci
    lista_X = [] #lista kolejnych REF
    lista_Y = [] #lista kolejnych wartości ADC

    if len(lista) % 2 != 0:
        raise NameError("Nie parzysta liczba elementow!")

    for element in range(0,len(lista),2): 
        lista_X.append(l[element])
        lista_Y.append(l[element+1])
    #print(lista_X)
    #print(lista_Y)

    roznica = 0 

    lista_REF = []
    lista_ADC = []

    for x in range(0,len(lista_X)-1):
        if int(lista_X[x+1]) > int(lista_X[x]+1):
            roznica = lista_X[x+1]-lista_X[x]
            dodajnik = (lista_Y[x+1]-lista_Y[x])/roznica
            for y in range(0,roznica):
                lista_REF.append(lista_X[x]+y)
                lista_ADC.append(int((lista_Y[x]+(y*dodajnik))))

    for e in range(0,len(lista_REF)-1):
        if lista_REF[e] >= lista_REF[e+1]:
            print("chuj")
            print(lista_REF[e])

    with open(name+"W.txt",'w') as F:
        F.write("")
    with open(name+"W.txt",'a') as F:
        for i in range(0,len(lista_REF)):
            F.write(str(lista_REF[i]) + " " + str(lista_ADC[i]) + "\n")
    del lista_X, lista_Y

    if n=="REF":
        return lista_REF
    elif n=="ADC":
        return lista_ADC
    else:
        return [i*2 for i in range(0,10)]
