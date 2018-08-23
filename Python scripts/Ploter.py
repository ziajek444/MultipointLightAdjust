import matplotlib.pyplot as plt
import LITNER
import math

def approximate(value, places = 0):
    factor = 10. ** places
    return factor * math.trunc(value / factor)

# [ approximate(x, 1) for x in vector ]
a = []
#wykresy są transponowane, dla ułatwienia analizy

#----------------------------------------------------------------

plt.figure(1)
plt.xlabel('Odczyt ADC (R=10k)')
plt.ylabel('Natężenie światła [Lx]')
plt.title("Porównanie wyników zebranych na luksomierzach LTR579 ALSPS i precyzyjnym \nDla dzielnika 10k")
x1 = LITNER.Vector("C02REF_cz","REF")
y1 = LITNER.Vector("C02REF_cz","ADC")
plt.plot(y1,x1,label="C02-10k ciepłe LTR579")
x1 = LITNER.Vector("C02REF_Led","REF")
y1 = LITNER.Vector("C02REF_Led","ADC")
plt.plot(y1,x1,label="C02-10k Led LTR579")
# dopasowanie wykresu 10k #
#   515 start Wykresy LED
x1 = LITNER.Vector("C02REF_cz","REF")
x1 = [x+((x*55)/100) for x in x1]      #if x >= 856    ### Od 856 dokonywana jest aproksymacja, poniżej 856 poprawaiana jest czytelność wyniku ADC
y1 = LITNER.Vector("C02REF_cz","ADC")
while len(x1)<len(y1):
    y1 = y1[1:]
plt.plot(y1,x1,label="aproksymacja",color='r')

# a 3275 #
l = [i for i in y1 if i < 3275]
y1 = LITNER.Vector("C02REF_Led","ADC")
l = l+y1
a.append(l) #0
while len(l)>len(x1):
    x1.append(x1[len(x1)-1]+1)
a.append(x1) #1
del l
##################

x1 = LITNER.Vector("LuxC02_m","REF")
y1 = LITNER.Vector("LuxC02_m","ADC")
plt.plot(y1,x1,label="C02-10k ciepłe precyzyjny")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

plt.figure(2)
plt.xlabel('Odczyt ADC (R=4,7k)')
plt.ylabel('Natężenie światła [Lx]')
plt.title("Porównanie wyników zebranych na luksomierzach LTR579 ALSPS i precyzyjnym \nDla dzielnika 4,7k")
x1 = LITNER.Vector("C03REF_cz","REF")
y1 = LITNER.Vector("C03REF_cz","ADC")
plt.plot(y1,x1,label="C03-4,7k ciepłe LTR579")
x1 = LITNER.Vector("C03REF_Led","REF")
y1 = LITNER.Vector("C03REF_Led","ADC")
plt.plot(y1,x1,label="C03-4,7k Led LTR579")
# dopasowanie wykresu 4,7k #
#   550 start Wykresy LED
x1 = LITNER.Vector("C03REF_cz","REF")
x1 = [x+((x*65)/100) for x in x1] #if x >= 856
y1 = LITNER.Vector("C03REF_cz","ADC")
while len(x1)>len(y1):
    y1.append(y1[len(y1)-1]+1)
while len(x1)<len(y1):
    #y1 = y1[:len(y1)-1]
    y1 = y1[1:]
plt.plot(y1,x1,label="aproksymacja",color='r')

# a #
l = [i for i in y1 if i < 2345]
y1 = LITNER.Vector("C03REF_Led","ADC")
l = l+y1
a.append(l) #2
while len(l)>len(x1):
    x1.append(x1[len(x1)-1]+1)
a.append(x1) #3

##################
x1 = LITNER.Vector("LuxC03_m","REF")
y1 = LITNER.Vector("LuxC03_m","ADC")
plt.plot(y1,x1,label="C03-4,7k ciepłe precyzyjny")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

plt.figure(3)
plt.xlabel('Odczyt ADC (R=2,2k)')
plt.ylabel('Natężenie światła [Lx]')
plt.title("Porównanie wyników zebranych na luksomierzach LTR579 ALSPS i precyzyjnym \nDla dzielnika 2,2k")
x1 = LITNER.Vector("C04REF_cz","REF")
y1 = LITNER.Vector("C04REF_cz","ADC")
plt.plot(y1,x1,label="C04-2,2k ciepłe LTR579")
x1 = LITNER.Vector("C04REF_Led","REF")
y1 = LITNER.Vector("C04REF_Led","ADC")
plt.plot(y1,x1,label="C04-2,2k Led LTR579")
# dopasowanie wykresu 2,2k #
#   508 start Wykresy LED
x1 = LITNER.Vector("C04REF_cz","REF")
x1 = [x+((x*63)/100) for x in x1] #if x >= 856
y1 = LITNER.Vector("C04REF_cz","ADC")
while len(x1)>len(y1):
    y1.append(y1[len(y1)-1]+1)
