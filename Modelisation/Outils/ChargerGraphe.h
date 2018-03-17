#include <iostream>
#include <fstream>

class ChargerGraphe {
	std::string chemin;
	inline void chargerFichier();
	inline void valideFichier();
	inline void initPositionsLignes();
	inline void resetLigneActuelle();
	inline void revenirAuDebut();

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

	ChargerGraphe(const std::string &chemin) : chemin(chemin) {
		this->resetLigneActuelle();
		this->chargerFichier();
		this->valideFichier();
		this->initPositionsLignes();
	}

	inline void atteindreChaine(const std::string&);
	inline void atteindreLigne(const unsigned&);
};

inline void ChargerGraphe::resetLigneActuelle() {
	this->ligneActuelle = ligneDeb;
}

inline void ChargerGraphe::revenirAuDebut() {
	this->resetLigneActuelle();
	this->fichier.clear();
	this->fichier.seekg(0, this->fichier.beg);
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
	if (numLigne > this->ligneActuelle) revenirAuDebut();
	bouclerSurLigne(compareInt, this->ligneActuelle, numLigne);
}

inline void ChargerGraphe::initPositionsLignes() {
	// Lecture jusqu'à sectionSommets
	const std::string sectionSommets("sectionSommets");
	const std::string sectionArcs("sectionArcs");

	this->atteindreChaine(sectionSommets);
	// La prochaine ligne est la source, la dernière ligne jusqu'à une ligne vide est le puit	this->ligneSommets = this->ligneActuelle;
	this->ligneSommets = this->ligneActuelle;

	this->atteindreChaine(sectionArcs);
	// Les arcs commencent ici
	this->ligneArcs = this->ligneActuelle;
}