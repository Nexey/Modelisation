#include <iostream>
#include <fstream>

class ChargerGraphe {
	std::string chemin;
	inline void chargerFichier();
	inline void valideFichier();
	inline void initFichier();
	inline void resetLigneActuelle();
	
	unsigned ligneActuelle;
	unsigned ligneSommets;
	unsigned ligneArcs;

public:
	std::ifstream fichier;

	ChargerGraphe(const std::string &chemin) : chemin(chemin) {
		this->resetLigneActuelle();
		this->chargerFichier();
		this->valideFichier();
		this->initFichier();
	}

	inline void lireFichier(const std::string&);
	inline void lireFichierDuDebut(const std::string&);
};

void ChargerGraphe::chargerFichier() {
	this->fichier.open(this->chemin);
}

void ChargerGraphe::valideFichier() {
	if (!fichier.is_open())
		std::cerr << "Erreur lors de l'ouverture du fichier.";
}

// Lit le fichier jusqu'à rencontrer le stop
// Attention, la prochaine lecture reprend là où elle s'était précédemment arrêtée
void ChargerGraphe::lireFichier(const std::string &stop) {
	std::string ligne;
	while (getline(this->fichier, ligne) && ligne.compare(stop) != 0) this->ligneActuelle++;
}

void ChargerGraphe::lireFichierDuDebut(const std::string &stop) {
	this->ligneActuelle = 0;
	this->fichier.clear();
	this->fichier.seekg(0, this->fichier.beg);
	lireFichier(stop);
}

inline void ChargerGraphe::initFichier() {
	// Lecture jusqu'à sectionSommets
	const std::string sectionSommets("sectionSommets");
	const std::string sectionArcs("sectionArcs");

	this->lireFichier(sectionSommets);
	// La prochaine ligne est la source, la dernière ligne jusqu'à une ligne vide est le puits
	this->ligneSommets = this->ligneActuelle;

	this->lireFichier(sectionArcs);
	this->ligneArcs = this->ligneActuelle;
}

inline void ChargerGraphe::resetLigneActuelle() {
	this->ligneActuelle = 1;
}
