#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>>lire_matrice(int n);
void tache_1();
//void printMatriceInital(const vector<vector<bool>>& matInit, int n);

int main(){	
	
	tache_1();
	
}

void tache_1(){
	
	char pbm[3];//by convention the end of strings represented in character sequences is signed by '\0'
	unsigned int n(0);//colonnes
	unsigned int m(0);//lignes
	
	cin >> pbm;
	if(!(pbm[0]=='P' && pbm[1]=='1' && pbm[2]=='\0')){
		exit(0);
	}
	//cout << pbm << endl;
	
	cin >> n >> m;
	if(n!=m){
		exit(0);
	}
	
	//printMatriceInital(lire_matrice(n), n);
	
	vector<vector<bool>>matrice_adjacente=construire_matAdj(lire_matrice(),n);
}
vector<vector<bool>>lire_matrice(int n){
	
	vector<vector<bool>>matInit(n, vector<bool>(n, true)); //initialise à blanc
	bool valeur;
	for(size_t i(0); i<matInit.size(); ++i){
		for(size_t j(0); j<matInit.size(); ++j){
			cin >> valeur;
			matInit[i][j]=valeur;//place les 0 et 1 dans matrice
		}
	}
	return matInit;//retourne la matrice du fichier, par encore matAdj
}

/*void printMatriceInital(const vector<vector<bool>>& matInit, int n){
	for(int i(0); i<n; ++i){
		for(int j(0); j<n; ++j){
			cout << matInit[i][j];
		}cout << endl;
	}cout << endl;

}*/


