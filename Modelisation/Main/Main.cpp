//#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"
//#include "../Algorithmes/ParcoursDFS.h"
#include "../Algorithmes/Dijkstra.h"

using namespace std;

int main() {
	//string chemin = "./Data/circuit.txt";
	//string chemin = "./Data/data_VRPTW_160_10_5_10.gpr";
	string chemin = "./Data/data_VRPTW_10.gpr";



	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	//system("pause");
	//cout << *graphe << endl;

	cout << (aucuneValuationNegative(graphe->lArcs) ? "Il n'y a pas de valuations negatives." : "Il existe au moins une valuation negative.") << endl;

	cout << dijkstra(graphe, coutArc) << endl << endl;
	cout << dijkstra(graphe, tempsArc) << endl;
	system("pause");
}