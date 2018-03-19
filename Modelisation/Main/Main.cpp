#include "../Outils/ChargerGraphe.h"
//#include "../Algorithmes/ParcoursDFS.h"
#include "../Algorithmes/Dijkstra.h"
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;


int main() {
	string chemin;
	vector<string> v;

	string path = "./Data";
	for (auto & p : fs::directory_iterator(path))
		v.push_back(p.path().string());

	for (unsigned i = 0; i < v.size(); i++)
		cout << i << ")\t" << v[i] << endl;

	unsigned choix;
	do {
		cout << "Entrez le numero du fichier a tester [0 - " << v.size() << "]\t";
		cin >> choix;
		if (choix < 0 || choix >= v.size()) cout << "Le numero doit etre compris entre 0 et " << v.size() << "." << endl;
	} while (choix < 0 || choix >= v.size());

	chemin = v[choix];

	ChargerGraphe infosGraphe(chemin);

	Graphe *graphe = infosGraphe.creationGraphe();
	
	//system("pause");
	cout << endl << *graphe << endl;

	//cout << (aucuneValuationNegative(graphe->lArcs) ? "Il n'y a pas de valuations negatives." : "Il existe au moins une valuation negative.") << endl;

	//cout << dijkstra(graphe, coutArc) << endl << endl;
	//cout << dijkstra(graphe, tempsArc) << endl;
	system("pause");
}