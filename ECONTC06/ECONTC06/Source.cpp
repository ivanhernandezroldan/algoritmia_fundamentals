#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

using tMatriz = vector<vector<int>>;

bool esValida(const tMatriz &vetos, int k, int i, int ultimo) {
	if (k == 0)return true;
	if (k > 0 && vetos[i][ultimo] == 1) return true;
	return false;
}

void donacion(int k, const tMatriz &vetos, const tMatriz &donaciones, vector<bool> &marcas, int donacionAc, int & donacionMejor, bool &haySol, const vector<int> &sumaRapido, const int &ultimo) {
	for (int i = 0; i < vetos.size(); i++) {

		if (!marcas[i] && esValida(vetos, k, i,ultimo)) {
			marcas[i] = true;
			donacionAc += donaciones[i][k];

			if (k + 1 == vetos.size()) {
				if (donacionAc > donacionMejor)
					donacionMejor = donacionAc;
				haySol = true;
			}
			else {
				if (sumaRapido[k] + donacionAc > donacionMejor)
					donacion(k + 1, vetos, donaciones, marcas, donacionAc, donacionMejor, haySol, sumaRapido,i);
			}

			marcas[i] = false;
			donacionAc -= donaciones[i][k];
		}
	}
}


void resuelveCaso1() {
	int n;
	cin >> n;


	tMatriz donaciones(n, vector<int>(n));
	tMatriz vetos(n, vector<int>(n));


	vector<bool> marcas(n, false);
	vector<int> maximo(n), sumaRapido(n);

	int costeMejor = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> donaciones[i][j];
		}
	}
	int maxi = -1;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> vetos[i][j];
		}
	}


	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			maxi = max(maxi, donaciones[i][j]);
		}
		maximo[i] = maxi;
		maxi = -1;
	}

	if (n > 1) {
		sumaRapido[n - 1] = 0;
		for (int i = n - 2; i >= 0; --i) {
			sumaRapido[i] = sumaRapido[i + 1] + maximo[i + 1];
		}
	}

	bool haySol = false;
	int donacionMejor = 0;

	donacion(0, vetos, donaciones, marcas, 0, donacionMejor, haySol, sumaRapido,0);

	if (haySol)
		cout << donacionMejor << endl;
	else
		cout << "NEGOCIA CON LOS ARTISTAS" << endl;

}



int main() {

	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	ifstream in("sample-ECONTC06.1.in");
	auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect cin to casos.txt
#endif

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i)
		resuelveCaso1();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

}
