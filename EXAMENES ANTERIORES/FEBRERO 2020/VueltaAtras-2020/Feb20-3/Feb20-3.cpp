//NOMBRE y APELLIDOS: Iván Hérnandez Roldán
//DNI: 06619496G


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime> 

using namespace std;

void recogidaPlayas(int numPlayas, int numPersonas, int numPlayasLimpias, const vector<int>& basuraPlayas, const vector<vector<int>>& basuraRecogidaPorPersonas, int k, int& basuraRecogida, int& basuraMaximaRecogida, int& playasComplementamenteLimpias, int &maximoPlayasCompletamenteLimpias, vector<int>& marcadorBasuraRecogidaPlayas, const vector<int>& estimacion, bool &restriccionCumplida) {
    for (int i = 0; i < numPlayas; i++) {
        if (marcadorBasuraRecogidaPlayas[i] < basuraPlayas[i]) { // esValida?
            int valorAux = min(basuraRecogidaPorPersonas[k][i], basuraPlayas[i] - marcadorBasuraRecogidaPlayas[i]);
            marcadorBasuraRecogidaPlayas[i] += valorAux;
            basuraRecogida += valorAux;
            if (marcadorBasuraRecogidaPlayas[i] == basuraPlayas[i]) {
                playasComplementamenteLimpias++;
            }
            if (k == numPersonas - 1) {
                if (basuraRecogida > basuraMaximaRecogida && playasComplementamenteLimpias >= numPlayasLimpias) {
                    basuraMaximaRecogida = basuraRecogida;
                    restriccionCumplida = true;
                    if (playasComplementamenteLimpias > maximoPlayasCompletamenteLimpias) {
                        maximoPlayasCompletamenteLimpias = playasComplementamenteLimpias;
                    }
                }
            }
            else {
                if (basuraRecogida + estimacion[k] > basuraMaximaRecogida) {
                    recogidaPlayas(numPlayas, numPersonas, numPlayasLimpias, basuraPlayas, basuraRecogidaPorPersonas, k + 1, basuraRecogida, basuraMaximaRecogida, playasComplementamenteLimpias, maximoPlayasCompletamenteLimpias, marcadorBasuraRecogidaPlayas, estimacion, restriccionCumplida);
                }
            }
            if (marcadorBasuraRecogidaPlayas[i] == basuraPlayas[i]) {
                playasComplementamenteLimpias--;
            }
            marcadorBasuraRecogidaPlayas[i] -= valorAux;
            basuraRecogida -= valorAux;
        }
    }
}

void resuelveCaso() {
    int numPersonas, numPlayas, numPlayasLimpias;
    cin >> numPersonas >> numPlayas >> numPlayasLimpias;
    vector<int> basuraPlayas; // recoge los datos de la basura en cada playa
    for (int i = 0; i < numPlayas; i++) {
        int basura;
        cin >> basura;
        basuraPlayas.push_back(basura);
    }
    vector<vector<int>> basuraRecogidaPorPersonas; // recoge los datos de la basura recogida por cada persona (fila) en cada playa (columna)
    vector<int> maximaBasuraRecogidaPorPersonas; // sirve para preparar el vector<int> estimacion. En cada posicion (persona) se recoge el maximo valor de basura recogida por cada persona
    for (int i = 0; i < numPersonas; i++) {
        vector<int> persona;
        basuraRecogidaPorPersonas.push_back(persona);
        maximaBasuraRecogidaPorPersonas.push_back(0);
        for (int j = 0; j < numPlayas; j++) {
            int valor;
            cin >> valor;
            basuraRecogidaPorPersonas[i].push_back(valor);
            if (valor > maximaBasuraRecogidaPorPersonas[i]) {
                maximaBasuraRecogidaPorPersonas[i] = valor;
            }
        }
    }
    bool restriccionCumplida = false; // indica si en cada caso se ha podido cumplir la restriccion del minimo de playas limpias
    int basuraRecogida = 0; // indica la basura recogida de la solucion parcial. Inicializo a '0' porque es cota inferior.
    int basuraMaximaRecogida = 0; // indica la basura maxima recogida de la solucion mejor. Inicializo a '0' porque es cota inferior.
    int playasComplementamenteLimpias = 0; // indica el numero de playas completamente limpias de la solucion mejor. Inicializo a '0' porque es cota inferior.
    int maximoPlayasCompletamenteLimpias = 0;
    int k = 0; // indica el nivel de la solucion (la persona a la que estas asignando la playa a la que se le envia)
    vector<int> marcadorBasuraRecogidaPlayas(numPlayas, 0); // cada posicion (playa) indica el valor de la basura recogida en esa playa segun la solucion parcial construida
    vector<int> estimacion(numPersonas, -1); // cada posicion (nivel de la solucion) indica el maximo valor de basura recogida total a partir de ese nivel de la solucion
    estimacion[numPersonas - 1] = 0;
    for (int i = numPersonas - 2; i >= 0; --i) {
        estimacion[i] = estimacion[i + 1] + maximaBasuraRecogidaPorPersonas[i + 1];
    }
    recogidaPlayas(numPlayas, numPersonas, numPlayasLimpias, basuraPlayas, basuraRecogidaPorPersonas, k, basuraRecogida, basuraMaximaRecogida, playasComplementamenteLimpias, maximoPlayasCompletamenteLimpias, marcadorBasuraRecogidaPlayas, estimacion, restriccionCumplida);
    if (restriccionCumplida) {
        cout << basuraMaximaRecogida << " " << numPlayasLimpias << endl;
    }
    else {
        cout << "IMPOSIBLE" << endl;
    }
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-Feb20-3.1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    unsigned t0, t1;

    t0 = clock();
    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
    t1 = clock();

    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}