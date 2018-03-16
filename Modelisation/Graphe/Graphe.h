#pragma once
#include <utility>
#include "../Graphe/Maillon.h"
#include "../Main/Erreur.h"
#include "../Graphe/Sommet.h"
#include "../Graphe/Arete.h"

template<class Ar, class So>
class Graphe
{
protected:
	int prochaineClef;
	
public:
	Maillon< Sommet<So> > * 	lSommets;
	Maillon< Arete<Ar, So> > *	lAretes;
	
#pragma region CREATIONS
public:
	//Constructeurs
	Graphe() : prochaineClef(0), lSommets(NULL), lAretes(NULL) {}
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
	
#pragma region ARETES
private:
	/*Ne met pas a jour la clé car elle est à chaque fois
	* mise à jours avant l'appel de cette fonction.
	* Met quand même à jours le sommet debut et fin.*/
	Arete<Ar, So> * creeArete1(const int clef, const Ar & info, Sommet<So> * debut, Sommet<So> * fin);

public:
	Arete<Ar, So> * creeArete(const Ar & info, Sommet<So> * debut, Sommet<So> * fin) { return creeArete1(prochaineClef++, info, debut, fin); }
#pragma endregion
	
#pragma region COPIE
	/*Au départ, le graphe this est vide.
	* Crée une copie de chaques sommets et chaques aretes.*/
	void copie(const Graphe<Ar, So> & graphe);

	Sommet<So> * creeSommet(const int clef, const So & info) { majProchaineClef(clef); return creeSommet1(clef, info); }

	Arete<Ar, So> * creeArete(const int clef, const Ar & info, Sommet<So> * debut, Sommet<So> * fin) {	majProchaineClef(clef);	return creeArete1(clef, info, debut, fin); }
	
	/*Utilisé par l'operateur = et par le destructeur*/
	void effaceTout();
#pragma endregion

#pragma endregion

#pragma region CONSULTATION
	//simple
	int nombreSommets() const { return Maillon< Sommet<So> >::taille(lSommets); }
	int nombreAretes() const { return Maillon< Arete<Ar, So> >::taille(lAretes); }

	//compliqué
	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > > *	adjacences(const Sommet<So> * sommet) const;
	Maillon< Arete<Ar, So> > *							aretesAdjacentes(const Sommet<So> * sommet) const;
	Maillon< Sommet<So> > *							voisins(const Sommet<So> * sommet) const;

	/*Recherche une arete à partir d'un sommet (debut et fin confondu)*/
	Arete<Ar, So> * getAreteParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const;

	//OPERATORS
	operator string() const;
#pragma endregion

#pragma region DESSIN(visiteur)
	/*Dessine d'abord les aretes, puis les sommets.
	* Renvoie True seulement en cas de succès complet.
	**/
	template< class FENETRE>
	bool dessineToutesAretes(FENETRE & fenetre) const;

	template< class FENETRE>
	bool dessineTousSommets(FENETRE & fenetre) const;

	template  <class FENETRE>
	bool dessine(FENETRE & fenetre) const;
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

	oss << "nombre d'aretes = " << this->nombreAretes() << "\n";

	oss << Maillon<Arete<Ar, So> >::toString(lAretes, "", "\n", "\n");
	oss << ")";
	return oss.str();
}

/*Operateur = et destruceur*/
template <class Ar, class So>
void Graphe<Ar, So>::effaceTout()
{
	Maillon< Arete<Ar, So>>::efface2(this->lAretes);
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
Arete<Ar, So> * Graphe<Ar, So>::creeArete1(const int clef, const Ar & info, Sommet<So> * debut, Sommet<So> * fin)
{
	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!Maillon< Sommet<So> >::appartient(debut, lSommets)) throw Erreur("debut d'arete non defini");
	if (!Maillon< Sommet<So> >::appartient(fin, lSommets)) throw Erreur("fin d'arete non definie");

	Arete<Ar, So> *  nouvelleArete = new Arete<Ar, So>(clef, info, debut, fin);

	lAretes = new Maillon< Arete<Ar, So> >(nouvelleArete, lAretes);

	return nouvelleArete;
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


	// -------------------- et maintenant on recopie les aretes --------------------

	// attention, la recopie des aretes est plus compliquee car il faut rebrancher les aretes sur les nouveaux sommets qui viennent d'etre crees.
	// Pour retrouver les "bons sommets" on utilise les clefs qui ont ete conservees

	const Maillon<Arete<Ar, So>> * pA;
	for (pA = graphe.lAretes; pA; pA = pA->s)
	{
		const Arete<Ar, So> * a = pA->v;			// arete courante a recopier
		Sommet<So> * d, *f;						// le debut et la fin de la nouvelle arete qui va etre creee
		Maillon< Sommet<So> > * p;

		// on recherche d dans la nouvelle liste de sommets grace a sa clef
		SommetDejaPresentDansLaCopie<So> conditionDebut(a->debut);
		p = Maillon< Sommet<So> >::appartient(lSommets, conditionDebut);
		d = p->v;

		// on recherche f dans la nouvelle liste de sommets grace a sa clef
		SommetDejaPresentDansLaCopie<So> conditionFin(a->fin);
		p = Maillon< Sommet<So> >::appartient(lSommets, conditionFin);
		f = p->v;

		this->creeArete(a->clef, a->v, d, f);
	}
}


