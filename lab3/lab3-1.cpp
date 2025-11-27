/*
Implementare una classe Programmatore che conservi i campi: 
    - id 
    - eta
    - stipendio 
    - anni_esperienza (interi positivi) 
    - senior (bool)

Si richiede di implementare:
    - Getter e setter per tutti I campi
    - Costruttore con parametri
    - Operatori di input e output (<< e >>)
    - Operatori di confronto == e != (guardando l’id)

Si richiede di implementare una classe GestoreProgrammatori, 
che contiene al suo interno un vettore di Programmatore. 

    Per questa classe si richiede di implementare un costruttore 
    con parametri e uno senza parametri 

    in aggiunta ai seguenti metodi:

        - Un metodo assumi_programmatore che riceva un programmatore come parametro
        e lo aggiunga al vettore di quelli già esistenti

        - Un metodo licenzia_programmatore che rimuova il programmatore ricevuto dal
        vettore dei programmatori

        - Un metodo max_stip_cat che restituisca lo stipendio massimo per una data
        categoria in input (junior o senior)

        - Un metodo senior_meno_esperto che restituisca il programmatore senior con
        meno anni di esperienza

        - Un metodo promuovi_a_senior che promuova a senior tutti i junior i cui anni di
        esperienza siano maggiori del senior meno esperto
*/

#include <iostream>
#include <string>
#include <algorithm> /* find */
#include <list>
using namespace std;

class Programmatore {
private:
    unsigned id;
    unsigned eta;
    unsigned stipendio;
    unsigned anni_esperienza;
    bool senior;

public:
    Programmatore(unsigned id, unsigned eta, unsigned stipendio, unsigned anni_esperienza, bool senior) {
        this->id = id;
        this->eta = eta;
        this->stipendio = stipendio;
        this->anni_esperienza = anni_esperienza;
        this->senior = senior;
    }

    void setId(unsigned new_id) { id = new_id; }
    unsigned getId() { return id; }

    void setEta(unsigned new_eta) { eta = new_eta; }
    unsigned getEta() { return eta; }

    void setStipendio(unsigned new_stipendio) { stipendio = new_stipendio; }
    unsigned getStipendio() { return stipendio; }

    void setAnniEsperienza(unsigned new_anni_esperienza) { anni_esperienza = new_anni_esperienza; }
    unsigned getAnniEsperienza() { return anni_esperienza; }

    void setSenior(bool new_senior) { senior = new_senior; }
    bool isSenior() {  return senior; }

    bool operator==(Programmatore other) {
        return id == other.id;
    }

    bool operator!=(Programmatore other) {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Programmatore& p) {
        os << "Programmatore(" << p.id << ")";
        return os;
    }

    friend istream& operator>>(istream& is, Programmatore& p) {
        cout << "Programmatore:\n\tID: ";
        is >> p.id;
        cout << "\tEta': ";
        is >> p.eta;
        cout << "\tStipendio: ";
        is >> p.stipendio;
        cout << "\tAnni Esperienza: ";
        is >> p.anni_esperienza;
        cout << "\t è Senior? (Y/N)";
        string s;
        is >> s;
        while (s.length() > 1 || string("yYnN").find(s) == string::npos) {
            cout << "\tInput errato, riprova: ";
            is >> s;
        }
        p.senior = s[0] == 'y' || s[0] == 'Y';

        return is;
    }
    
};

class GestoreProgrammatori {
private:
    list<Programmatore> programmatori;

public: 
    GestoreProgrammatori() {}
    GestoreProgrammatori(list<Programmatore> programmatori) {
        this->programmatori = programmatori;
    }

    void assumi_programmatore(Programmatore p) {
        programmatori.push_back(p);
    }
    
    list<Programmatore> getProgrammatori() const {
        return programmatori;
    }

    bool licenzia_programmatore(Programmatore p) {
        for (auto iter = programmatori.begin(); iter != programmatori.end(); iter++) {
            if (*iter == p) {
                programmatori.erase(iter);
                return true;
            }
        }
        return false;
    }

    unsigned max_stip_cat(bool amoung_seniors) {
        unsigned max = 0;
        for (Programmatore p : programmatori) {
            if (amoung_seniors && !p.isSenior()) {
                continue;
            }
            if (!amoung_seniors && p.isSenior()) {
                continue;
            }
            if (p.getStipendio() > max) {
                max = p.getStipendio();
            }
        }
        return max;
    }

    Programmatore senior_meno_esperto() {

        Programmatore p_min(0, 0, 0, 0, false);
        bool finded_first = false;

        for (Programmatore p : programmatori) {
            if (!p.isSenior()) {
                continue;
            }
            if (!finded_first) {
                p_min = p;
                finded_first = true;
                continue;
            }
            if (p.getAnniEsperienza() < p_min.getAnniEsperienza()) {
                p_min = p;
            }
        }
        return p_min;
    }

    void promuovi_a_senior() {
        Programmatore p_min = senior_meno_esperto();
        for (Programmatore& p : programmatori) {
            if (p.isSenior()) {
                continue;
            }
            if (p.getAnniEsperienza() > p_min.getAnniEsperienza()) {
                p.setSenior(true);
            }
        }
    }
};



int main() {
    GestoreProgrammatori gestore;
    int scelta;

    do {
        cout << "\n--- Menu Gestore Programmatori ---\n";
        cout << "1. Assumi un nuovo programmatore\n";
        cout << "2. Licenzia un programmatore\n";
        cout << "3. Mostra stipendio massimo senior\n";
        cout << "4. Mostra stipendio massimo non senior\n";
        cout << "5. Promuovi a senior programmatori esperti\n";
        cout << "6. Visualizza tutti i programmatori\n";
        cout << "0. Esci\n";
        cout << "Scelta: ";
        cin >> scelta;

        switch (scelta) {
            case 1: {
                Programmatore p(0,0,0,0,false);
                cin >> p; // usa l'operatore >> della classe Programmatore
                gestore.assumi_programmatore(p);
                cout << "Programmatore assunto.\n";
                break;
            }
            case 2: {
                unsigned p_id;
                cout << "Programmatori:\n";

                for (Programmatore& p : gestore.getProgrammatori()) {
                    
                }
                cout << "Inserisci il ID del programmatore da licenziare:\n";
                cin >> p_id;
                Programmatore p(p_id, 0, 0, 0, false);
                if (gestore.licenzia_programmatore(p)) {
                    cout << "Programmatore licenziato.\n";
                } else {
                    cout << "Programmatore non trovato.\n";
                }
                break;
            }
            case 3:
                cout << "Stipendio massimo senior: " << gestore.max_stip_cat(true) << endl;
                break;
            case 4:
                cout << "Stipendio massimo non senior: " << gestore.max_stip_cat(false) << endl;
                break;
            case 5:
                gestore.promuovi_a_senior();
                cout << "Promozioni effettuate.\n";
                break;
            case 6: {
                cout << "\nLista programmatori:\n";
                for (Programmatore& p : gestore.getProgrammatori()) {
                    cout << p << " | Eta: " << p.getEta()
                         << " | Stipendio: " << p.getStipendio()
                         << " | Anni esperienza: " << p.getAnniEsperienza()
                         << " | Senior: " << (p.isSenior() ? "Si" : "No") << endl;
                }
                break;
            }
            case 0:
                cout << "Uscita dal programma.\n";
                break;
            default:
                cout << "Scelta non valida!\n";
        }

    } while (scelta != 0);

    return 0;
}