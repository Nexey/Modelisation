#include "../Graphe/Graphe.h"
#include "../Outils/ChargerGraphe.h"

using namespace std;

int main() {
	string chemin = "./Data/data_VRPTW_10.gpr";
	ChargerGraphe infosGraphe(chemin);

	Graphe<Arc<int, int>, Sommet<int>> graphe;

	graphe.creeSommet(Sommet<int>(0));
	graphe.creeSommet(Sommet<int>(1));
	graphe.creeArc(4, (&graphe)->lSommets->v, (&graphe)->lSommets->s->v);

	system("pause");
}