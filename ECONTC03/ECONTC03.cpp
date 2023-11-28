#include <iostream>

using namespace std;

bool esApta(int v[], const int& desnivelMax, const int& numCotas) {
	bool apta = true;
	int i = 0;
	int cotaAnterior = 0;
	int cotaInferior = v[0];
	int cotaSuperior = v[0];
	while (i < numCotas && (cotaSuperior - cotaInferior) <= desnivelMax) {
		if (v[i] > cotaAnterior) {
			cotaSuperior= v[i];
			cotaAnterior = v[i];
		}
		else {
			cotaInferior = v[i];
			cotaAnterior = 0;
		}
		i++;
	}
	if ((cotaSuperior - cotaInferior) > desnivelMax) {
		apta = false;
	}
	return apta;
}

int main() {
	int desnivelMax;
	cin >> desnivelMax;
	while (!cin.eof()) {
		int numCotas;
		cin >> numCotas;
		int v[200000];
		for (int i = 0; i < numCotas; i++) {
			cin >> v[i];
		}
		bool apta = esApta(v, desnivelMax, numCotas);
		if (apta) {
			cout << "APTA" << endl;
		}
		else {
			cout << "NO APTA" << endl;

		}
		cin >> desnivelMax;
	}
	return 0;
}