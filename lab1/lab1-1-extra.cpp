/*
Scrivere un programma c++ che, presa in input una sequenza di
numeri interi terminata da 0, memorizzi il minimo in una variabile min,
il massimo in una variabile max e stampi infine la differenza tra i due
valori salvati (max – min)

Extra (per casa) : implementare una versione ricorsiva dello stesso programma
*/

#include <iostream>

using namespace std;

int maxmin(int x, int min, int max) {
    if (x == 0) {
        return max - min;
    }

    if (max == 0 || max < x) {
        max = x;
    }

    if (min == 0 || min > x) {
        min = x;
    }

    cout << "\tIns. valore: ";
    cin >> x;

    if (cin.fail()) {
        cout << "\nErrore in input" << endl;
        return 0;
    }

    return maxmin(x, min, max);
}

int main() {
    int max = 0, min = 0, x, max_less_min;
    cout << "Inserisci valori o '0' per terminare.\n";
    cout << "\tIns. valore: ";
    cin >> x;

    max_less_min = maxmin(x, min, max);

    cout << "(max - min): " << max_less_min << endl;

    return 0;
}