#skrypt do poprawiania wykresy tak aby
# dało się go wykorzystać w mikrokontrolerze

with open("2_2K_wykres.txt",'r') as F:
    Zawartosc = F.read();

#print(Zawartosc)
    liczba="";
    lista = [];
for c in Zawartosc:
        if c >= '0' and c<= '9':
            liczba+=c
        elif liczba != "":  #Jezeli na koncu pliku bedzie za duzo \r lub \n, program sie nie zepsuje, poprostu nie wezmie pod uwage pustej linii.
            lista.append(int(liczba))
            liczba = ""


#print(lista)
listaX = lista[0::2]
listaY = lista[1::2]

listaX = listaX[::-1]
listaY = listaY[::-1]
#print(len(listaY))

h = listaX[0]
nowaListaX = []
nowaListaX.append(h)

index = 1;
nowaListaY = []
nowaListaY.append(listaY[0])

for L in listaX[1:]:
    if h != L:
        nowaListaX.append(L)
        nowaListaY.append(listaY[index])
        h = L
    index+=1

nowaListaX = nowaListaX[::-1]
nowaListaY = nowaListaY[::-1]
#print(len(nowaListaX))
#print(len(nowaListaY))
counter = 0;
with open("2_2K_wykresW.txt",'w') as F:
  for f in range(0,len(nowaListaX),6):
    #F.write("{"+ "{0},{1}".format(nowaListaY[f],nowaListaX[f])+ "},\n");
    #F.write("{0},".format(nowaListaY[f],nowaListaX[f]));
    F.write("LX = {0}; eeprom_write_block(&LX,&Luksy[ik],2); ik++; \n".format(nowaListaY[f],nowaListaX[f]));
    counter+=1

print(counter)
#for P in range(len(nowaListaY)):
#    print(str(nowaListaX[P]) + "\t" + str(nowaListaY[P]) +" \n")

#import matplotlib.pyplot as plt

#plt.figure(1)

#plt.plot(nowaListaX,nowaListaY)
#plt.show();

