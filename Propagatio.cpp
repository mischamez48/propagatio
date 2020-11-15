#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

const string P1("P1 missing or incorrect");
const string WRONG_NB_COL_LGN("Nb columns and/or nb lines incorrect");
const string MATRIX_SQUARE("Matrix is not square");
const string IRREGULAR_CONTENT("Matrix description with incorrect content");
const string DISCONNECTED_GRAPH("Matrix corresponds to a disconnected graph");

vector<vector<bool>>lire_matrice(int n);
void check(int i, vector<bool>& visited ,vector<vector<bool>> matAdj, int n);
vector<vector<bool>> tache_1(unsigned int& n);
vector<bool> tache_2(vector<vector<bool>>matAdj, int n);
void tache_3(vector<bool> visited, vector<vector<bool>> matAdj, int n);
void recursio(vector<int>& dep, vector<vector<bool>> matAdj, vector<bool>& visited, int n, vector<vector<int>>& sepp);
bool contains(vector<int> v, int x);
void printMatrice(const vector<vector<bool>>& mat, int n);
void printPbm(const vector<vector<bool>>& mat, int n);
void DEBUG_ERR(const char x[]);
void DEBUG(const char x[]);
vector<vector<bool>>construire_matAdj(const vector<vector<bool>>& MatInit, int n);
void tache_4(vector<bool>& visited, vector<vector<bool>> matAdj, int n);

int main() {
	unsigned int n(0);	// Colonnes


	vector<vector<bool>>matAdj = tache_1(n);

	vector<bool> visited = tache_2(matAdj, n);

	tache_3(visited, matAdj, n);
	
	tache_4(visited,matAdj,n);
	

}



vector<vector<bool>> tache_1(unsigned int& n) {

	char pbm[3];			// Par convention les tableaux de char se terminent par le delimiteur '\0' prenant donc la derniere pos du tableau
	unsigned int m(0);		// Lignes

	cin >> pbm;
	if (!(pbm[0] == 'P' && pbm[1] == '1' && pbm[2] == '\0')) { //3.2.1.2
		cout << P1 <<endl;
		exit(0);
	}
	//DEBUG(pbm);

	cin >> n >> m;
	if (n == 0 || m == 0) {// colonnes et lignes doivent être strictements positifs
		cout << WRONG_NB_COL_LGN << endl;
		//DEBUG_ERR("Entree infos d'entete incorrectes");
		exit(0);
	}else if(n!=m){
		cout << MATRIX_SQUARE << endl;
		exit(0);
	}



	//printMatrice(lire_matrice(n), n);

	return construire_matAdj(lire_matrice(n), n);
}

vector<bool> tache_2(vector<vector<bool>> matAdj, int n) {
	vector<bool> visited(n);				// Init tab visited
	for (int i(0); i < n; i++) {
		visited[i] = false;					// Tous les elems a false
	}

	int initInt(0);							// Variable pour 1er appel de check()

	for (int i(0); i < n; i++) {
		for (int j(0); j < n; j++) {
			if (matAdj[i][j] == true) {
				initInt = i;				// Si un elem sur ligne i de matAdj est vrai, commencer check par i
			}
		}
	}

	check(initInt, visited, matAdj, n);		// Premier appel de la fonction recursive

	for (int i(0); i < n; i++) {			// Verification que visited contienne que des true
		if (visited[i] == false) {
			cout << DISCONNECTED_GRAPH <<endl;
			//DEBUG_ERR("DO ERROR MSG 3.1.2");// Sinon arret du programme car matAdj non connexe
			exit(0);
		}
	}

	return visited;
}

void tache_3(vector<bool> visited, vector<vector<bool>> matAdj, int n) {
	for (int i(0); i < n; i++) {
		visited[i] = false;						// Ré-init visited à false
	}

	vector<int> initDep(1);
	vector<vector<int>> sepp;
	initDep[0] = 0;								// Ensemble de départ contient noeud 0 uniquement

	cout << "0";						//commence toujours pas le noed 0, donc afficher 0	

	recursio(initDep, matAdj, visited, n, sepp);	//Appel de la récursion avec ensemble {0} de départ

	for (unsigned int i(0); i < sepp.size(); ++i) {
		if(!(i==(sepp.size()-1))){
				cout << endl;
		}
		for (unsigned j(0); j < sepp[i].size(); ++j) {
			cout << sepp[i][j];
			if(!(j==(sepp.size()))){
				cout << " ";
			}
		}cout << endl;
	}
		
}

