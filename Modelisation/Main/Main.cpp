#include "../Outils/ChargerGraphe.h"
//#include "../Algorithmes/ParcoursDFS.h"
#include "../Algorithmes/Dijkstra.h"
#include <string>
#include <iostream>
#include <filesystem>
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
			if (choix < 1 || choix >= v.size()) cout << "Le numero doit etre compris entre 0 et " << v.size() << "." << endl;
		} while (choix < 1 || choix >= v.size());

		chemin = v[choix - 1];
	}

	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	//system("pause");
	cout << endl << *graphe << endl;

	//cout << (aucuneValuationNegative(graphe->lArcs) ? "Il n'y a pas de valuations negatives." : "Il existe au moins une valuation negative.") << endl;

	//cout << dijkstra(graphe, coutArc) << endl << endl;
	//cout << dijkstra(graphe, tempsArc) << endl;
	system("pause");
}