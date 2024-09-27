

from string import punctuation
from random import randint, choice, seed

# non richiesto permette solo di ottenere gli stessi risultati
seed(59) # use this to obtain always the same result

def get_bilemmi(filename):
    # legge testo del file passato come parametro
    lemmi = set()
    bilemmi = dict()
    parola = ''
    with open(filename, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.lower()
            for char in punctuation:
                line = line.replace(char, ' ')
            line = line.split()
            if len(line) > 0:
                if parola != '':
                    bilemmi[(parola, line[0])] = bilemmi.get((parola, line[0]), 0) + 1
                for index,lemma in enumerate(line[:-1]):
                    bilemmi[(lemma, line[index+1])] = bilemmi.get((lemma, line[index+1]), 0) + 1
                    lemmi.add(lemma)
                parola = line[-1]
                lemmi.add(parola)

    if len(lemmi) == 0: # controllo aggiuntivo
        raise ValueError("Nessun dato estratto")

    return lemmi, bilemmi    


def get_valid_bigrams(parola_precedente, bigrams):
    lemmi_validi = [] 
    for bigram in bigrams:
        # check sulla parola se coincide
        if bigram[0] == parola_precedente:
            lemmi_validi.append([bigram[1], bigrams[bigram]])

    return lemmi_validi

def scegli_top_k_lemmi(lemmi_validi, k = 5):
    num_possibilities = min(len(lemmi_validi), k)
    lemmi_validi.sort(key = lambda x : x[1])
    lemmi_validi = lemmi_validi[-num_possibilities:]

    return lemmi_validi
        

def scegli_parola(parola_precedente, bigrams, testo_set) -> str:
    # seleziono i 2-lemmi validi
    lemmi_validi = get_valid_bigrams(parola_precedente, bigrams)
    # se ne esistono prendo i k<=5 piÃ¹ frequenti
    if len(lemmi_validi) > 0: 
        lemmi_validi = scegli_top_k_lemmi(lemmi_validi)
        parola = choice(lemmi_validi)[0]
    # altrimenti scelgo una parola random
    else:
        parola = choice(testo_set)

    return parola

def genera_frase(parola, bigrams, testo_set):
    if parola not in testo_set: # se la parola non esiste
        parola = choice(testo_set) # ne scelgo una random
    lunghezza_frase = randint(5,50) # la prima parola non conta

    # genero frase parola per parola
    for _ in range(lunghezza_frase):
        parola = scegli_parola(parola, bigrams, testo_set)
        print(parola, end = ' ')
    print()

    return 

def main():
    try:
        parole, bigrams = get_bilemmi('promessisposi.txt')

        # print di controllo per don / si puÃ² / la parentela
        # print(bigrams[('si','puÃ²')],bigrams[('la','parentela')],bigrams[('riflessione','dubitativa')])

        # loop input utente
        parola = input("Parola:").strip()
        while parola != '':
            genera_frase(parola, bigrams, parole)
            parola = input("Parola:").strip()

    except Exception as e:
        print("Eccezione:", e)

    return

main()