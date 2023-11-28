//NOMBRE y APELLIDOS: Iván Hernández Roldán


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool esValida(int color, const vector<int> &solParcial, const vector<int> &marcadorCubos, int k, int cubosAzules, int cubosRojos, int cubosVerdes) {
    bool valida = true;
    if (k == 0 && color != 1) { // Si en la primera posicion no voy a colocar un cubo rojo
        valida = false;
    }
    else if (color == 2 && solParcial[k-1] == 2) { // Si voy a colocar un verde despues de haber colocaado otro verde
        valida = false;
    }
    else if (color == 2 && marcadorCubos[2] + 1 > marcadorCubos[0]) { // Si con la eleccion del cubo se deja de cumplir piezas verdes < piezas azules
        valida = false;
    }
    else if (color == 0 && marcadorCubos[0] == cubosAzules) { // Si ya he utilizado todos los cubos azules
        valida = false;
    }
    else if (color == 1 && marcadorCubos[1] == cubosRojos) { // Si ya he utilizado todos los cubos rojos
        valida = false;
    }
    else if (color == 2 && marcadorCubos[2] == cubosVerdes) { // Si ya he utilizado todos los cubos verdes
        valida = false;
    }
    return valida;
}

void tratarSolucion(const vector<int>& solParcial) {
    for (int i : solParcial) {
        if (i == 0) {
            cout << "azul";
        }
        else if (i == 1) {
            cout << "rojo";
        }
        else {
            cout << "verde";
        }
        cout << " ";
    }
    cout << endl;
}

void torreColores(vector<int> &solParcial, vector<int> &marcadorCubos, int alturaTorre, int k, int cubosAzules, int cubosRojos, int cubosVerdes, bool &solucionEncontrada) {
    // i = 0 es la opcion de colocar un cubo azul en la solucionParcial
    // i = 1 es la opcion de colocar un cubo rojo en la solucionParcial
    // i = 2 es la opcion de colocar un cubo verde en la solucionParcial
    for (int i = 0; i < 3; i++) {
        if (esValida(i, solParcial, marcadorCubos, k, cubosAzules, cubosRojos, cubosVerdes)) {
            solParcial.push_back(i);
            marcadorCubos[i]++;
            if (k == alturaTorre - 1) {
                if (marcadorCubos[1] > marcadorCubos[0] + marcadorCubos[2]) {
                    tratarSolucion(solParcial);
                    solucionEncontrada = true;
                }   
            }
            else {
                if (k < alturaTorre - 1) {
                    torreColores(solParcial, marcadorCubos, alturaTorre, k + 1, cubosAzules, cubosRojos, cubosVerdes, solucionEncontrada);
                }
            }
            solParcial.pop_back();
            marcadorCubos[i]--;
        }
    }
}

void resuelveCaso(int alturaTorre, int cubosAzules, int cubosRojos, int cubosVerdes) {
    vector<int> solParcial;
    vector<int> marcadorCubos; 
    for (int i = 0; i < 3; i++) {
        marcadorCubos.push_back(0);
    }
    // la pos 0 de marcadorCubos indica el numero de cubos azules usados
    // la pos 1 de marcadorCubos indica el numero de cubos rojos usados
    // la pos 2 de marcadorCubos indica el numero de cubos verdes usados
    int k = 0; // Es el nivel de la solucion parcial
    bool solucionEncontrada = false;
    torreColores(solParcial, marcadorCubos, alturaTorre, k, cubosAzules, cubosRojos, cubosVerdes, solucionEncontrada);
    if (solucionEncontrada) {
        cout << endl;
    }
    else {
        cout << "SIN SOLUCION" << endl << endl;
    }
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-C20.1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int alturaTorre, cubosAzules, cubosRojos, cubosVerdes;
    cin >> alturaTorre >> cubosAzules >> cubosRojos >> cubosVerdes;
    while (alturaTorre != 0 || cubosAzules != 0 || cubosRojos != 0 || cubosVerdes != 0) {
        resuelveCaso(alturaTorre, cubosAzules, cubosRojos, cubosVerdes);
        cin >> alturaTorre >> cubosAzules >> cubosRojos >> cubosVerdes;
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}