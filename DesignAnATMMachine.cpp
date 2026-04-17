#include <vector>
using namespace std;

class ATM {
private:
    vector<long long> cantidadBilletes;
    vector<int> denominaciones;

public:
    ATM() {
        cantidadBilletes = vector<long long>(5, 0);
        denominaciones = {20, 50, 100, 200, 500};
    }

    void deposit(vector<int> cantidadDepositada) {
        for (int indice = 0; indice < 5; indice++) {
            cantidadBilletes[indice] += cantidadDepositada[indice];
        }
    }

    vector<int> withdraw(int monto) {
        vector<int> billetesEntregados(5, 0);
        int montoRestante = monto;

        for (int indice = 4; indice >= 0; indice--) {
            long long maximoBilletesPosibles = montoRestante / denominaciones[indice];
            long long billetesAUsar = min(cantidadBilletes[indice], maximoBilletesPosibles);

            billetesEntregados[indice] = (int)billetesAUsar;
            montoRestante -= (int)(billetesAUsar * denominaciones[indice]);
        }

        if (montoRestante != 0) {
            return {-1};
        }

        for (int indice = 0; indice < 5; indice++) {
            cantidadBilletes[indice] -= billetesEntregados[indice];
        }

        return billetesEntregados;
    }
};
