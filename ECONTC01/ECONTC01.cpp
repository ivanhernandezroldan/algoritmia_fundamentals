#include <iostream> 

using namespace std;

void es_Pastoso(int v[], const int & n, bool & exito, int & indicePastoso){
	int i = n-1;
	int sumaParcial = 0;
	while(!exito && i >= 0){
		if(v[i] == sumaParcial){
			exito = true;
			indicePastoso = i;
		}
		else{
			sumaParcial += v[i];
			i--;
		}
	}
}

int main(){
	int numCasos;
	cin >> numCasossos;
	while(numCasos--){
		int n;
		cin >> n;
		int v[100000];
		for(int i = 0; i < n; i++){
			cin >> v[i];
		}
		int indicePastoso;
		bool exito = false;
		es_Pastoso(v, n, exito, indicePastoso);
		if(exito){
			cout << "Si " << indicePastoso << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
}