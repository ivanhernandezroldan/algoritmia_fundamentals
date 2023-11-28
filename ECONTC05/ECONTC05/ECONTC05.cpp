//NOMBRE y APELLIDOS: Iván Hernández Rooldán


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int encontrarImpar(const vector<int>& v, int& inicio, int& fin) {
    if (inicio == fin) { //Caso base: caso unitario
        return inicio;
    }
    else { // Casos recursivos:
        int mitad = (inicio + fin) / 2;
        if (((fin - inicio) / 2) % 2 == 0) { // Si lo que queda a los lados de la mitad es un numero de elementos par
            if (v[mitad] == v[mitad - 1]) { // Si el elemento mitad es igual al de su izquierda
                return encontrarImpar(v, inicio, mitad); // Llamada recursiva por la izquierda
            }
            else { // Si el elemento mitad es igual al de su derecha
                return encontrarImpar(v, mitad, fin); // Llamada recursiva por la derecha
            }
        }
        else { // Si lo que queda a los lados de la mitad es un numero de elementos impar
            if (v[mitad] == v[mitad - 1]) { // Si el elemento mitad es igual al de su izquierda
                int nuevo_inicio = mitad + 1;
                return encontrarImpar(v, nuevo_inicio, fin); // Llamada recursiva por la derecha 
            }
            else { //Si el elemento mitad es igual al de su derecha
                int nuevo_fin = mitad -1;
                return encontrarImpar(v, inicio, nuevo_fin); // Llamada recursiva por la izquierda
            }
        }
    }
}

int encontrarImpar(const vector<int>& v, const int & num_elems) {
    int inicio = 0; // inicializacion de un parametro de entrada salida de la funcion recursiva
    int fin = num_elems - 1; // inicializacion de un parametro de entrada salida de la funcion recursiva
    return encontrarImpar(v, inicio, fin); //lamada inicial a la funcion recursiva
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int num_elems;
    cin >> num_elems;
    vector<int> v;
    for (int i = 0; i < num_elems; i++) {
        int elem;
        cin >> elem;
        v.push_back(elem);
    }
     //Calcula el resultado
    int posImpar = encontrarImpar(v, num_elems);
     //Escribe el resultado
    cout << posImpar << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("1.in");
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