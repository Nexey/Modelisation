#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"
#include "../Parcours/ParcoursDFS.h"

using namespace std;

int main() {
	string chemin = "./Data/data_VRPTW_10.gpr";
	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	system("pause");
	cout << *graphe;
	cout << detection_De_Circuit(graphe, graphe->lSommets->valeur);
	system("pause");
}