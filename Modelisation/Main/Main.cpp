#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"
#include "../Algorithmes/ParcoursDFS.h"
#include "../Algorithmes/Dijkstra.h"

using namespace std;


int main() {
	string chemin = "./Data/circuit.txt";

	//string chemin = "./Data/data_VRPTW_160_10_5_10.gpr";
	//string chemin = "./Data/data_VRPTW_10.gpr";

	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	//system("pause");
	//cout << *graphe << endl;
	cout << (Dijkstra::aucuneValuationNegative(graphe->lArcs)?"Il n'y a pas de valuations n�gatives.":"Il existe au moins une valuation n�gative.") << endl;
	//cout << detection_De_Circuit(graphe, graphe->lSommets->valeur) << endl;
	system("pause");
}