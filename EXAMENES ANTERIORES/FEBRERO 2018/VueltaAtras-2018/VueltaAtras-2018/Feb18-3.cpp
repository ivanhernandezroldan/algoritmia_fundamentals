//NOMBRE y APELLIDOS: Iván Hernández Roldán

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void quitaNieves(const vector<int>& anchuraMaquinas, const vector<int>& anchuraCarreteras, int numMaquinas, int numCarreteras, const vector<vector<int>>& calidades, int k, vector<int>& solucion, int& calidad, vector<int>& solucionMejor, int& calidadMejor, const vector<int>& estimacion, vector<bool> &marcadorCarreteras) {
    for (int i = 0; i < numCarreteras + 1; i++) {
        if (i == numCarreteras) { // caso en el que no se le asigna ninguna carretera a la quitanieves del nivel k
            if (k == numMaquinas - 1) { // esSolucion?
                if (calidad > calidadMejor) { // esLaMejorSolucion?
                    calidadMejor = calidad;
                    solucionMejor = solucion;
                }
            }
            else {
                if (calidad + estimacion[k] > calidadMejor) { // esRentableSeguirConstruyendoLaSolucion?
                    quitaNieves(anchuraMaquinas, anchuraCarreteras, numMaquinas, numCarreteras, calidades, k + 1, solucion, calidad, solucionMejor, calidadMejor, estimacion, marcadorCarreteras);
                }
            }
        }
        else{
            if (!marcadorCarreteras[i] && anchuraMaquinas[k] <= anchuraCarreteras[i]) { // esValida?
                solucion.push_back(i);
                marcadorCarreteras[i] = true;
                calidad += calidades[k][i];
                if (k == numMaquinas - 1) { // esSolucion?
                    if (calidad > calidadMejor) { // esLaMejorSolucion?
                        calidadMejor = calidad;
                        solucionMejor = solucion;
                    }
                }
                else {
                    if (calidad + estimacion[k] > calidadMejor) { // esRentableSeguirConstruyendoLaSolucion?
                        quitaNieves(anchuraMaquinas, anchuraCarreteras, numMaquinas, numCarreteras, calidades, k + 1, solucion, calidad, solucionMejor, calidadMejor, estimacion, marcadorCarreteras);
                    }
                }
                solucion.pop_back();
                marcadorCarreteras[i] = false;
                calidad -= calidades[k][i];
            }
        }       
    }
}

void resuelveCaso() {
    int numMaquinas, numCarreteras;
    cin >> numMaquinas >> numCarreteras;
    vector<int> anchuraMaquinas; // el valor de cada posicion (maquina) es la anchura de esa maquina
    vector<int> anchuraCarreteras; // el valor de cada posicion (carretera) es la anchura de esa carretera
    for (int i = 0; i < numMaquinas; i++) {
        int anchura;
        cin >> anchura;
        anchuraMaquinas.push_back(anchura);
    }
    for (int i = 0; i < numCarreteras; i++) {
        int anchura;
        cin >> anchura;
        anchuraCarreteras.push_back(anchura);
    }
    vector<vector<int>> calidades; // cada casilla de la matriz cuadrada corresponde a la calidad de limpieza de la maquina (fila) en la carretera (columna)
    vector<int> mejoresCalidades; // el valor de cada posicion (maquina) es la mejor calidad posible que puede conseguir esa maquina entre todas las carreteras disponibles
    for (int i = 0; i < numMaquinas; i++) {
        vector<int> fila;
        calidades.push_back(fila);
        mejoresCalidades.push_back(0);
        for (int j = 0; j < numCarreteras; j++) {
            int calidad;
            cin >> calidad;
            calidades[i].push_back(calidad);
            if (calidad > mejoresCalidades[i]) {
                mejoresCalidades[i] = calidad;
            }
        }
    }
    vector<int> estimacion; // el valor de cada posicion (nivel de la solucion parcial) es la estimación de la mejor calidad posible a alcanzar desde ese nivel de la solucion parcial
    for (int i = 0; i < numMaquinas; i++) {
        estimacion.push_back(0);
        for (int j = i + 1; j < numMaquinas; j++) {
            estimacion[i] += mejoresCalidades[j];
        }
    }
    vector<int> solucion, solucionMejor; // el valor de cada posición (maquina) es la carretera asignada a esa maquina
    int calidad = 0; // indica la calidad de la solucion parcial.
    int calidadMejor = 0; // indica la calidad de la solucion mejor. Inicializo a 0 porque es una cota inferior.
    vector<bool> marcadorCarreteras; // el valor de cada posicion (carretera) es un booleano que indica si esa carretera ha sido asignada en la solucion parcial
    for (int i = 0; i < numCarreteras; i++) {
        marcadorCarreteras.push_back(false);
    }
    int k = 0; // indica el nivel por donde vamos en la solucion parcial
    if (numMaquinas == 0) {
        cout << 0 << endl;
    }
    else {
        quitaNieves(anchuraMaquinas, anchuraCarreteras, numMaquinas, numCarreteras, calidades, k, solucion, calidad, solucionMejor, calidadMejor, estimacion, marcadorCarreteras);
        cout << calidadMejor << endl;
    }
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-Feb18-3.1.in");
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