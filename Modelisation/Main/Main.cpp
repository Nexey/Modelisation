#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"

using namespace std;

int main() {
	string chemin = "./Data/data_VRPTW_10.gpr";
	ChargerGraphe infosGraphe(chemin);

	system("pause");
}