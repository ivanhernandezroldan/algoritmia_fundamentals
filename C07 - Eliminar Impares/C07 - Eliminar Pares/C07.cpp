#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void eliminaImpares(vector<int>& v) {
    int i = 0;
    int contador = 0;
    while () {
        if (v[i] % 2 == 1) {
            contador++;
            int aux = v[i];
            v[i] = v[v.size() - 1];
            v[v.size() - 1] = aux;
            v.pop_back();
        }
        else {
            if (contador != 0) {
                int aux = v[i];
                v[i] = v[i + contador];
                v[i + contador] = aux;
                contador--;
            }
            else {
                i++;
            }
        }
    }
}

bool resuelveCaso() {
    int numElems;
    cin >> numElems;
    if (numElems == -1) {
        return false;
    }
    vector<int> v;
    for (int i = 0; i < numElems; i++) {
        int elem;
        cin >> elem;
        v.push_back(elem);
    }
    eliminaImpares(v);
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("sample-C07.1.in");
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