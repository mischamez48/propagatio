#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>>lire_matrice(int n);
void check(int i, vector<bool>& visited ,vector<vector<bool>> matAdj, int n);
vector<vector<bool>> tache_1(unsigned int& n);
void tache_2(vector<vector<bool>>matAdj, int n);
void printMatrice(const vector<vector<bool>>& mat, int n);
void printPbm(const vector<vector<bool>>& mat, int n);
void DEBUG_ERR(const char x[]);
void DEBUG(const char x[]);
vector<vector<bool>>construire_matAdj(const vector<vector<bool>>& MatInit, int n);

int main() {
	unsigned int n(0);	// Colonnes


	vector<vector<bool>>matAdj = tache_1(n);

	tache_2(matAdj, n);

}



vector<vector<bool>> tache_1(unsigned int& n) {

	char pbm[3];			// Par convention les tableaux de char se terminent par le delimiteur '\0' prenant donc la derniere pos du tableau
	unsigned int m(0);		// Lignes

	cin >> pbm;
	if (!(pbm[0] == 'P' && pbm[1] == '1' && pbm[2] == '\0')) { //3.2.1.2
		exit(0);
	}
	//DEBUG(pbm);

	cin >> n >> m;
	if (n != m || n <= 0 || m <= 0) {// colonnes et lignes doivent être positifs
		DEBUG_ERR("Entree infos d'entete incorrectes");
		exit(0);
	}



	//printMatrice(lire_matrice(n), n);

	return construire_matAdj(lire_matrice(n), n);
}

void tache_2(vector<vector<bool>> matAdj, int n) {
	vector<bool> visited(n);
	for (int i(0); i < n; i++) {
		visited[i] = false;
	}

	check(0, visited, matAdj, n);

	for (int i(0); i < n; i++) {
		if (visited[i] == false) {
			DEBUG_ERR("DO ERROR MSG 3.1.2");
			exit(0);
		}
	}

	DEBUG("PLS HELP ME");
}


vector<vector<bool>>lire_matrice(int n) {

	//TODO Prendre les erreurs sur le fichier error.txt def page 7 du pdf

	vector<vector<bool>>matInit(n, vector<bool>(n, true)); //initialise à blanc

	unsigned int input;
	for (size_t i(0); i < matInit.size(); ++i) {
		for (size_t j(0); j < matInit.size(); ++j) {
			cin >> input;
			if (input > 1) {						// Si la valeur donnée en input n'est pas de type bool
				DEBUG_ERR("valeur incorrecte");		// Avertir et imprimer erreur
				exit(0);
			}
			matInit[i][j] = input;					// Place les 0 et 1 dans matrice (pas besoin de cast)
		}
	}
	return matInit;									// Retourne la matrice du fichier pre-adj
}

void check(int i, vector<bool>& visited, vector<vector<bool>> matAdj, int n) {
	visited[i] = true;
	for (int j = 0; j < n; j++) {
		if (matAdj[i][j] == true && visited[j] == false) {
			check(j, visited, matAdj, n);
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


/*
* Fonctions constantes utiles pour déboguer
*/
void DEBUG_ERR(const char x[]) {
	cerr << x << endl;
}
void DEBUG(const char x[]) {
	cout << x << endl;
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