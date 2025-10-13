/*
Data una matrice quadrata di numeri interi allocata in memoria dinamica,
scrivere un programma che identifichi la più grande sottomatrice quadrata di elementi uguali 
e assegni ad un puntatore il primo elemento (in alto a sinistra) di tale sottomatrice, 
ritornando la dimensione della sottomatrice trovata.

Il programma deve essere in grado di stampare in output (nel main):
    - la dimensione della sottomatrice trovata,
    - le coordinate del primo elemento della sottomatrice (in alto a sinistra)
    - il valore “uguale” trovato.

Nota: se non esiste una sottomatrice quadrata uguale di dimensione superiore o uguale a 2, ogni cella della matrice rappresenta una
sottomatrice quadrata di dimensione 1.
*/

#include <iostream>

using namespace std;

struct sottomatrice_quad { // questo struct ci serve perchè sarà necessario ritornare 2 valori diversi, l'indirizzo e la dimensione.
    int size;
    int* address;
};

bool is_inside_mat_quad(int n, int i, int j) {  // funzione solo per controllare se gli indici scelti fanno parte della matrice
    return 0 <= i && i < n &&  0 <= j && j < n;
}

int mat_coord(int n, int i, int j) {
    return n * i + j;                       // funzione importantissima: sfruttando gli indirizzi, la matrice non diventa altro che un singolo array con tutti i valori uno dopo l'altro.
}                                           // per selezionare una posizione nella matrice, per esempio [2][3] bisogna moltiplicare i * n, così da posizionarci sulla riga giusta (2 * 5 = 10)
                                            // e aggiungere il valore di j (10 + 3 = 13), infatti, in una matrice 5x5, contando colonna per colonna, l'oggetto nella terza riga e quarta colonna sarà nella 
                                            // 13esima posizione


sottomatrice_quad trova_sottomatrice_quad(int* mat, int n, int starting_coord) {
    sottomatrice_quad res = {1, mat + starting_coord};          // inizializza una submatrice, size = 1, e indirizzo = a quello di partenza
    int value = *(mat + starting_coord);                        // il valore in posizione coord nella matrice mat
    for (int size = 2; size <= n; size++) {                     // per un quadrato largo 2, 3 ... max n
        for(int i = 0; i < size; i++) {                         // controlla i valori del quadrato attuale
            for(int j = 0; j < size; j++) {
                if (i == 0 && j == i) {         // ovvio che value sarà uguale a found_value[0][0]
                    continue;                   // continua il for skippando questo step
                }
                int found_value = *(mat + starting_coord + mat_coord(n, i, j));    // il valore in posizione coord nella matrice mat + un offest di [i][j]
                if (!is_inside_mat_quad(n, i, j) || found_value != value) {       // controlla se i e j sono dentro la matrice e che il valore appena trovato e uguale a value, altrimenti, ritorna l'ultimo risultato ottenuto.
                    return res;
                }
            }
        }
        res.size++;
    }
    return res;
}

sottomatrice_quad trova_max_sottomatrice_quad(int* mat, int n) {
    sottomatrice_quad res = {0, nullptr};
    for(int i=0; i < n - 1; i++) {              // è inutile iniziare a controllare dall'ultima riga
        for(int j=0; j < n - 1; j++) {          // stesso per la colonna
            sottomatrice_quad found = trova_sottomatrice_quad(mat, n, mat_coord(n, i, j));
            if (found.size > res.size) {
                res = found;
            }
        }
    }
    return res;
}

void stampa_mat_quad(int* mat, int n) {
    for(int i=0; i < n; i++) {
        for(int j=0; j < n; j++) {
            cout << *(mat + mat_coord(n, i, j)) << "\t ";
        }
        cout << endl;
    }
}

int main() {
    const int n = 5;
    int mat[n][n] = {
        {7,    3,  21,  -7,  32},
        {8,    9,   7,   7,   7},
        {1,   -4,   1,   2,   7},
        {4,   32,   1,   1,   7},
        {91, -43,   8,  -7,  -1}
    };
    sottomatrice_quad result = trova_max_sottomatrice_quad(*mat, n);

    cout << "MATRICE (SIZE:" << n << "):\n\n"; 
    stampa_mat_quad(*mat, n);

    cout << "\nSOTTOMATRICE QUADRATA TROVATA:" << endl;
    cout << "\tSIZE: " << result.size << endl;
    cout << "\tFIRST VALUE ADDRESS: " << result.address << endl;
    cout << "\tVALUE: " << *result.address << endl;

    return 0;
}