#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

void crecientePorLosPelosYDivertido(const vector<int>& v, bool& esCrecientePorLosPelos, bool& esdDivertido, int d) {
    int i = 0;
    unordered_map<int, int> marcadorRepeticiones;
    int maximasRepeticiones = 0;
    while (i < v.size() && esCrecientePorLosPelos && esdDivertido) {
        if (i != 0) {
            // esdDivertido?
            if (marcadorRepeticiones.count(v[i]) == 0) {
                marcadorRepeticiones.insert({ v[i], 1 });
                if (maximasRepeticiones < marcadorRepeticiones[v[i]]) {
                    maximasRepeticiones = marcadorRepeticiones[v[i]];
                }
            }
            else {
                marcadorRepeticiones[v[i]] += 1;
                if (maximasRepeticiones < marcadorRepeticiones[v[i]]) {
                    maximasRepeticiones = marcadorRepeticiones[v[i]];
                }
                if (d < maximasRepeticiones) {
                    esdDivertido = false;
                }
            }

            // esCrecientePorLosPelos?
            if (v[i - 1] > v[i]) {
                esCrecientePorLosPelos = false;
            }
            else if (v[i] - v[i - 1] > 1) {
                esCrecientePorLosPelos = false;
            }
        }
        else {
            // esdDivertido?
            marcadorRepeticiones.insert({ v[i], 1 });
            if (maximasRepeticiones < marcadorRepeticiones[v[i]]) {
                maximasRepeticiones = marcadorRepeticiones[v[i]];
            }
            if (d < maximasRepeticiones) {
                esdDivertido = false;
            }
        }
        i++;
    }
}

void resuelveCaso() {
    int d;
    cin >> d;
    int numElems;
    cin >> numElems;
    vector<int> v;
    for (int i = 0; i < numElems; i++) {
        int elem;
        cin >> elem;
        v.push_back(elem);
    }
    bool esCrecientePorLosPelos = true;
    bool esdDivertido = true;
    crecientePorLosPelosYDivertido(v, esCrecientePorLosPelos, esdDivertido, d);
    if (esCrecientePorLosPelos && esdDivertido) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-C06.1.in");
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