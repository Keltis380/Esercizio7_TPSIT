#include <iostream>
#include <string>
using namespace std;

class Sensore {
protected:
    string nome;
    int grezzo;

public:
    Sensore(string n, int g) : nome(n), grezzo(g) {}
    virtual ~Sensore() {}
    string getNome() const { return nome; }
    virtual double valore() const = 0;
    virtual string unita() const = 0;
    virtual bool inAllarme() const { return false; }
};

class Temperatura : public Sensore {
public:
    Temperatura(string n, int g) : Sensore(n, g) {}
    double valore() const override { return grezzo / 10.0; }
    string unita() const override { return "gradi C"; }
    bool inAllarme() const override { return valore() > 30; }
};

class Umidita : public Sensore {
public:
    Umidita(string n, int g) : Sensore(n, g) {}
    double valore() const override { return grezzo * 100.0 / 1023; }
    string unita() const override { return "%"; }
    bool inAllarme() const override { return valore() > 70; }
};

class Luce : public Sensore {
public:
    Luce(string n, int g) : Sensore(n, g) {}
    double valore() const override { return grezzo; }
    string unita() const override { return "lux"; }
};

class Centralina {
    Sensore* sensori[10];
    int numero;

public:
    Centralina() : numero(0) {}

    bool aggiungi(Sensore* s) {
        if (numero >= 10) return false;
        sensori[numero] = s;
        numero++;
        return true;
    }

    int report() const {
        int allarmi = 0;

        for (int i = 0; i < numero; i++) {
            cout << sensori[i]->getNome() << ": "<< sensori[i]->valore() << " "<< sensori[i]->unita();

            if (sensori[i]->inAllarme()) {
                cout << " <-- ALLARME";
                allarmi++;
            }

            cout << endl;
        }

        return allarmi;
    }
};

int main() {
    Temperatura t1("Temp. aula", 215);
    Temperatura t2("Temp. server", 342);
    Umidita u1("Umidita bagno", 818);
    Luce l1("Luce corridoio", 350);
    Centralina c;
    c.aggiungi(&t1);
    c.aggiungi(&t2);
    c.aggiungi(&u1);
    c.aggiungi(&l1);

    int allarmi = c.report();
    cout << "Sensori in allarme: " << allarmi << endl;

    return 0;
}