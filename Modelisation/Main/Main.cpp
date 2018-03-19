#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"
#include "../Parcours/ParcoursDFS.h"

using namespace std;

bool aucuneValuationNegative(Maillon<Arc> *lArc) {
	if (lArc != NULL) {
		if (lArc->valeur->cout < 0 || lArc->valeur->temps < 0) return false;
		return aucuneValuationNegative(lArc->suivant);
	}
	// On est arrivé à la fin de la liste des arcs, donc on peut renvoyer true
	return true;
}

int main() {
	string chemin = "./Data/circuit.txt";

	//string chemin = "./Data/data_VRPTW_160_10_5_10.gpr";
	//string chemin = "./Data/data_VRPTW_10.gpr";

	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	//system("pause");
	//cout << *graphe << endl;
	cout << (aucuneValuationNegative(graphe->lArcs)?"Il n'y a pas de valuations négatives.":"Il existe au moins une valuation négative.") << endl;
	//cout << detection_De_Circuit(graphe, graphe->lSommets->valeur) << endl;
	system("pause");
}