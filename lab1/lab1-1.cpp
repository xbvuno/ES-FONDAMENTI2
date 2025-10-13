/*
Scrivere un programma c++ che, presa in input una sequenza di
numeri interi terminata da 0, memorizzi il minimo in una variabile min,
il massimo in una variabile max e stampi infine la differenza tra i due
valori salvati (max – min)

Extra (per casa) : implementare una versione ricorsiva dello stesso programma
*/

#include <iostream>

using namespace std;

int main() {
    int max = 0, min = 0, x;
    cout << "Inserisci valori o '0' per terminare.\n";
    cout << "\tIns. valore: ";
    cin >> x;

    while (x != 0) {

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
            return 2;
        }
    }

    if (!max) {
        cout << "\nNon è stato inserito nessun valore.";
        return 1;
    }

    cout << "max: " << max << endl;
    cout << "min: " << min << endl;
    cout << "(max - min): " << (max - min) << endl;

    return 0;
}