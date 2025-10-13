/*
Scrivere una funzione ricorsiva che riceva in input un
array di N numeri interi positivi, e faccia quanto segue:
    - Legge un elemento dell’array (la prima volta legge
      l’elemento in posizione 1) e lo confronta con il
      precedente:
        - Se il numero letto è minore del precedente continua a leggere
        - Se il numero letto è Maggiore o uguale del precedente, decrementa il numero di 1 e
          ricomincia a leggere dalla posizione 1
    - La funzione termina quando “non ha più niente da
      leggere” restituendo la somma dei valori letti
*/

#include <iostream>
#include <cstdlib> // per numeri random
#include <time.h> // per il seed dei random

using namespace std;


void print_array(int array[], int n) {
    for (int i = 0; i < n; i++) {
        cout << array[i] << ", ";
    }
    cout << endl;
}

int funny_stuff(int array[], int n) {
    int somma = 0;
    for (int i = 1; i < n; i++) {
        if (array[i] >= array[i - 1]) {
            array[i]--;
            return funny_stuff(array, n);
        } else {
            somma += array[i];
        }
    }
    return somma + array[0];
}

int main() {
    srand(time(0));  // imposta il seed di generazione numeri randomici

    const int N = 8;
    const int MAX_RAND = 16;
    const int MIN_RAND = 1;

    int array[N];
    for (int i = 0; i < N; i++) {
        array[i] = rand() % (MAX_RAND - MIN_RAND) + MIN_RAND;
    }
    print_array(array, N);
    int somma = funny_stuff(array, N);
    cout << "\nSOMMA: " << somma;
    

    return 0;
}