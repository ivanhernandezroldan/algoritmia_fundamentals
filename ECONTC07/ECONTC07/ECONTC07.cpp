
// NOMBRE Y APELLIDOS: Iván Hernández Roldán

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Cancion {
    int duracion;
    int puntuacion;
};

void grabacion(const vector<Cancion> &canciones, vector<bool> &marcadorCanciones, int numCanciones, int &duracionCaraDisponible, int duracionCancionMasCorta, int &puntuacion, int &puntuacionMejor, vector<bool> &solucion) {
    for (int i = 0; i < numCanciones; i++) {
        if (!marcadorCanciones[i] && canciones[i].duracion <= duracionCaraDisponible) { // esValida?
            marcadorCanciones[i] = true; // marco
            puntuacion += canciones[i].puntuacion; // marco
            duracionCaraDisponible -= canciones[i].duracion; // marco
            if (duracionCancionMasCorta > duracionCaraDisponible) { // esSolucion?
                if (puntuacion > puntuacionMejor) { // esLaMejorSolucion?
                    puntuacionMejor = puntuacion;
                    solucion = marcadorCanciones;
                }
            }
            else {
                //falta la poda de optimizacion: hubiese hecho if(mejorPuntuacionDeTodasLasCanciones*(duracionCaraDisponible/duracionCancionMasCorta) + puntuacion > puntuacionMejor)
                grabacion(canciones, marcadorCanciones, numCanciones, duracionCaraDisponible, duracionCancionMasCorta, puntuacion, puntuacionMejor, solucion);
            }
            marcadorCanciones[i] = false; // desmarco
            puntuacion -= canciones[i].puntuacion; // desmarco
            duracionCaraDisponible += canciones[i].duracion; // desmarco
        }
    }
}

bool resuelveCaso() {
    int numCanciones;
    cin >> numCanciones;
    if (numCanciones == 0) {
        return false;
    }
    int duracionCara;
    cin >> duracionCara;
    vector<Cancion> canciones; // Vector que recoge la informacion de todas las canciones
    int duracionCancionMasCorta = duracionCara*2; // Inicializo a una cota superior.
    for (int i = 0; i < numCanciones; i++) {
        int duracion, puntuacion;
        cin >> duracion >> puntuacion;
        if (duracion < duracionCancionMasCorta) {
            duracionCancionMasCorta = duracion;
        }
        Cancion c { duracion, puntuacion };
        canciones.push_back(c);
    }
    vector<bool> marcadorCanciones; // Marcador de las canciones ya asignadas en la solucion parcial
    vector<bool> solucion; // Marcador de las canciones asignadas en la solucion final
    for (int i = 0; i < numCanciones; i++) {
        marcadorCanciones.push_back(false);
        solucion.push_back(false);
    }
    int puntuacion = 0; // Es la puntuacion de la solucion parcial. Inicializo a '0' porque es una cota inferior.
    int puntuacionMejorCara1 = 0; // Es la puntuacion de la mejor solucion final obtenida en la primera cara. Inicializo a '0' porque es una cota inferior.
    int puntuacionMejorCara2 = 0; // Es la puntuacion de la mejor solucion final obtenida en la segunda cara. Inicializo a '0' porque es una cota inferior.
    int duracionCaraDisponible = duracionCara; // Es la duracion disponible de la cara en cada momento de la solucion
    grabacion(canciones, marcadorCanciones, numCanciones, duracionCaraDisponible, duracionCancionMasCorta, puntuacion, puntuacionMejorCara1, solucion);
    duracionCaraDisponible = duracionCara; // Reinicio el valor de la duracion disponible de la nueva cara 
    marcadorCanciones = solucion;
    grabacion(canciones, marcadorCanciones, numCanciones, duracionCaraDisponible, duracionCancionMasCorta, puntuacion, puntuacionMejorCara2, solucion);
    cout << puntuacionMejorCara1 + puntuacionMejorCara2 << endl;
    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("sample-ECONTC07.1.in");
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