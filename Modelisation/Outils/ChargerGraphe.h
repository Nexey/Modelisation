#include <iostream>
#include <fstream>

class ChargerGraphe {
	std::string chemin;
	inline void chargerFichier();
	inline void valideFichier();
	inline void initFichier();
public:
	std::ifstream fichier;

	ChargerGraphe(const std::string &chemin) : chemin(chemin){
		this->chargerFichier();
		this->valideFichier();
		this->initFichier();
	}

	inline void lireFichier(const std::string &);
	
};

void ChargerGraphe::chargerFichier() {
	this->fichier.open(this->chemin);
}

void ChargerGraphe::valideFichier() {
	if (!fichier.is_open())
		std::cerr << "Erreur lors de l'ouverture du fichier.";
}

void ChargerGraphe::lireFichier(const std::string &stop) {
	std::ifstream tmp(this->chemin);

	std::string ligne;

	std::cout << "Lecture du fichier en entier :\n\n";

	while (getline(/*tmp*/ this->fichier, ligne) && ligne.compare(stop) != 0);
		/* std::cout << ligne << '\n';*/
}

inline void ChargerGraphe::initFichier() {
	// Lecture jusqu'à sectionSommets
	const std::string sectionSommets("sectionSommets");
	const std::string sectionArcs("sectionArcs");
	this->lireFichier(sectionSommets);
	string test;
	getline(this->fichier, test);
	cout << test << std::endl;
}