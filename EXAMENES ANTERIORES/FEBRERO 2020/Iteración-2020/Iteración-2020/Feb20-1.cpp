#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
// P = {longSegmentoMasLargo = 0}
void longuitudSegmento(const vector<int> &v, int & longSegmentoMasLargo) {
    int i = 0;
    int contadorSubSegmentoEstrictamenteCreciente;
    int elemAnterior;
    int longSegmento;
    while (i < v.size()) {
        if (i == 0) {
            contadorSubSegmentoEstrictamenteCreciente = 1;
            longSegmento = 1;
            if (longSegmento > longSegmentoMasLargo) {
                longSegmentoMasLargo = longSegmento;
            }
        }
        else {
            if (v[i] > elemAnterior) {
                contadorSubSegmentoEstrictamenteCreciente++;
                longSegmento++;
                if (contadorSubSegmentoEstrictamenteCreciente < 3) {
                    if (longSegmento > longSegmentoMasLargo) {
                        longSegmentoMasLargo = longSegmento;
                    }
                }
                else {
                    contadorSubSegmentoEstrictamenteCreciente = 2;
                    longSegmento = 2;
                }
            }
            else {
                contadorSubSegmentoEstrictamenteCreciente = 1;
                longSegmento++;
                if (longSegmento > longSegmentoMasLargo) {
                    longSegmentoMasLargo = longSegmento;
                }
            }
        }
        elemAnterior = v[i];
        i++;
    }
}
// Q = {longSegmentoMasLargo = (max p,q : 0 <= p <= q <= v.size() && (no existe j : p <= j < q - 2 : v[j] < v[j+1] < v[j+2]) : q - p)}
// I = {0 <= i < v.size() && longSegmentoMasLargo = (max p,q : 0 <= p <= q <= i + 1 && (no existe j : p <= j < q - 2 : v[j] < v[j+1] < v[j+2]) : q - p) && elemAnterior = v[i - 1] <=> i > 0 && }
// Coste: El coste en tiempo de esta función es O(n) donde n es v.size()
// Cota: v.size() - i

void resuelveCaso() {
    int numElems;
    cin >> numElems;
    vector<int> v;
    for (int i = 0; i < numElems; i++) {
        int elem; 
        cin >> elem;
        v.push_back(elem);
    }
    int longSegmentoMasLargo = 0;
    longuitudSegmento(v, longSegmentoMasLargo);
    cout << longSegmentoMasLargo << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-Feb20-1.1.in");
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