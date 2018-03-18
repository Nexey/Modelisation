#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "../Main/Erreur.h"

using namespace std;

template<class Type>
Type max(const Type &a, const Type &b) { return a > b ? a : b; }

template <class Type>
class Maillon {
public:
    	Type * valeur;				// valeur
	Maillon<Type> * suivant;	// suivant

	Maillon(Type * v, Maillon<Type> * s) :valeur(v), suivant(s) {}

	static const string toString(const Maillon<Type> * p, const char * debut = "( ", const char * separateur = ", ", const char * fin = ")");

	static int taille(const Maillon<Type> * l);

	static  Maillon<Type> * copie1(Maillon<Type> * l);

	static  Maillon<Type> * copie2(const Maillon<Type> * l);

	static Maillon<Type> * copie3(const Maillon<Type> * l);

	static void concat(Maillon<Type> * & l1, Maillon<Type> *  l2);

	static void efface1(Maillon<Type>* & l);

	static void efface2(Maillon<Type>* & l);

	static  Maillon< Type > * appartient(const Type * a, Maillon<Type> * l);

	template <class FONCTEUR>
	static Maillon< Type > * appartient(Maillon<Type> * l, const FONCTEUR & condition);

	static void insertionOrdonnee(Type * a, Maillon<Type> * & l, bool(*estPlusPetitOuEgal)(const Type * a1, const Type * a2));

	static bool retire(const Type * a, Maillon<Type> * & l);

	static Type * depiler(Maillon<Type> * & l);
};

template<class Type>
ostream& operator <<(ostream & os, const Maillon<Type> * p) { return os << Maillon<Type>::toString(p); }

template <class Type>
const string Maillon<Type>::toString(const Maillon<Type> * p, const char * debut, const char * separateur, const char * fin) {
	Maillon<Type> * r;
	ostringstream oss;

	for (r = (Maillon<Type>*) p, oss << debut; r; r = r->suivant)
		oss << *(r->valeur) << separateur;

	oss << fin;
	return oss.str();
}

template <class Type>
void Maillon<Type>::concat(Maillon<Type> * & l1, Maillon<Type> * l2) {
	if (!l1)        /* l1 == liste vide */
		l1 = l2;

	else
		concat(l1->suivant, l2);
}

template <class Type>
int Maillon<Type>::taille(const Maillon<Type> * l) {
	if (!l) return 0;
	else
		return 1 + Maillon<Type>::taille(l->suivant);
}

template <class Type>
Maillon<Type> * Maillon<Type>::copie1(Maillon<Type> * l) {
	if (!l)
		return NULL;
	else
		return new Maillon<Type>(l->valeur, Maillon<Type>::copie1(l->suivant));
}

template <class Type>
Maillon<Type> * Maillon<Type>::copie2(const Maillon<Type> * l) {
	if (!l)
		return NULL;
	else
		return new Maillon<Type>(new Type(*(l->valeur)), Maillon<Type>::copie2(l->suivant));
}

template <class Type>
Maillon<Type> * Maillon<Type>::copie3(const Maillon<Type> * l) {
	if (!l)
		return NULL;
	else
		return new Maillon<Type>(l->valeur->copie(), Maillon<Type>::copie3(l->suivant));
}

template <class Type>
void Maillon<Type>::efface1(Maillon<Type>* & l) {
	if (l) {
		Maillon<Type>::efface1(l->suivant);
		delete l; l = NULL;
	}
}

template <class Type>
void Maillon<Type>::efface2(Maillon<Type>* & l) {
	if (l) {
		Maillon<Type>::efface2(l->suivant);
		delete l->valeur; delete l; l = NULL;
	}
}

template <class Type>
Maillon< Type > * Maillon< Type >::appartient(const Type * a, Maillon<Type> * l) {
	for (; l; l = l->suivant)
		if (a == l->valeur)
			return l;

	return l;
}

template <class Type>
template <class FONCTEUR>
Maillon< Type > * Maillon< Type >::appartient(Maillon<Type> * l, const FONCTEUR & condition) {
	for (; l; l = l->suivant)
		if (condition(l->valeur))
			return l;

	return l;
}

template<class Type>
void Maillon<Type>::insertionOrdonnee(Type * a, Maillon<Type> * & l, bool(*estPlusPetitOuEgal)(const Type * a1, const Type * a2)) {
	if (!l || estPlusPetitOuEgal(a, l->valeur))
		l = new Maillon<Type>(a, l);
	else
		Maillon<Type>::insertionOrdonnee(a, l->suivant, estPlusPetitOuEgal);
}

template<class Type>
bool Maillon<Type>::retire(const Type * a, Maillon<Type> * & l) {
	if (!l)
		return false;
	else
		if (a == l->valeur) {
			Maillon<Type> * r = l; l = l->suivant; delete r;
			return true;
		}
		else
			return Maillon<Type>::retire(a, l->suivant);
}

template <class Type>
Type * Maillon<Type>::depiler(Maillon<Type> * & l) {
	if (!l) throw Erreur("impossible de depiler une pile vide");
	Type * a = l->valeur;
	Maillon<Type> * tete = l;

	l = l->suivant; delete tete;
	return a;

}

template <class Type>
Maillon<Type> * reunion(Maillon<Type> * l1, Maillon<Type> * l2) {
	Maillon<Type> * r = Maillon<Type>::copie1(l2);
	Maillon<Type> * pl1;

	for (pl1 = l1; pl1; pl1 = pl1->suivant)
		if (!Maillon<Type>::appartient(pl1->valeur, r))
			r = new Maillon<Type>(pl1->valeur, r);

	return r;
}

template <class Type>
void partage(Maillon<Type> * & p, Maillon<Type> * & p1) {
	if (p == NULL || p->suivant == NULL)
		p1 = NULL;
	else {
		Maillon<Type> *  r1, *r2;

		r1 = p->suivant;
		r2 = r1->suivant;

		partage(r2, p1);

		r1->suivant = p1;
		p->suivant = r2;
		p1 = r1;
	}
}

template <class Type>
void fusion(Maillon<Type> * & p1, Maillon<Type> * & p2, bool(*estPlusPetitOuEgal)(const Type * a1, const Type * a2)) {
	if (!p2) return; // p2 est vide, il n'y a rien a faire

	if (!p1) // p1 est vide et p2 ne l'est pas
	{
		p1 = p2; p2 = NULL;
		return;
	}

	// a present, p1 et p2 sont non vides

	if (estPlusPetitOuEgal(p1->valeur, p2->valeur)) // p1->valeur <= p2->valeur
	{
		Maillon<Type> * r;
		r = p1->suivant;
		fusion(r, p2, estPlusPetitOuEgal);
		p1->suivant = r;
	}
	else // p1->valeur > p2->valeur
	{
		Maillon<Type> * r;
		r = p2->suivant;
		fusion(p1, r, estPlusPetitOuEgal);
		p2->suivant = p1;
		p1 = p2;
		p2 = NULL;
	}
}

template <class Type>
void tri(Maillon<Type>* & p, bool(*estPlusPetitOuEgal)(const Type * a1, const Type * a2)) {
	if (p != NULL && p->suivant != NULL) {
		Maillon<Type> * p1;

		partage(p, p1);

		tri(p, estPlusPetitOuEgal); tri(p1, estPlusPetitOuEgal);

		fusion(p, p1, estPlusPetitOuEgal);
	}
}