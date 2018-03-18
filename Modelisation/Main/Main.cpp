#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"

using namespace std;

int main() {
	string chemin = "./Data/data_VRPTW_10.gpr";
	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	cout << *graphe;
	//graphe->creeArc(4, 4, (graphe)->lSommets->valeur, (graphe)->lSommets->suivant->valeur);

	system("pause");
}