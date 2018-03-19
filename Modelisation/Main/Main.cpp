#include "../Outils/ChargerGraphe.h"
#include "../Algorithmes/ParcoursDFS.h"
#include "../Algorithmes/Dijkstra.h"
#include <string>
#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;


int main(int argc, char *argv[]) {
	string chemin("./Data/data_VRPTW_10.gpr");
	vector<string> v;

	if (argc > 1) chemin = argv[1];
	else {
		string path = "./Data";
		for (auto & p : fs::directory_iterator(path))
			v.push_back(p.path().string());

		for (unsigned i = 0; i < v.size(); i++)
			cout << i + 1 << ")\t" << v[i] << endl;

		unsigned choix;
		do {
			cout << "Entrez le numero du fichier a tester [1 - " << v.size() << "]\t";
			cin >> choix;
			if (choix < 1 || choix > v.size()) cout << "Le numero doit etre compris entre 1 et " << v.size() << "." << endl;
		} while (choix < 1 || choix > v.size());

		chemin = v[choix - 1];
	}

	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	cout << endl << *graphe << endl;

	//system("pause");
	cout << (detection_De_Circuit(graphe, graphe->lSommets->valeur) ? "Il existe un circuit." : "Il n'existe aucun circuit.") << endl;

	//system("pause");
	cout << endl << "Algorithme de Dijkstra avec le cout :" << endl << dijkstra(graphe, coutArc) << endl << endl;
	
	system("pause");
	cout << "Algorithme de Dijkstra avec le temps :" << endl << dijkstra(graphe, tempsArc) << endl;
	system("pause");
}