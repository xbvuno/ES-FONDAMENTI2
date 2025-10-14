/*
Scrivere una funzione ricorsiva che prenda in input:
- una matrice di interi positivi M (supporre sia già riempita),
- due interi i,j che indicano una “posizione attuale” e
- una lettera, partendo dalla cella i,j si comporti come segue:
    - X, termina l’esecuzione del programma (STOP)
    - W, fa spostare la posizione attuale verso la riga precedente (SU)
    - A, fa spostare la posizione attuale verso la colonna precedente (SINISTRA)
    - S, fa spostare la posizione attuale verso la riga successive (GIU)
    - D, fa spostare la posizione attuale verso la colonna successiva (DESTRA)
Se cerco di muovermi verso una cella «non valida», sono “caduto” e l’esecuzione termina.
Se alla fine dei comandi sono ancora sulla matrice, restituisco la somma delle celle che ho visitato.

*/

#include <iostream>
#include <cstdlib>  /* srand(), rand() */

using namespace std;

const int MAT_SIZE = 6;


void print_mat(int mat[MAT_SIZE][MAT_SIZE], int highlight_x, int highlight_y) {
    cout << "------------------------------\n\n[W|A|S|D] Spostati\n[X] Esci e Somma\n\n";
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < MAT_SIZE; j++) {
            if (j == highlight_x && i == highlight_y) {
                cout << "\033[47m" << mat[i][j] << "\033[0m ";
            } else {
                cout << mat[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << "\nInput: ";
}

bool inside_mat(int x, int y) {
    return 0 <= x && x < MAT_SIZE && 0 <= y && y < MAT_SIZE;
}

const string ALLOWED_INPUTS = "wasdx";
char validate_input() {
    char c;
    while (true) {
        cin >> c;
        c = tolower(c);
        if (cin.fail()) {
            return 'x';
        }
        for (int i=0; i < ALLOWED_INPUTS.length(); i++) {
            if (ALLOWED_INPUTS[i] == c) {
                return c;
            }
        }
        cout << "Retry: ";
    }
}

int move_and_sum(int mat[MAT_SIZE][MAT_SIZE], int x, int y, char action, int sum) {
    if (action == 'x') {
        return sum;
    }
    sum += mat[y][x];
    switch(action) {
        case 'w':
            y -= 1;
            break;
        case 's':
            y += 1;
            break;
        case 'a':
            x -= 1;
            break;
        case 'd':
            x += 1;
            break;
    }
    if(!inside_mat(x, y)) {
        cout << "Caduto fuori!";
        return sum;
    } 
    print_mat(mat, x, y);
    char input = validate_input();
    return move_and_sum(mat, x, y, input, sum);
}

int main() {
    int mat[MAT_SIZE][MAT_SIZE];

    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < MAT_SIZE; j++) {
            mat[i][j] = 10 + rand() % (100 - 10); // da 10..99
        }
    }

    int starting_pos_x = rand() % MAT_SIZE, starting_pos_y = rand() % MAT_SIZE;

    print_mat(mat, starting_pos_x, starting_pos_y);
    char first_input = validate_input();
    int somma = move_and_sum(mat, starting_pos_x, starting_pos_y, first_input, 0);
    cout << "\n\nSOMMA: " << somma;
    return 0;
}
