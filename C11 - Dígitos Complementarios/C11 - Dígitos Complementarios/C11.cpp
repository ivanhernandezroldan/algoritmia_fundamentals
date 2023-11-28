#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int invertirNumero(const int& numero, int& contadorDigitos) {
    if (numero / 10 == 0) {
        contadorDigitos = 0;
        return numero;
    }
    else {
        int primerosDigitosInvertidos = invertirNumero(numero / 10, contadorDigitos);
        contadorDigitos++;
        int ultimoDigito = numero % 10;
        return ultimoDigito * pow(10, contadorDigitos) + primerosDigitosInvertidos;
    }
}

int complementarNumero(const int& numero) {
    if (numero / 10 == 0) {
        int complementario = 9 - numero;
        return complementario;
    }
    else {
        int digitosComplementados = complementarNumero(numero / 10);
        int ultimoDigito = numero % 10;
        int complementarioUltimoDigito = 9 - ultimoDigito;
        return digitosComplementados*10 + complementarioUltimoDigito;
    }
}

void resuelveCaso() {
    int numero;
    cin >> numero;
    int numComplementario = complementarNumero(numero);
    int contadorDigitos;
    int inversoComplementario = invertirNumero(numComplementario, contadorDigitos);
    cout << numComplementario << " " << inversoComplementario << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}