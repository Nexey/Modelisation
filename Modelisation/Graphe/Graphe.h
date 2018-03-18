#pragma once
#include <utility>
#include "../Graphe/Maillon.h"
#include "../Main/Erreur.h"
#include "../Graphe/ElementsGraphe.h

class Graphe
{
public:
	Maillon< Sommet > * 	lSommets;
	Maillon< Arc > *	lArcs;
	
#pragma region CREATIONS
	//Constructeurs
	Graphe() : lSommets(NULL), lArcs(NULL) {}

	//Destructeur
	~Graphe() { this->effaceTout(); }

    	/*Utilisé par l'operateur = et par le destructeur*/
    	void effaceTout();



	Sommet * creeSommet(int borneInf, int borneSup);
	Arc * creeArc(int cout, int temps, Sommet * debut, Sommet * fin);


#pragma region CONSULTATION
	//simple
	int nombreSommets() const { return Maillon< Sommet >::taille(lSommets); }
	int nombreArcs() const { return Maillon< Arc >::taille(lArcs); }

	//compliqué
	Maillon< pair< Sommet *, Arc* > > *	adjacences(const Sommet * sommet) const;
	Maillon< Arc > *							arcsAdjacents(const Sommet * sommet) const;
	Maillon< Sommet > *							voisins(const Sommet * sommet) const;

	/*Recherche un arc à partir d'un sommet*/
	Arc * getArcParSommets(const Sommet * debut, const Sommet * fin) const;

	//OPERATORS
	operator string() const;
#pragma endregion
};

#pragma region OPERATORS
ostream & operator << (ostream & os, const Graphe & gr) { return os << (string)gr; }

Graphe::operator string() const
{
	ostringstream oss;
	oss << "Graphe[ \n";
	oss << "nombre de sommets = " << this->nombreSommets() << "\n";
	oss << Maillon<Sommet >::toString(lSommets, "", "\n", "\n");
	oss << "nombre d'arcs = " << this->nombreArcs() << "\n";
	oss << Maillon<Arc >::toString(lArcs, "", "\n", "\n");
	oss << "]";
	return oss.str();
}

/*Operateur = et destruceur*/
void Graphe::effaceTout()
{
	Maillon< Arc>::efface2(this->lArcs);
	Maillon<Sommet >::efface2(this->lSommets);
}
#pragma endregion

#pragma region CREATIONS
Sommet * Graphe::creeSommet(int borneInf, int borneSup)
{
	Sommet * sommetCree = new Sommet(borneInf, borneSup);
	lSommets = new Maillon< Sommet >(sommetCree, lSommets);

	return sommetCree;
}


Arc * Graphe::creeArc(int cout, int temps, Sommet * debut, Sommet * fin)
{
	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!Maillon< Sommet >::appartient(debut, lSommets)) throw Erreur("debut d'arc non defini");
	if (!Maillon< Sommet >::appartient(fin, lSommets)) throw Erreur("fin d'arc non definie");

	Arc *  nouvelArc = new Arc(cout, temps, debut, fin);

	lArcs = new Maillon< Arc >(nouvelArc, lArcs);

	return nouvelArc;
}
#pragma endregion


#pragma region CONSULTATION
Maillon< pair< Sommet *, Arc* > >  *  Graphe::adjacences(const Sommet * sommet) const
{
	const Maillon< Arc > * l;

	Maillon< pair< Sommet *, Arc* > > * r;				// pair< Sommet *, Arc* >

	for (l = lArcs, r = NULL; l; l = l->suivant)

		if (sommet == l->valeur->debut)
			r = new Maillon< pair< Sommet *, Arc* > >(new pair< Sommet *, Arc* >(l->valeur->fin, l->valeur), r);

	return r;
}


Maillon< Arc > *  Graphe::arcsAdjacents(const Sommet * sommet) const
{
	const Maillon< Arc > * l;

	Maillon< Arc> * r;				// pair< Sommet *, Arc* >

	for (l = lArcs, r = NULL; l; l = l->suivant)
		if (sommet == l->valeur->debut)
			r = new Maillon< Arc >(l->valeur, r);

	return r;
}


Maillon< Sommet > *  Graphe::voisins(const Sommet * sommet) const
{
	const Maillon< Arc > * l;

	Maillon< Sommet> * r;				// pair< Sommet *, Arc* >

	for (l = lArcs, r = NULL; l; l = l->suivant)
		if (sommet == l->valeur->debut)
			r = new Maillon< Sommet >(l->valeur->fin, r);

	return r;
}

Arc * Graphe::getArcParSommets(const Sommet * debut, const Sommet * fin) const
{
	Maillon<Arc > * l;

	for (l = this->lArcs; l; l = l->suivant)
		if (l->valeur->estEgal(debut, fin))
			return l->valeur;

	return NULL;
}
#pragma endregion