//NOMBRE y APELLIDOS: Iván Hernández Roldán 


#include <iostream>
#include <fstream>
#include <cmath> // si no incluyo esto en el domjudge me da error !!!!!!!!!!!
using namespace std;



int invertirNumero(const int & numero, int & contadorDigitos){ //Coste lineal
    if (numero / 10 == 0) {
        contadorDigitos = 0;
        return numero;
    }
    else {
        int restoDigitosInvertidos = invertirNumero(numero / 10, contadorDigitos);      
        contadorDigitos++;
        int ultimoDigito = numero % 10;
        return ultimoDigito * pow(10,contadorDigitos) + restoDigitosInvertidos;
    }
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numero;
    std::cin >> numero;
    // Resolvemos
    while (numero != 0) {
        int contadorDigitos;
        int numeroInvertido = invertirNumero(numero, contadorDigitos);
        cout << numeroInvertido << endl;
        cin >> numero;
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}