void recursio(vector<int>& depart, vector<vector<bool>> matAdj, vector<bool>& visited, int n,vector<vector<int>>& sepp) {
	if (depart.size() > 0) {						// Tant que l'ensemble de départ n'est pas vide : 
		vector<int> arrivee;						// Ensemble temporaire
		for (unsigned int i(0); i < depart.size(); ++i) {
			visited[depart[i]] = true;				// Ligne du noeud dans l'ensemble de départ à été visité
			for (int j(0); j < n; j++) {
				if (matAdj[depart[i]][j] == true && visited[j] == false && !contains(depart, j)) {		
					arrivee.push_back(j);			// On met le noeud dans l'ensemble temporaire
					visited[j]= true;
				}
			}
		}
		sort(arrivee.begin(), arrivee.end());
		if(arrivee.size()!=0){
		sepp.push_back(arrivee);
		recursio(arrivee, matAdj, visited, n, sepp);	// On rappelle la fonction avec l'ensemble temporaire
		}
		
	}
}

void tache_4(vector<bool>& visited, vector<vector<bool>> matAdj, int n){
	
	vector<double> distance_moyenne(n);
	double moyenne(0);
	
	for(unsigned int i(0); i<visited.size(); ++i){
		for(int i(0); i < n; i++){
			visited[i] = false;						// Ré-init visited à false
		}
		vector<vector<int>>sepp;
		vector<int>initDep(1);
		initDep[0]=i;
		
		recursio(initDep, matAdj, visited, n, sepp);
		
		double tmp;
		for(unsigned int j(0); j<sepp.size();++j){
			tmp=(sepp[j].size()*(j+1));
			distance_moyenne[i]+=(tmp/(n-1));
			tmp=0;
		}
		moyenne+=distance_moyenne[i]/n;
		sepp.clear();
	}
	cout <<fixed << setprecision(6) << moyenne<< endl;
	
	
}




vector<vector<bool>>lire_matrice(int n) {

	//TODO Prendre les erreurs sur le fichier error.txt def page 7 du pdf

	vector<vector<bool>>matInit(n, vector<bool>(n, true)); //initialise à blanc

	unsigned int input;
	for (size_t i(0); i < matInit.size(); ++i) {
		for (size_t j(0); j < matInit.size(); ++j) {
			cin >> input;
			if (input > 1) {						// Si la valeur donnée en input n'est pas de type bool
				cout << IRREGULAR_CONTENT <<endl;
				//DEBUG_ERR("valeur incorrecte");		// Avertir et imprimer erreur
				exit(0);
			}
			matInit[i][j] = input;					// Place les 0 et 1 dans matrice (pas besoin de cast)
		}
	}
	return matInit;									// Retourne la matrice du fichier pre-adj
}

void check(int i, vector<bool>& visited, vector<vector<bool>> matAdj, int n) {
	visited[i] = true;										// Passer ligne en vrai grace à la verification the initInt
	for (int j = 0; j < n; j++) {
		if (matAdj[i][j] == true && visited[j] == false) {	// Si on trouve un noeud voisin qui n'a pas été vérifié,
			check(j, visited, matAdj, n);					// on cherche les voisins de celui-ci
		}
	}
}

vector<vector<bool>>construire_matAdj(const vector<vector<bool>>& MatInit, int n) {

	vector<vector<bool>>matAdj(n, vector<bool>(n)); // Init matrice adj

	for (int i(0); i < n; ++i) {					// Etape 1
		for (int j(0); j < n; j++) {
			matAdj[i][j] = MatInit[i][j];			// Copie de la matrice init passée en param
		}
	}

	for (int i(0); i < n; ++i) {					// Etape 2
		for (int j(0); j < n; j++) {
			if (matAdj[i][j] == 1) {
				matAdj[j][i] = 1;					// Condition donnée dans 3.2.1.3
			}
		}
	}
	for (int i(0); i < n; i++) {					// Etape 3	

		matAdj[i][i] = 0;							// Remplacement de la diagonale par des 0
	}


	return matAdj;
}


///	FONCTIONS UTILES A DEBOGUER
/// 
void DEBUG_ERR(const char x[]) {
	cerr << x << endl;
}
void DEBUG(const char x[]) {
	cout << x << endl;
}
bool contains(vector<int> v, int x) {
	if (find(v.begin(), v.end(), x) != v.end()){
		return true;
	}
	else {
		return false;
	}
}
void printMatrice(const vector<vector<bool>>& mat, int n) {
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			cout << mat[i][j];
		}cout << endl;
	}cout << endl;
}
void printPbm(const vector<vector<bool>>& mat, int n) {
	cout << "P1\n" << n << " " << n << endl;
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			cout << mat[i][j];
		}cout << endl;
	}cout << endl;
}
