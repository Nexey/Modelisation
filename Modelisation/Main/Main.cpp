#include "../Outils/ChargerGraphe.h"
#include "../Algorithmes/ParcoursDFS.h"
#include "../Algorithmes/Dijkstra.h"
#include "../Algorithmes/Ford.h"
using namespace std;

int main(int argc, char *argv[]) {

	ChargerGraphe infosGraphe(detectionChemin(argc, argv));

	Graphe *graphe = infosGraphe.creationGraphe();
	
	cout << endl << *graphe << endl;
	
	cout << "Algorithme de detection de circuit :" << endl;
	system("pause");
	cout << endl << (detection_De_Circuit(graphe, graphe->lSommets->valeur) ? "Il existe un circuit." : "Il n'existe aucun circuit.") << endl;

	cout << endl << "Algorithme de Dijkstra avec le cout :" << endl;
	system("pause");
	cout << endl << dijkstra(graphe, coutArc) << endl << endl;

	cout << endl << "Algorithme de Dijkstra avec le temps :" << endl;
	system("pause");
	cout << endl << dijkstra(graphe, tempsArc) << endl << endl;
	
	cout << "Algorithme de Ford avec le cout :" << endl;
	system("pause");
	cout << endl << Ford(graphe, graphe->lSommets->valeur);

	cout << endl << endl << "Fin du programme." << endl;
	system("pause");
}