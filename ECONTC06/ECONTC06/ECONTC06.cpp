//NOMBRE y APELLIDOS: Iván Hernández Roldán


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Dos funciones de poda de optimalidad:
// 1ª: Podria ver cual es la mejor donacion de todos los artistas en cualquier momento y multiplicar ese valor por los huecos que me quedan por ocupar en la solucion para conseguir una estimacion de la donacion maxima alcanzable
// 2ª: Podria ver cual es la mejor donacion de cada momento posible y crear un vector<int> estimacion que me indique la mejor donacion desde cada nivel de la solucion
  
void conciertoRock(const vector<vector<int>>& donaciones, const vector<vector<int>>& vetos, int numArtistas, int numMomentos, vector<bool>& marcadorArtistas, vector<int>&solucion, int k, int &donacion, int &donacionMejor, const vector<int>& estimacion, bool& exito) {
    for (int i = 0; i < numArtistas; i++) {
        if (!marcadorArtistas[i]){ // esValida?
            marcadorArtistas[i] = true; // marco
            if (k != 0) {
                if (vetos[i][solucion[k-1]] == 1) { // esValida?
                    solucion[k] = i; // marco
                    donacion += donaciones[i][k]; // marco
                    if (k == numArtistas - 1) { // esSolucion?
                        if (donacion > donacionMejor) { // esLaMejorSolucionConseguida?
                            donacionMejor = donacion;
                            exito = true;
                        }
                    }
                    else {
                        if (donacion + estimacion[k] > donacionMejor) { // esRentableSeguirConstruyendoEstaSolucion?
                            conciertoRock(donaciones, vetos, numArtistas, numMomentos, marcadorArtistas, solucion, k + 1, donacion, donacionMejor, estimacion, exito);
                        }
                    }
                    donacion -= donaciones[i][k]; // desmarco
                    solucion[k] = -1; // desmarco
                }
            }
            else {
                solucion[k] = i; // marco
                donacion += donaciones[i][k]; // marco
                if (k == numArtistas - 1) { // esSolucion?
                    if (donacion > donacionMejor) { // esLaMejorSolucionConseguida?
                        donacionMejor = donacion;
                        exito = true;
                    }
                }
                else {
                    if (donacion + estimacion[k] > donacionMejor) { // esRentableSeguirConstruyendoEstaSolucion?
                        conciertoRock(donaciones, vetos, numArtistas, numMomentos, marcadorArtistas, solucion, k + 1, donacion, donacionMejor, estimacion, exito);
                    }
                }
                donacion -= donaciones[i][k]; // desmarco
                solucion[k] = -1; // desmarco
            }
            marcadorArtistas[i] = false; // desmarco
        }  
    }
}

void resuelveCaso() {
    int numArtistas, numMomentos;
    cin >> numArtistas;
    numMomentos = numArtistas;
    vector<vector<int>> donaciones; // cada casilla de la matriz cuadrada donaciones es la donacion estimada del artista "fila" si toca en el momento "columna"
    vector<int> mejorDonacion; // el valor de cada posicion (momento de actuar) es la mejor donacion posible que puede obtener en ese momento de actuar entre todos los artistas
    vector<bool> marcadorArtistas; // el valor de cada posicion (artista) es un booleano que indica si ese artista ya tiene asignado un momento para tocar
    vector<int> solucion; // el valor de cada posición (momento de actuar) es el artista que va a actuar en ese momento
    vector<int> estimacion; // el valor de cada posicion (nivel de la solucion) es la mejor estimacion para la mejor donacion final alcanzable desde ese nivel de la solucion
    for (int i = 0; i < numMomentos; i++) {
        estimacion.push_back(0);
        mejorDonacion.push_back(0);
        marcadorArtistas.push_back(false);
        solucion.push_back(-1); // inicializo la solucion a un valor cualquiera
    }
    for (int i = 0; i < numArtistas; i++) {
        vector<int> artista;
        donaciones.push_back(artista);
        for (int j = 0; j < numMomentos; j++) {
            int donacion;
            cin >> donacion;
            donaciones[i].push_back(donacion);
            if (donacion > mejorDonacion[j]) {
                mejorDonacion[j] = donacion;
            }
        }
    }
    estimacion[numMomentos - 1] = 0;
    for (int i = numMomentos - 2; i >= 0; i--) {
        estimacion[i] = estimacion[i + 1] + mejorDonacion[i + 1];
    }
    vector<vector<int>> vetos; // cada casilla de la matriz cuadrada vetos es la decision del artista "fila" sobre si quiere tocar despues del artista "columna"
    for (int i = 0; i < numArtistas; i++) {
        vector<int> artista;
        vetos.push_back(artista);
        for (int j = 0; j < numArtistas; j++) {
            int veto;
            cin >> veto;
            vetos[i].push_back(veto);
        }
    }
    int donacion = 0; // es la donacion de la solucion parcial
    int donacionMejor = 0; // es la mejor donacion acumulada de todas las soluciones finales. Inicializada a 0 porque es una cota inferior.
    bool exito = false;
    int k = 0; // es el nivel de la solucion parcial. Indica el momento de actuar.
    conciertoRock(donaciones, vetos, numArtistas, numMomentos, marcadorArtistas, solucion, k, donacion, donacionMejor, estimacion, exito);
    if (exito) {
        cout << donacionMejor <<endl;
    }
    else {
        cout << "NEGOCIA CON LOS ARTISTAS" << endl;
    }
}

int main1() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample-ECONTC06.1.in");
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