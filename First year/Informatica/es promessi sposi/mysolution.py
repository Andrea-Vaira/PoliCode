from string import punctuation
from random import *


def leggiFile(fileName):
    file = open(fileName, 'r', encoding='utf-8')
    f = file.read()
    for char in punctuation:
        f = f.replace(char, ' ')
    return f.split()

def creaBigrammi(listaParole):
    listaBigrammi = []
    bigrammi = {}
    for i in range (0, len(listaParole)-1):
        listaBigrammi.append([listaParole[i], listaParole[i+1]])
    for bigramma in listaBigrammi:
        key = bigramma[0]+' '+bigramma[1]
        if key in bigrammi:
            bigrammi[key] = bigrammi[key] + 1
        else:
            bigrammi[key] = 1
    return bigrammi
    
def esisteParola(parola, list):
    if parola in list:
        return True
    else:
        return False     

def generaFrase(primaParola, dict):
    dictParola = {}
    parola = primaParola
    frase = primaParola

    numParole = randint(5, 50)
    for n in range(numParole):
        for key in dict:
            keyParola = key.split()[0]
            if keyParola == parola:
                dictParola[key] = dict[key]
        
        listDicts = list(dictParola.items())
        listSorted = sorted(listDicts, key=lambda x: x[1], reverse=True)
        listaScelte = []
        if len(listSorted) > 5:
            listaScelte = listSorted[0:5]
        parola = listaScelte[randint(0, len(listaScelte)-1)][0].split()[1]
        frase = frase + ' ' + parola
    print(frase)
    return       
            

def main():
    list = leggiFile('promessisposi.txt')
    dict = creaBigrammi(list)
    
    print('Inserisci una parola')
    parola = input()
    while len(parola) != 0:
        if not esisteParola(parola, list):
            indice = randint(0, len(list)-1)
            parola = list[indice]
        generaFrase(parola, dict)
        print('Inserisci una parola')
        parola = input()
    return


main()

