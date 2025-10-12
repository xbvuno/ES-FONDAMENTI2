/*
➢  Scrivere una funzione scambia che, date in input due variabili, ne
    scambi il contenuto. La funzione non deve avere valori di ritorno.

➢  Scrivere una funzione eleva che, presi in input due numeri interi x e
    y, calcoli la potenza x^y e la restituisca.

➢  Scrivere un programma che, prendendo in input tre numeri interi:
    a, b, c, che calcoli a^b e b^c. 
    Se è vero che a^b > b^c i valori di a e b vanno scambiati
*/

#include <iostream>

using namespace std;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

int pow(int n, int exp) {
    int v = n;
    if (exp == 0) {
        return 1;
    }
    if (exp == 1) {
        return n;
    }
    while (exp > 1) {
        v*=n;
        exp--;
    }
    return v;
}


int main() {
    int a, b, c;
    cout << "Ins. a:";
    cin >> a;
    cout << "Ins. b:";
    cin >> b;
    cout << "Ins. c:";
    cin >> c;
    
    int a_pow_b = pow(a, b);
    int b_pow_c = pow(b, c);

    
    cout << "a^b: " << a_pow_b << endl;
    cout << "b^c: " << b_pow_c << endl << endl;

    if (a_pow_b > b_pow_c) {
        swap(a, b);
    }

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    return 0;
}