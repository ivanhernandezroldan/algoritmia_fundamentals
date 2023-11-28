
// NOMBRE Y APELLIDOS: IVÁN HERNÁNDEZ ROLDÁN

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool esSuficientementeDisperso(const vector<int>& v, const int& dispersionPrecisada, const int& ini, const int& fin) {
	if (ini == fin) { //CASO BASE: el segmento unitario se considera suficientemente disperso
		return true;
	}
	else {//CASO RECURSIVO
		int mitad = (ini + fin) / 2;
		bool esDispersoIzquierda = esSuficientementeDisperso(v, dispersionPrecisada, ini, mitad);
		bool esDispersoDerecha = esSuficientementeDisperso(v, dispersionPrecisada, mitad + 1, fin);
		if (esDispersoIzquierda && esDispersoDerecha) {
			if (abs(v[ini] - v[fin]) >= dispersionPrecisada) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
}


/*
COSTE DEL ALGORTIMO:
· Tamaño del problema = n = fin - ini + 1
· Analizando el tiempo de ejectucion del algoritmo en el caso peor:
	T(n) = {
		c0 si n = 1              // donde c0 es el tiempo invertido en evaluar la condicion del caso base.
		2*T(n/2) + c1 si n > 1     // donde c1 es el tiempo invertido en inicializar mitad y en evaluar la condición (esDispersoIzquierda && esDispersoDerecha) y la condicion (abs(v[ini] - v[fin]) >= dispersionPrecisada).
	}
· Despliegue de recurrencias:
	T(n) = c1 + 2*T(n/2)
		 = c1 + c1 + c1 + 4*T(n/4)
		 = c1 + c1 + c1 + c1 + c1 + c1 + c1 + 8*T(n/8)
		 ...
		 = ((2^k) - 1)*c1 + (2^k)*T(n/2^k)
·Postulado:
	(Las llamadas terminan cuando n = 1)
	=> n/2^k = 1; k = log n;
	=>T(n) = c1*(2^log n) + (2^log n)*T(n/2^log n) = c1*n + n*T(1) => Por tanto: T(n) es de O(n).
*/

/*
RECURRENCIA DEL ALGORITMO:
	T(n) = {
		c0 si n = 1              // donde c0 es el tiempo invertido en evaluar la condicion del caso base.
		a*T(n/b) + c1*n^k si n > 1     // donde c1 es el tiempo invertido en inicializar mitad y en evaluar la condición (esDispersoIzquierda && esDispersoDerecha) y la condicion (abs(v[ini] - v[fin]) >= dispersionPrecisada).
	}
COSTE DEL ALGORITMO SEGUN EL TEOREMA DE LA DIVISION:
·Tenemos:
	k = 0;
	b = 2; 
	a = 2;
·Por tanto:
	=> Como a > b^k, entonces T(n) es de O(n^log(base2)2).
	=> T(n) es de O(n).
*/

bool esSuficientementeDisperso(const vector<int>  &v, const int& dispersionPrecisada) {
	int ini = 0; //parametro de entrada inicial de la función recursiva
	int fin = v.size() - 1; //parametro de entrada inicial de la función recursiva
	//dispersion Precisada tambien es un parametro de entrada que tiene el mismo valor en todas las llamadas recursivas
	//llamada inicial a la funcion recursiva
	return esSuficientementeDisperso(v, dispersionPrecisada, ini, fin);
}

bool resuelveCaso() {
	//Leer caso de prueba: cin>>...
	int numTiradas;
	cin >> numTiradas;
	if (!std::cin) {
		return false;
	}
	else {
		int dispersionPrecisada;
		cin >> dispersionPrecisada;
		vector<int> v;
		for (int i = 0; i < numTiradas; i++) {
			int valorTirada;
			cin >> valorTirada;
			v.push_back(valorTirada);
		}
		bool esDisperso = esSuficientementeDisperso(v, dispersionPrecisada);
		if (esDisperso) {
			cout << "SI" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	//Resolver problema
	//Escribir resultado
	return true;
}


int main() {

	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.in");
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