while len(x1)<len(y1):
    #y1 = y1[:len(y1)-1]
    y1 = y1[1:]
plt.plot(y1,x1,label="aproksymacja",color='r')

# a #
l = [i for i in y1 if i < 1510]
y1 = LITNER.Vector("C04REF_Led","ADC")
l = l+y1
a.append(l) #4
while len(l)>len(x1):
    x1.append(x1[len(x1)-1]+1)
a.append(x1) #5

##################
x1 = LITNER.Vector("LuxC04_m","REF")
y1 = LITNER.Vector("LuxC04_m","ADC")
plt.plot(y1,x1,label="C04-2,2k ciepłe precyzyjny")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

plt.figure(4)
plt.xlabel('Odczyt ADC (R=1k)')
plt.ylabel('Natężenie światła [Lx]')
plt.title("Porównanie wyników zebranych na luksomierzach LTR579 ALSPS i precyzyjnym \nDla dzielnika 1k")
x1 = LITNER.Vector("C05REF_cz","REF")
y1 = LITNER.Vector("C05REF_cz","ADC")
plt.plot(y1,x1,label="C02-1k ciepłe LTR579")
x1 = LITNER.Vector("C05REF_Led","REF")
y1 = LITNER.Vector("C05REF_Led","ADC")
plt.plot(y1,x1,label="C05-1k Led LTR579")
# dopasowanie wykresu 1k #
#   438 start Wykresy LED
x1 = LITNER.Vector("C05REF_cz","REF")
x1 = [x+((x*100)/100) for x in x1] #if x >= 856
y1 = LITNER.Vector("C05REF_cz","ADC")
while len(x1)>len(y1):
    y1.append(y1[len(y1)-1]+1)
while len(x1)<len(y1):
    #y1 = y1[:len(y1)-1]
    y1 = y1[1:]
plt.plot(y1,x1,label="aproksymacja",color='r')

# a #
l = [i for i in y1 if i < 770]
y1 = LITNER.Vector("C05REF_Led","ADC")
l = l+y1
a.append(l) #6
while len(l)>len(x1):
    x1.append(x1[len(x1)-1]+1)
a.append(x1) #7

##################
x1 = LITNER.Vector("LuxC05_m","REF")
y1 = LITNER.Vector("LuxC05_m","ADC")
plt.plot(y1,x1,label="C05-1k ciepłe precyzyjny")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

#Porównianie wyników wszystkich czujników podczas pomiaru luxometrem precyzyjnym
plt.figure(5)
plt.ylabel('Wskaźnik fotomierza precyzyjnego [Lx]')
plt.xlabel('Odczyt ADC')
plt.title("Porównianie wyników wszystkich czujników\n podczas pomiaru luxometrem precyzyjnym\nświato ciepłe")
x1 = LITNER.Vector("LuxC05_m","REF")
y1 = LITNER.Vector("LuxC05_m","ADC")
plt.plot(y1,x1,label="C05-1k")
x1 = LITNER.Vector("LuxC04_m","REF")
y1 = LITNER.Vector("LuxC04_m","ADC")
plt.plot(y1,x1,label="C04-2,2k")
x1 = LITNER.Vector("LuxC03_m","REF")
y1 = LITNER.Vector("LuxC03_m","ADC")
plt.plot(y1,x1,label="C03-4,7k")
x1 = LITNER.Vector("LuxC02_m","REF")
y1 = LITNER.Vector("LuxC02_m","ADC")
plt.plot(y1,x1,label="C02-10k")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

plt.figure(6)
plt.ylabel('Wskaźnik fotomierza LTR579 ALSPS [Lx]')
plt.xlabel('Odczyt ADC')
plt.title("Porównianie wyników wszystkich czujników\n podczas pomiaru luxometrem LTR579 ALSPS\nświato ciepłe")
x1 = LITNER.Vector("C05REF_cz","REF")
y1 = LITNER.Vector("C05REF_cz","ADC")
plt.plot(y1,x1,label="C05-1k")
x1 = LITNER.Vector("C04REF_cz","REF")
y1 = LITNER.Vector("C04REF_cz","ADC")
plt.plot(y1,x1,label="C04-2,2k")
x1 = LITNER.Vector("C03REF_cz","REF")
y1 = LITNER.Vector("C03REF_cz","ADC")
plt.plot(y1,x1,label="C03-4,7k")
x1 = LITNER.Vector("C02REF_cz","REF")
y1 = LITNER.Vector("C02REF_cz","ADC")
plt.plot(y1,x1,label="C02-10k")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

