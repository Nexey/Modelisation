#pragma once
#include <utility>
#include "../Graphe/Maillon.h"
#include "../Main/Erreur.h"
#include "../Graphe/Sommet.h"
#include "../Graphe/Arc.h"

template<class Ar, class So>
class Graphe
{
protected:
	int prochaineClef;
	
public:
	Maillon< Sommet<So> > * 	lSommets;
	Maillon< Arc<Ar, So> > *	lArcs;
	
#pragma region CREATIONS
public:
	//Constructeurs
	Graphe() : prochaineClef(0), lSommets(NULL), lArcs(NULL) {}
	Graphe(const Graphe<Ar, So> & graphe) : Graphe() { this->copie(graphe); }

	//Destructeur
	~Graphe() { this->effaceTout(); }

	/*Operateur =*/
	const Graphe<Ar, So> & operator = (const Graphe<Ar, So> & graphe) { this->effaceTout(); this->copie(graphe); return *this; }


private:
	/*Utile dans copie, permet d'avoir la première clé dispo
	* Lors de la copie de liste (dans un ordre de clé un peu aléatoire)*/
	void majProchaineClef( const int clef) { prochaineClef = max(1+clef,prochaineClef); }

#pragma region SOMMETS
private:
	/*Ne met pas a jour la clé car elle est à chaque fois
	* mise à jours avant l'appel de cette fonction.*/
	Sommet<So> * creeSommet1( const int clef, const So & info);

public:
	Sommet<So> * creeSommet( const So & info) { return creeSommet1( prochaineClef++, info); }
#pragma endregion
	
#pragma region ARCS
private:
	/*Ne met pas a jour la clé car elle est à chaque fois
	* mise à jours avant l'appel de cette fonction.
	* Met quand même à jours le sommet debut et fin.*/
	Arc<Ar, So> * creeArc1(const int clef, const Ar & info, Sommet<So> * debut, Sommet<So> * fin);

public:
	Arc<Ar, So> * creeArc(const Ar & info, Sommet<So> * debut, Sommet<So> * fin) { return creeArc1(prochaineClef++, info, debut, fin); }
#pragma endregion
	
#pragma region COPIE
	/*Au départ, le graphe this est vide.
	* Crée une copie de chaques sommets et chaques arcs.*/
	void copie(const Graphe<Ar, So> & graphe);

	Sommet<So> * creeSommet(const int clef, const So & info) { majProchaineClef(clef); return creeSommet1(clef, info); }

	Arc<Ar, So> * creeArc(const int clef, const Ar & info, Sommet<So> * debut, Sommet<So> * fin) {	majProchaineClef(clef);	return creeArc1(clef, info, debut, fin); }
	
	/*Utilisé par l'operateur = et par le destructeur*/
	void effaceTout();
#pragma endregion

#pragma endregion

#pragma region CONSULTATION
	//simple
	int nombreSommets() const { return Maillon< Sommet<So> >::taille(lSommets); }
	int nombreArcs() const { return Maillon< Arc<Ar, So> >::taille(lArcs); }

	//compliqué
	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > > *	adjacences(const Sommet<So> * sommet) const;
	Maillon< Arc<Ar, So> > *							arcsAdjacents(const Sommet<So> * sommet) const;
	Maillon< Sommet<So> > *							voisins(const Sommet<So> * sommet) const;

	/*Recherche un arc à partir d'un sommet (debut et fin confondu)*/
	Arc<Ar, So> * getArcParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const;

	//OPERATORS
	operator string() const;
#pragma endregion
};

#pragma region OPERATORS
template <class Ar, class So>
ostream & operator << (ostream & os, const Graphe<Ar, So> & gr) { return os << (string)gr; }

template <class Ar, class So>
Graphe<Ar, So>::operator string() const
{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->prochaineClef << endl;
	oss << "nombre de sommets = " << this->nombreSommets() << "\n";

	oss << Maillon<Sommet<So> >::toString(lSommets, "", "\n", "\n");

	oss << "nombre d'arcs = " << this->nombreArcs() << "\n";

	oss << Maillon<Arc<Ar, So> >::toString(lArcs, "", "\n", "\n");
	oss << ")";
	return oss.str();
}

/*Operateur = et destruceur*/
template <class Ar, class So>
void Graphe<Ar, So>::effaceTout()
{
	Maillon< Arc<Ar, So>>::efface2(this->lArcs);
	Maillon<Sommet<So> >::efface2(this->lSommets);
	this->prochaineClef = 0;
}
#pragma endregion

#pragma region CREATIONS
template <class Ar, class So>
Sommet<So> * Graphe<Ar, So>::creeSommet1(const int clef, const So & info)
{
	Sommet<So> * sommetCree = new Sommet<So>(clef, info);
	lSommets = new Maillon< Sommet<So> >(sommetCree, lSommets);

	return sommetCree;
}


