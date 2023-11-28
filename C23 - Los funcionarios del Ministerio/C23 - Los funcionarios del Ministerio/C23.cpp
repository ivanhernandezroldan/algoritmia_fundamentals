//NOMBRE y APELLIDOS: Iván Hernández Roldán

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void funcionariosMinisterio(const vector<vector<int>> &tiempos, const vector<int> &estimacion, vector<bool> & marcador, int numFuncionarios, int numTrabajos, int k, int tiempoParcial, int & tiempoMejor) {
    for (int i = 0; i < numTrabajos; i++) {
        if (!marcador[i]) { // Es valida?
            tiempoParcial += tiempos[k][i];
            marcador[i] = true;
            if (k == numFuncionarios - 1) { // Es solucion?
                if (tiempoParcial < tiempoMejor) {
                    tiempoMejor = tiempoParcial;
                }
            }
            else {
                if (estimacion[k] + tiempoParcial < tiempoMejor) { // Poda de optimizacion
                    funcionariosMinisterio(tiempos, estimacion, marcador, numFuncionarios, numTrabajos, k + 1, tiempoParcial, tiempoMejor);
                }
            }
            tiempoParcial -= tiempos[k][i];
            marcador[i] = false;
        }
    }
}

void resuelveCaso(int numFuncionarios, int numTrabajos) {
    // Recojo datos
    vector<vector<int>> tiempos;
    vector<int> mejoresTiempos;
    for (int i = 0; i < numFuncionarios; i++) {
        vector<int> funcionario;
        tiempos.push_back(funcionario);
        mejoresTiempos.push_back(10001); // Lo inicializo con una cota superior correcta
        for (int j = 0; j < numTrabajos; j++) {
            int dato;
            cin >> dato;
            tiempos[i].push_back(dato);
            if (dato < mejoresTiempos[i]) {
                mejoresTiempos[i] = dato;
            }
        }
    }
    // Preparo la poda de optimizacion. Para la poda de optimizacion utilizare un vector<int> estimacion de numFuncionarios posiciones (1 para cada funcionario) donde cada posicion sea el tiempo total que tardan los funcionarios no asignados en realizar su tarea que menos tiempo le cuesta
    vector<int> estimacion;
    for (int i = 0; i < numFuncionarios; i++) {
        estimacion.push_back(0);
        for (int j = i + 1; j < mejoresTiempos.size(); j++)
            estimacion[i] += mejoresTiempos[j];
    }
    // Preparo más variables de la vuelta atras
    int tiempoParcial = 0; // Variable de entrada. Indica el tiempo que tardaran los funcionarios en realizar los trabajos asignados de la solucion parcial
    int tiempoMejor = 10001 * numFuncionarios; // Variable de entrada salida (la inicializo con una cota superior). Indica el mejor tiempo, conseguido por una solucion final, que tardaran los funcionarios en realizar los trabajos asignados
    int k = 0; // Indicará el funcionario que está eligiendo trabajo
    vector<bool> marcador;
    for (int i = 0; i < numTrabajos; i++) {
        marcador.push_back(false);
    }
    // Llamada vuelta atras
    funcionariosMinisterio(tiempos, estimacion, marcador, numFuncionarios, numTrabajos, k, tiempoParcial, tiempoMejor);
    cout << tiempoMejor << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-C23.1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numFuncionarios, numTrabajos;
    cin >> numFuncionarios;
    numTrabajos = numFuncionarios;
    while (numFuncionarios != 0) {
        resuelveCaso(numFuncionarios, numTrabajos);
        cin >> numFuncionarios;
        numTrabajos = numFuncionarios;
    }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}