plt.figure(7)
plt.ylabel('Wskaźnik fotomierza precyzyjnego [Lx]')
plt.xlabel('Odczyt ADC')
plt.title("Porównianie wyników wszystkich czujników\n podczas pomiaru luxometrem LTR579 ALSPS\nświato ciepłe")
x1 = LITNER.Vector("C05REF_Led","REF")
y1 = LITNER.Vector("C05REF_Led","ADC")
plt.plot(y1,x1,label="C05-1k")
x1 = LITNER.Vector("C04REF_Led","REF")
y1 = LITNER.Vector("C04REF_Led","ADC")
plt.plot(y1,x1,label="C04-2,2k")
x1 = LITNER.Vector("C03REF_Led","REF")
y1 = LITNER.Vector("C03REF_Led","ADC")
plt.plot(y1,x1,label="C03-4,7k")
x1 = LITNER.Vector("C02REF_Led","REF")
y1 = LITNER.Vector("C02REF_Led","ADC")
plt.plot(y1,x1,label="C02-10k")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

#Aproksymowane wykresy, Ostateczne
plt.figure(8)
plt.ylabel('Natężenie światła [Lx]')
plt.xlabel('Odczyt ADC')
plt.title("Aproksymowane wykresy,\n zależności między ADC a Natężeniem światła\nPołączone wykresy:\n-Aproksymowany światła ciepłego\n-Nie zmieniony światła Led")
x1 = a[1]
y1 = a[0]
with open("1K_wykres.txt",'w') as F:
    for i in range(0,len(a[0])):
        F.write(str(a[0][i])+"\t"+str(int(a[1][i]))+"\t\n")
        
plt.plot(y1,x1,label="C05-1k")
x1 = a[3]
y1 = a[2]
with open("2_2K_wykres.txt",'w') as F:
    for i in range(0,len(a[2])):
        F.write(str(a[2][i])+"\t"+str(int(a[3][i]))+"\t\n")
        
plt.plot(y1,x1,label="C04-2,2k")
x1 = a[5]
y1 = a[4]
with open("4_7K_wykres.txt",'w') as F:
    for i in range(0,len(a[4])):
        F.write(str(a[4][i])+"\t"+str(int(a[5][i]))+"\t\n")
        
plt.plot(y1,x1,label="C03-4,7k")
x1 = a[7]
y1 = a[6]
with open("10K_wykres.txt",'w') as F:
    for i in range(0,len(a[6])):
        F.write(str(a[6][i])+"\t"+str(int(a[7][i]))+"\t\n")
        
plt.plot(y1,x1,label="C02-10k")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

#----------------------------------------------------------------

#Porównanie figure 5 i figure 6, w celu ukazania różnic w pomiarze różnymi luxometrami
plt.figure(9)
plt.ylabel('Natężenie wskazywane przez luksometr (badanie w laboratorium) [Lx]')
plt.xlabel('Odczyt ADC')
plt.title("Porównianie wyników wszystkich czujników\n podczas pomiaru luxometrem LTR579 ALSPS\nświato ciepłe")
    #   F5  #
x1 = LITNER.Vector("LuxC05_m","REF")
y1 = LITNER.Vector("LuxC05_m","ADC")
plt.plot(y1,x1,label="C05-1k precyzyjny")
x1 = LITNER.Vector("LuxC04_m","REF")
y1 = LITNER.Vector("LuxC04_m","ADC")
plt.plot(y1,x1,label="C04-2,2k precyzyjny")
x1 = LITNER.Vector("LuxC03_m","REF")
y1 = LITNER.Vector("LuxC03_m","ADC")
plt.plot(y1,x1,label="C03-4,7k precyzyjny")
x1 = LITNER.Vector("LuxC02_m","REF")
y1 = LITNER.Vector("LuxC02_m","ADC")
plt.plot(y1,x1,label="C02-10k precyzyjny")
    #   F6  #
x1 = LITNER.Vector("C05REF_cz","REF")
y1 = LITNER.Vector("C05REF_cz","ADC")
plt.plot(y1,x1,label="C05-1k LTR579")
x1 = LITNER.Vector("C04REF_cz","REF")
y1 = LITNER.Vector("C04REF_cz","ADC")
plt.plot(y1,x1,label="C04-2,2k LTR579")
x1 = LITNER.Vector("C03REF_cz","REF")
y1 = LITNER.Vector("C03REF_cz","ADC")
plt.plot(y1,x1,label="C03-4,7k LTR579")
x1 = LITNER.Vector("C02REF_cz","REF")
y1 = LITNER.Vector("C02REF_cz","ADC")
plt.plot(y1,x1,label="C02-10k LTR579")
plt.legend(bbox_to_anchor=(0.9, -0.05), loc=1,
           ncol=2, mode="expand", borderaxespad=0.)

plt.show()
