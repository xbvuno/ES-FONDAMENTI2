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

struct sottomatrice_quad {
    int size;
    int* address;
};

bool is_inside_mat_quad(int n, int i, int j) {
    return 0 <= i && i < n &&  0 <= j && j < n;
}

int mat_coord(int n, int i, int j) {
    return n * i + j;
}

sottomatrice_quad trova_sottomatrice_quad(int* mat, int n, int coord) {
    sottomatrice_quad res = {1, mat + coord};
    int value = *(mat + coord);                 // il valore in posizione coord nella matrice mat
    cout << "\nat [i = " << coord / n << "][j = " << coord % n << "] searching " << value << endl;
    for (int size = 2; size <= n; size++) {     // per un quadrato largo 2, 3 ... max n
        cout << "\tSQUARE SIZE: " << size << endl; 
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if (i == 0 && j == i) { // ovvio che value sarà uguale a found_value[0][0]
                    continue;           // continua il for skippando questo step
                }
                int found_value = *(mat + coord + mat_coord(n, i, j));
                if (!is_inside_mat_quad(n, i, j)) {
                    cout << "\t\tEXIT: [i + " << mat_coord(n, i, j) / n << "][j + " << mat_coord(n, i, j) % n << "] outside bounderies\nreturning..." << endl;
                    return res;
                }
                if (found_value != value) {
                    cout << "\t\tBAD:  [i + " << mat_coord(n, i, j) / n << "][j + " << mat_coord(n, i, j) % n << "] = " << found_value << "\nreturning..." << endl;
                    return res;
                } else {
                    cout << "\t\tGOOD: [i + " << mat_coord(n, i, j) / n << "][j + " << mat_coord(n, i, j) % n << "] = " << value << endl;
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
    for(int i=0; i < n; i++) {              // è inutile iniziare a controllare dall'ultima riga
        for(int j=0; j < n; j++) {          // stesso per la colonna
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
        {1,   -4,   7,   7,   7},
        {4,   32,   7,   7,   7},
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