#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
 
void encuentraNumero(const vector<int> &v, int & numMasCercano, int x, int ini, int fin) {
    int m = (fin - ini) / 2;
    if (fin - ini == 0) {
        numMasCercano = v[ini];
    }
    else if (x == v[m]) {
        numMasCercano = v[m];
    }
    else {
        if (abs(x - v[m]) < abs(v[m + 1] - x)) {
            encuentraNumero(v, numMasCercano, x, ini, m);
        }
        else if (abs(x - v[m]) > abs(v[m + 1] - x)) {
            encuentraNumero(v, numMasCercano, x, m + 1, fin);
        }
        else {
            numMasCercano = v[m];
        }    
    }
}
    

void resuelveCaso() {
    int x, n;
    cin >> x >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int elem;
        cin >> elem;
        v.push_back(elem);
    }
    int numMasCercano;
    int ini = 0;
    int fin = n - 1;
    encuentraNumero(v, numMasCercano, x, ini, fin);
    cout << numMasCercano << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-Feb18-2.1.in");
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