#include <iostream>
#include <fstream>

class ChargerGraphe {
	std::string chemin;
	inline void chargerFichier();
	inline void valideFichier();
public:
	std::ifstream fichier;

	ChargerGraphe(const std::string &chemin) : chemin(chemin){
		chargerFichier();
		valideFichier();
	}

	inline void lireFichier();
	
};

void ChargerGraphe::chargerFichier() {
	this->fichier.open(this->chemin);
}

void ChargerGraphe::valideFichier() {
	if (!fichier.is_open())
		std::cerr << "Erreur lors de l'ouverture du fichier.";
}

void ChargerGraphe::lireFichier() {
	std::ifstream tmp(this->chemin);

	std::string ligne;

	std::cout << "Lecture du fichier en entier :\n\n";

	while (getline(tmp, ligne)) {
		std::cout << ligne << '\n';
	}
}