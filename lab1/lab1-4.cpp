/*
Scrivere una funzione che (nell’ordine):

    1. Legge un intero n
    2. Legge una sequenza di caratteri di lunghezza n
    3. Legge un carattere di controllo k

Se tra i caratteri letti non è presente il carattere di controllo, la funzione
stampa l’ultimo carattere letto.

Se il carattere di controllo è presente, ne stampa il numero di occorrenze.
*/

#include <iostream>
#include <vector>


using namespace std;


int main() {
    int n;
    cout << "Ins. n: ";
    cin >> n;

    char sequenza[n];

    cout << "Ins. " << n << " caratteri (separati da spazio o invio):\n";
    for (int i = 0; i < n; i++) {
        cin >> sequenza[i];
    }

    char k;
    cout << "Inserisci k: ";
    cin >> k;

    int occorrenze = 0;
    for (char c : sequenza) {
        if (c == k)
            occorrenze++;
    }

    if (occorrenze == 0)
        cout << "k non presente, ultimo carattere letto: " << sequenza[n - 1] << endl;
    else
        cout << k << " compare " << occorrenze << " volte." << endl;

    return 0;
}