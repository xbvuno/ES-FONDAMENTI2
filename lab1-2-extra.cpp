/*
Scrivere una funzione che, dato un numero intero positivo n, divida n per 2
fino ad arrivare a 0, contando quante volte la divisione ha dato come resto 1

Esempio per n = 36: 
    36/2 = 18 resto 0
    18/2 = 9 resto 0
    9/2 = 4 resto 1
    4/2 = 2 resto 0
    2/2 = 1 resto 0
    1/2 = 0 resto 1 
Esco e restituisco 2

Extra (per casa) : implementare una versione ricorsiva della stessa funzione
*/

#include <iostream>

using namespace std;

int conta_resti(int n, int count) {
    if (n == 0) {
        return count;
    }
    cout << '\t' << n << " / 2 \t= ";
    bool resto = n % 2;
    n /= 2;
    cout << n << " resto " << resto << endl;
    return conta_resti(n, count + resto);
}

int main() {
    int count = 0, n;
    cout << "Inserisci valore da dividere:";
    cin >> n;

    int resti = conta_resti(n, 0);

    cout << "Numero di resti: " << resti << endl;

    return 0;
}