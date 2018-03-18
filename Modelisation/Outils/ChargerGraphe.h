#include <iostream>
#include <fstream>
#include <vector>
#include "../Graphe/Graphe.h"

class ChargerGraphe {
	std::string chemin;
	const std::string sectionSommets;
	const std::string sectionArcs;

	inline void chargerFichier();
	inline void valideFichier();
	inline void initPositionsLignes();
	inline void resetLigneActuelle();
	inline void revenirAuDebut();
	inline void bouclerJusqueLigneVide();
	inline void recupereSommets(Graphe*);

	template<class T>
	inline void bouclerSurLigne(bool(*condition) (const T &, const T  &), const T &a, const T  &b);
	
	unsigned ligneActuelle;
	unsigned ligneSommets;
	unsigned ligneArcs;

	const int ligneDeb = 1;

	// Ligne qui sert de poubelle pour les getLine()
	std::string ligneTmp;
public:
	std::ifstream fichier;

	ChargerGraphe(const std::string &chemin) : chemin(chemin), sectionSommets("sectionSommets"), sectionArcs("sectionArcs") {
		this->resetLigneActuelle();
		this->chargerFichier();
		this->valideFichier();
		this->initPositionsLignes();
	}

	inline void atteindreChaine(const std::string&);
	inline void atteindreLigne(const unsigned&);
	inline Graphe* creationGraphe();

	void split(const string &s, char delim, vector<string> &elems);
	vector<string> split(const string &s, char delim);
};

inline void ChargerGraphe::resetLigneActuelle() {
	this->ligneActuelle = ligneDeb;
}

inline void ChargerGraphe::revenirAuDebut() {
	this->resetLigneActuelle();
	this->fichier.clear();
	this->fichier.seekg(0, this->fichier.beg);
}

inline void ChargerGraphe::bouclerJusqueLigneVide() {
	do {
		getline(this->fichier, ligneTmp);
		this->ligneActuelle++;
	} while (ligneTmp != "");
}

void ChargerGraphe::chargerFichier() {
	this->fichier.open(this->chemin);
}

void ChargerGraphe::valideFichier() {
	if (!fichier.is_open())
		std::cerr << "Erreur lors de l'ouverture du fichier.";
}

bool compareString(const std::string &a, const std::string &b) {
	return a.compare(b) != 0;
}

bool compareInt(const unsigned &a, const unsigned &b) {
	return a != b;
}

template<class T>
void ChargerGraphe::bouclerSurLigne(bool(*condition) (const T &, const T  &), const T &a, const T  &b) {
	do {
		this->ligneActuelle++;
	} while (getline(this->fichier, this->ligneTmp) && condition(a, b));
}

// Lit le fichier jusqu'à rencontrer le stop
void ChargerGraphe::atteindreChaine(const std::string &stop) {
	revenirAuDebut();
	bouclerSurLigne(compareString, this->ligneTmp, stop);
}

// Lit le fichier jusqu'à rencontrer le numéro de ligne
void ChargerGraphe::atteindreLigne(const unsigned &numLigne) {
	if (this->ligneActuelle > numLigne) revenirAuDebut();
	bouclerSurLigne(compareInt, this->ligneActuelle, numLigne);
}

void ChargerGraphe::initPositionsLignes() {
	// Lecture jusqu'à sectionSommets

	this->atteindreChaine(this->sectionSommets);
	// La prochaine ligne est la source, la dernière ligne jusqu'à une ligne vide est le puit
	this->ligneSommets = this->ligneActuelle;

	this->atteindreChaine(this->sectionArcs);
	// Les arcs commencent ici
	this->ligneArcs = this->ligneActuelle;
}

void ChargerGraphe::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		if (item != "")
			elems.push_back(item);
	}
}

vector<string> ChargerGraphe::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void ChargerGraphe::recupereSommets(Graphe *g) {
	this->atteindreLigne(this->ligneSommets);
	getline(this->fichier, this->ligneTmp);
	vector<string> ligne;

	this->bouclerJusqueLigneVide();
	int numLigne = this->ligneActuelle - 1;
	
	do {
		this->atteindreLigne(numLigne);
		getline(this->fichier, ligneTmp);
		if (this->ligneTmp != "") {
			ligne = split(this->ligneTmp, ' ');

			g->creeSommet(ligne[0], std::stoi(ligne[1]), std::stoi(ligne[2]));
		}
		numLigne--;
	} while (numLigne >= this->ligneSommets);
}



inline Graphe* ChargerGraphe::creationGraphe() {
	Graphe *g = new Graphe();
	this->recupereSommets(g);
	return g;
}