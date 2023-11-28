#include <iostream>
#include<vector>
#include <fstream>
using namespace std;

vector<int> nuevaCabana(const vector<int> &v, int l, int &secuenciaMasLarga) {
    vector<int> comienzoEspaciosApropiados;
    int i = v.size() - 1;
    int valorMaximo = 0;
    int contadorRepetidos = 0;
    int anteriorValor = v[i];
    bool insertadoPosicion = false;
    while (i >= 0) {
        if (v[i] >= valorMaximo) {
            valorMaximo = v[i];
            if (v[i] == anteriorValor) {
                contadorRepetidos++;
            }
            else {
                contadorRepetidos = 1;
                insertadoPosicion = false;
            } 
        }
        else {
            contadorRepetidos = 0;
            insertadoPosicion = false;
        }
        if (contadorRepetidos >= l) {
            if (!insertadoPosicion) {
                comienzoEspaciosApropiados.push_back(i + contadorRepetidos - 1);
                insertadoPosicion = true;
            }
            if (contadorRepetidos > secuenciaMasLarga) {
                secuenciaMasLarga = contadorRepetidos;
            }
        }
        anteriorValor = v[i];
        i--;
    }
    return comienzoEspaciosApropiados;
}

bool resuelveCaso() {
    if (cin.eof()) {
        return false;
    }
    int numElems, l;
    cin >> numElems >> l;
    vector<int> v; 
    for (int i = 0; i < numElems; i++) {
        int elem; 
        cin >> elem;
        v.push_back(elem);
    }
    int secuenciaMasLarga = 0;
    if (v.size() > 1) {
        vector<int> comienzoEspaciosApropiados = nuevaCabana(v, l, secuenciaMasLarga);
        cout << secuenciaMasLarga << " " << comienzoEspaciosApropiados.size() << " ";
        for (int i : comienzoEspaciosApropiados) {
            cout << i << " ";
        }
        cout << endl;
    }
    else {
        cout << "0 0" << endl;
    }
    
    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("sample-C08.1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}