template <class Ar, class So>
Arc<Ar, So> * Graphe<Ar, So>::creeArc1(const int clef, const Ar & info, Sommet<So> * debut, Sommet<So> * fin)
{
	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!Maillon< Sommet<So> >::appartient(debut, lSommets)) throw Erreur("debut d'arc non defini");
	if (!Maillon< Sommet<So> >::appartient(fin, lSommets)) throw Erreur("fin d'arc non definie");

	Arc<Ar, So> *  nouvelArc = new Arc<Ar, So>(clef, info, debut, fin);

	lArcs = new Maillon< Arc<Ar, So> >(nouvelArc, lArcs);

	return nouvelArc;
}
#pragma endregion

#pragma region COPIE
/*Foncteur pour la recherche dans une liste Maillon.
* Remplace l'operateur == des pointeurs par une comparaison des clefs*/
template <class So>
class SommetDejaPresentDansLaCopie
{
public:
	const Sommet<So> * s;

	SommetDejaPresentDansLaCopie(const Sommet<So> * s) :s(s) {}

	bool operator () (const Sommet<So> * sommet) const { return sommet->clef == s->clef; }
};

template <class Ar, class So>
void Graphe<Ar, So>::copie(const Graphe<Ar, So> & graphe)
{
	const Maillon<Sommet<So>> * pS;

	// -------------- d'abord on recopie les sommets --------------------

	for (pS = graphe.lSommets; pS; pS = pS->s)
	{
		const Sommet<So> * sommet = pS->v;				// sommet courant a recopier
		this->creeSommet(sommet->clef, sommet->v);		// on cree la copie du sommet courant avec la meme clef
	}


	// -------------------- et maintenant on recopie les arcs --------------------

	// attention, la recopie des arcs est plus compliquee car il faut rebrancher les arcs sur les nouveaux sommets qui viennent d'etre crees.
	// Pour retrouver les "bons sommets" on utilise les clefs qui ont ete conservees

	const Maillon<Arc<Ar, So>> * pA;
	for (pA = graphe.lArcs; pA; pA = pA->s)
	{
		const Arc<Ar, So> * a = pA->v;			// arc courante a recopier
		Sommet<So> * d, *f;						// le debut et la fin de le nouvel arc qui va etre creee
		Maillon< Sommet<So> > * p;

		// on recherche d dans la nouvelle liste de sommets grace a sa clef
		SommetDejaPresentDansLaCopie<So> conditionDebut(a->debut);
		p = Maillon< Sommet<So> >::appartient(lSommets, conditionDebut);
		d = p->v;

		// on recherche f dans la nouvelle liste de sommets grace a sa clef
		SommetDejaPresentDansLaCopie<So> conditionFin(a->fin);
		p = Maillon< Sommet<So> >::appartient(lSommets, conditionFin);
		f = p->v;

		this->creeArc(a->clef, a->v, d, f);
	}
}


#pragma endregion

#pragma region CONSULTATION
template <class Ar, class So>
Maillon< pair< Sommet<So> *, Arc<Ar, So>* > >  *  Graphe<Ar, So>::adjacences(const Sommet<So> * sommet) const
{
	const Maillon< Arc<Ar, So> > * l;

	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > > * r;				// pair< Sommet<So> *, Arc<Ar,So>* >

	for (l = lArcs, r = NULL; l; l = l->s)

		if (sommet == l->v->debut)
			r = new Maillon< pair< Sommet<So> *, Arc<Ar, So>* > >(new pair< Sommet<So> *, Arc<Ar, So>* >(l->v->fin, l->v), r);

	return r;
}


template <class Ar, class So>
Maillon< Arc<Ar, So> > *  Graphe<Ar, So>::arcsAdjacents(const Sommet<So> * sommet) const
{
	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > > * ladj = this->adjacences(sommet);
	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > > * l;

	Maillon< Arc<Ar, So> > * r;

	for (l = ladj, r = NULL; l; l = l->s)
		r = new Maillon< Arc<Ar, So> >(l->v->second, r);

	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > >::efface2(ladj);

	return r;
}


template <class Ar, class So>
Maillon< Sommet<So> > *  Graphe<Ar, So>::voisins(const Sommet<So> * sommet) const
{
	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > > * ladj = this->adjacences(sommet);
	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > > * l;

	Maillon< Sommet<So> > * r;

	for (l = ladj, r = NULL; l; l = l->s)
		r = new Maillon< Sommet<So> >(l->v->first, r);

	Maillon< pair< Sommet<So> *, Arc<Ar, So>* > >::efface2(ladj);

	return r;
}

template <class Ar, class So>
Arc<Ar, So> * Graphe<Ar, So>::getArcParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const
{
	Maillon<Arc<Ar, So> > * l;

	for (l = this->lArcs; l; l = l->s)
		if (l->v->estEgal(s1, s2))
			return l->v;

	return NULL;
}
#pragma endregion