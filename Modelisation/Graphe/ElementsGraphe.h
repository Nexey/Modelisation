#pragma once

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Sommet {
public:
	int degre;
	int inf;
	int sup;

	string nom;

    int etiquette;
	//info = valuation du sommet : poids arete ascendante + valuation sommmet pere
	Sommet* pere;

	Sommet(const string& nom, int borneInf, int borneSup) : degre(0), nom(nom), inf(borneInf), sup(borneSup) {}

    	Sommet(const Sommet& copie):degre(0), nom(copie.nom), inf(copie.inf), sup(copie.sup){}

	operator string () const;

	bool equals(const Sommet *s){
		if((degre == s->degre) && (inf == s->inf) && (sup == s->sup) && (nom.compare(s->nom)) && (etiquette == s->etiquette) && (pere == s->pere))
			return true;
		return false;
	}
};


class Arc {
private:
    //Interdiction de la construction par copie
    //(les sommets debut et fin ne peuvent pas être ceux de l'Arc "copie"
    //ni créer 2 sommets qui ne corresponderont à rien
    Arc(const Arc& copie){}
public:
	Sommet * debut, *fin;

	int coutArc;
	int tempsArc;

	string nom;

	Arc(const string& nom, int coutArc, int tempsArc, Sommet * debut, Sommet * fin) : nom(nom), coutArc(coutArc), tempsArc(tempsArc), debut(debut), fin(fin) {
		debut->degre++;
		fin->degre++;
		debut->pere = fin;
	}

    	Arc(const Arc& copie, Sommet* newDebut, Sommet* newFin): nom(copie.nom), coutArc(copie.coutArc), tempsArc(copie.tempsArc), debut(newDebut), fin(newFin){

	}

	~Arc() { debut->degre--; fin->degre--; }

	operator string () const;

	bool estEgal(const Sommet * debut, const Sommet * fin) const;
};

//#########SOMME
Sommet::operator string () const {
	ostringstream oss;
	oss << "Sommet[";
	oss << "nom: " << nom << ";   ";
	oss << "degre: " << degre << ";   ";
	oss << "inf: " << inf << ";   ";
	oss << "sup: " << sup;
	oss << "]";
	return oss.str();
}

ostream & operator << (ostream & os, const Sommet & sommet) {
	return os << (string)sommet;
}

//#########ARC
Arc::operator string () const {
	ostringstream oss;
	oss << "Arc[";
	oss << "nom: " << nom << ";   ";
	oss << "cout: " << coutArc << ";   ";
	oss << "temps: " << tempsArc << ";   ";
	oss << "debut: " << *debut << ";   ";
	oss << "fin: " << *fin;
	oss << "]";
	return oss.str();
}

ostream & operator << (ostream & os, const Arc& arc) {
	return os << (string)arc;
}

bool Arc::estEgal(const Sommet * deb, const Sommet * fi) const {
	// Attention : Nous sommes dans un graphe orienté, et donc s1 doit être le début et s2 la fin
	return deb == debut && fi == fin;
}