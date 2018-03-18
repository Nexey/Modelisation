#include <iostream>
#include <fstream>
#include <vector>
#include "../Graphe/Graphe.h"

class ChargerGraphe {
	std::string chemin;
	const std::string sectionSommets;
	const std::string sectionArcs;
	unsigned ligneActuelle;
	unsigned ligneSommets;
	unsigned ligneArcs;

	const int ligneDeb = 1;

	// Ligne qui sert de poubelle pour les getLine()
	std::string ligneTmp;

	inline void chargerFichier();
	inline void valideFichier();
	inline void initPositionsLignes();
	inline void resetLigneActuelle();
	inline void revenirAuDebut();
	inline void bouclerJusqueLigneVide();

	inline Sommet *recupereSommet(Maillon<Sommet> *lSommets, const string nom);
	inline void recupereSommets(Graphe*);
	inline void recupereArcs(Graphe*);

	inline void atteindreChaine(const std::string&);
	inline void atteindreLigne(const unsigned&);

	void eclater(const string &s, char delim, vector<string> &elems);
	vector<string> eclater(const string &s, char delim);

	template<class T>
	inline void bouclerSurLigne(bool(*condition) (const T &, const T  &), const T &a, const T  &b);
	
public:
	std::ifstream fichier;

	ChargerGraphe(const std::string &chemin) : chemin(chemin), sectionSommets("sectionSommets"), sectionArcs("sectionArcs") {
		this->resetLigneActuelle();
		this->chargerFichier();
		this->valideFichier();
		this->initPositionsLignes();
	}

	inline Graphe* creationGraphe();
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
	//if (this->ligneActuelle > numLigne)
		revenirAuDebut();
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

void ChargerGraphe::eclater(const string &ligne, char delim, vector<string> &mots) {
	stringstream ligneStream(ligne);
	string mot;
	while (getline(ligneStream, mot, delim)) {
		if (mot != "")
			mots.push_back(mot);
	}
}

vector<string> ChargerGraphe::eclater(const string &ligne, char delim) {
	vector<string> mots;
	eclater(ligne, delim, mots);
	return mots;
}

void ChargerGraphe::recupereSommets(Graphe *g) {
	this->atteindreLigne(this->ligneSommets);
	getline(this->fichier, this->ligneTmp);
	vector<string> mots;

	this->bouclerJusqueLigneVide();
	unsigned numLigne = this->ligneActuelle - 1;
	
	do {
		this->atteindreLigne(numLigne);
		getline(this->fichier, ligneTmp);
		if (this->ligneTmp != "") {
			mots = eclater(this->ligneTmp, ' ');

			g->creeSommet(mots[0], std::stoi(mots[1]), std::stoi(mots[2]));
		}
		numLigne--;
	} while (numLigne >= this->ligneSommets);
}

Sommet *ChargerGraphe::recupereSommet(Maillon<Sommet> *lSommets, const string nom) {
	if (lSommets->valeur->nom == nom)
		return lSommets->valeur;
	else
		return recupereSommet(lSommets->suivant, nom);
}

inline void ChargerGraphe::recupereArcs(Graphe *g) {
	this->atteindreLigne(this->ligneArcs);
	vector<string> mots;
	do {
		getline(this->fichier, ligneTmp);
		if (this->ligneTmp != "") {
			mots = eclater(this->ligneTmp, ' ');

			g->creeArc(mots[0], std::stoi(mots[3]), std::stoi(mots[4]),
				recupereSommet(g->lSommets, mots[1]),
				recupereSommet(g->lSommets, mots[2])
			);
		}
	} while (this->ligneTmp != "");
}

inline Graphe* ChargerGraphe::creationGraphe() {
	Graphe *g = new Graphe();
	this->recupereSommets(g);
	this->recupereArcs(g);
	return g;
}