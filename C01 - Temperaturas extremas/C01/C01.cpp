#include <iostream>
#include <fstream>
#include<vector>
using namespace std;

// P = {numPicos = 0 && numValles = 0}
void temperaturasExtremas(const vector<int> &temperaturas, int &numPicos, int &numValles) {
    int i = 0;
    while (i < temperaturas.size()) {
        if (i != 0 && i != temperaturas.size() -1) {
            if (temperaturas[i - 1] > temperaturas[i] && temperaturas[i] < temperaturas[i + 1]) {
                numValles++;
            }
            else if (temperaturas[i - 1] < temperaturas[i] && temperaturas[i] > temperaturas[i + 1]) {
                numPicos++;
            }
        }
        i++;

    }
}
// Q = {numPicos = (#j : 0 < j < temperaturas.size() - 1 : v[j - 1] < v[j] > v[j + 1]) && numValles = (#j : 0 < j < temperaturas.size() - 1 : v[j - 1] > v[j] < v[j + 1])}
// Esta mal => I = {0 <= i <= temperaturas.size() && numPicos = (#j : 0 < j < i : v[j - 1] < v[j] > v[j + 1]) && numValles = (#j : 0 < j < i - 1 : v[j - 1] > v[j] < v[j + 1])}
// Cota: i
// Coste: El coste en tiempo de temperaturasExtremas es de O(n) donde n es temperaturas.size()

void resuelveCaso() {
    int numTemperaturas;
    cin >> numTemperaturas;
    vector<int> temperaturas;
    for (int i = 0; i < numTemperaturas; i++) {
        int temperatura;
        cin >> temperatura;
        temperaturas.push_back(temperatura);
    }
    int numPicos = 0;
    int numValles = 0;
    temperaturasExtremas(temperaturas, numPicos, numValles);
    cout << numPicos << " " << numValles << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-C01.1.in");
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