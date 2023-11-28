#include <iostream>

using namespace std;
// { 0 < longitud(v) && longVector = longitud(v) }
// fun intervaloNoMejora(int v[]) return int segmentoMasLargo
// { segmentoMasLargo = max p, q : (0 <= p < q <= longitud(v)) && (paratodo x: p < x < q : v[p] > v[x] ) : q - p - 1}

int intervaloNoMejora(int v[], const int & longVector) {
	// Cota : longVector - indice
	// INV : 0 <= indice <= longVector && mejorMarca = max i: 0 <= i < indice : v[i] && segmentoMasLargo = max p, q : (0 <= p < q <= indice) && (paratodo x: p < x < q : v[p] > v[x] ) : q - p - 1
	
	int segmentoMasLargo = 0;
	int segmentoMasLargoParcial = 0;
	int indice = 0;
	int mejorMarca = 0;
	while (indice < longVector) {
		if (mejorMarca < v[indice]) {
			mejorMarca = v[indice];
			if (segmentoMasLargoParcial > segmentoMasLargo) {
				segmentoMasLargo = segmentoMasLargoParcial;
			}
			segmentoMasLargoParcial = 0;
		}
		else {
			segmentoMasLargoParcial++;
		}
		indice++;
	}
	if(segmentoMasLargoParcial > segmentoMasLargo) {
		segmentoMasLargo = segmentoMasLargoParcial;
	}
	return segmentoMasLargo;
}

//Coste del algoritmo: En todos los casos el coste es O(n) donde n = longVector porque para calcular la solución es necesario si o si pasar por todos los elementos del vector

int main() {
	int numCasos;
	cin >> numCasos;
	while (numCasos--) {
		int longVector;
		cin >> longVector;
		int v[100]; // no se cuál debería ser la capacidad del vector, pongo 100 porque supongo que me valdrá para todos los casos
		for (int i = 0; i < longVector; i++) {
			int valor;
			cin >> valor;
			v[i] = valor;
		}
		int solucion = intervaloNoMejora(v, longVector);
		cout << solucion << endl;
	}
}