#pragma endregion

#pragma region CONSULTATION
template <class Ar, class So>
Maillon< pair< Sommet<So> *, Arete<Ar, So>* > >  *  Graphe<Ar, So>::adjacences(const Sommet<So> * sommet) const
{
	const Maillon< Arete<Ar, So> > * l;

	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > > * r;				// pair< Sommet<So> *, Arete<Ar,So>* >

	for (l = lAretes, r = NULL; l; l = l->s)

		if (sommet == l->v->debut)
			r = new Maillon< pair< Sommet<So> *, Arete<Ar, So>* > >(new pair< Sommet<So> *, Arete<Ar, So>* >(l->v->fin, l->v), r);
		else
			if (sommet == l->v->fin)
				r = new Maillon< pair< Sommet<So> *, Arete<Ar, So>* > >(new pair< Sommet<So> *, Arete<Ar, So>* >(l->v->debut, l->v), r);

	return r;
}


template <class Ar, class So>
Maillon< Arete<Ar, So> > *  Graphe<Ar, So>::aretesAdjacentes(const Sommet<So> * sommet) const
{
	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > > * ladj = this->adjacences(sommet);
	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > > * l;

	Maillon< Arete<Ar, So> > * r;

	for (l = ladj, r = NULL; l; l = l->s)
		r = new Maillon< Arete<Ar, So> >(l->v->second, r);

	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > >::efface2(ladj);

	return r;
}


template <class Ar, class So>
Maillon< Sommet<So> > *  Graphe<Ar, So>::voisins(const Sommet<So> * sommet) const
{
	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > > * ladj = this->adjacences(sommet);
	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > > * l;

	Maillon< Sommet<So> > * r;

	for (l = ladj, r = NULL; l; l = l->s)
		r = new Maillon< Sommet<So> >(l->v->first, r);

	Maillon< pair< Sommet<So> *, Arete<Ar, So>* > >::efface2(ladj);

	return r;
}

template <class Ar, class So>
Arete<Ar, So> * Graphe<Ar, So>::getAreteParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const
{
	Maillon<Arete<Ar, So> > * l;

	for (l = this->lAretes; l; l = l->s)
		if (l->v->estEgal(s1, s2))
			return l->v;

	return NULL;
}
#pragma endregion

#pragma region DESSIN
template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessine(FENETRE & fenetre) const
{

	if (!this->dessineToutesAretes(fenetre)) return false;
	
	return this->dessineTousSommets(fenetre);
}


template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessineToutesAretes(FENETRE & fenetre) const
{
	Maillon< Arete<Ar, So>> * pA;
	for (pA = this->lAretes; pA; pA = pA->s)
		if (!fenetre.dessine(pA->v)) return false; // tente de dessiner puis retourne false en cas d'echec

	return true;
}

template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessineTousSommets(FENETRE & fenetre) const
{
	Maillon< Sommet<So>> * pS;
	for (pS = this->lSommets; pS; pS = pS->s)
		if (!fenetre.dessine(pS->v)) return false;	// tente de dessiner puis retourne false en cas d'echec

	return true;
}


template <class So, class FENETRE>
bool dessine(const Maillon<Sommet<So>> * chemin, FENETRE & fenetre, const unsigned int couleur)
{
	if (!(chemin && chemin->s)) // le chemin est vide ou ne contient qu'un sommet : il n'y  a rien a dessiner
		return true;

	else
	{
		// on dessine d'abord la 1ere arete

		if (!fenetre.dessine(chemin->v, chemin->s->v, couleur)) return false;

		return dessine(chemin->s, fenetre, couleur);		// puis on dessine les aretes suivantes
	}
}
#pragma endregion