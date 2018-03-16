#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "../Main/Erreur.h"

using namespace std;

template<class T>
T max(const T &a, const T &b) { return a > b ? a : b; }

template <class T>
class Maillon {
public:
	T * v;				// valeur
	Maillon<T> * s;	// suivant

	Maillon(T * v, Maillon<T> * s) :v(v), s(s) {}

	static const string toString(const Maillon<T> * p, const char * debut = "( ", const char * separateur = ", ", const char * fin = ")");

	static int taille(const Maillon<T> * l);

	static  Maillon<T> * copie1(Maillon<T> * l);

	static  Maillon<T> * copie2(const Maillon<T> * l);

	static Maillon<T> * copie3(const Maillon<T> * l);

	static void concat(Maillon<T> * & l1, Maillon<T> *  l2);

	static void efface1(Maillon<T>* & l);

	static void efface2(Maillon<T>* & l);

	static  Maillon< T > * appartient(const T * a, Maillon<T> * l);

	template <class FONCTEUR>
	static Maillon< T > * appartient(Maillon<T> * l, const FONCTEUR & condition);

	static void insertionOrdonnee(T * a, Maillon<T> * & l, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2));

	static bool retire(const T * a, Maillon<T> * & l);

	static T * depiler(Maillon<T> * & l);
};

template<class T>
ostream& operator <<(ostream & os, const Maillon<T> * p) { return os << Maillon<T>::toString(p); }

template <class T>
const string Maillon<T>::toString(const Maillon<T> * p, const char * debut, const char * separateur, const char * fin) {
	Maillon<T> * r;
	ostringstream oss;

	for (r = (Maillon<T>*) p, oss << debut; r; r = r->s)
		oss << *(r->v) << separateur;

	oss << fin;
	return oss.str();
}

template <class T>
void Maillon<T>::concat(Maillon<T> * & l1, Maillon<T> * l2) {
	if (!l1)        /* l1 == liste vide */
		l1 = l2;

	else
		concat(l1->s, l2);
}

template <class T>
int Maillon<T>::taille(const Maillon<T> * l) {
	if (!l) return 0;
	else
		return 1 + Maillon<T>::taille(l->s);
}

template <class T>
Maillon<T> * Maillon<T>::copie1(Maillon<T> * l) {
	if (!l)
		return NULL;
	else
		return new Maillon<T>(l->v, Maillon<T>::copie1(l->s));
}

template <class T>
Maillon<T> * Maillon<T>::copie2(const Maillon<T> * l) {
	if (!l)
		return NULL;
	else
		return new Maillon<T>(new T(*(l->v)), Maillon<T>::copie2(l->s));
}

template <class T>
Maillon<T> * Maillon<T>::copie3(const Maillon<T> * l) {
	if (!l)
		return NULL;
	else
		return new Maillon<T>(l->v->copie(), Maillon<T>::copie3(l->s));
}

template <class T>
void Maillon<T>::efface1(Maillon<T>* & l) {
	if (l) {
		Maillon<T>::efface1(l->s);
		delete l; l = NULL;
	}
}

template <class T>
void Maillon<T>::efface2(Maillon<T>* & l) {
	if (l) {
		Maillon<T>::efface2(l->s);
		delete l->v; delete l; l = NULL;
	}
}

template <class T>
Maillon< T > * Maillon< T >::appartient(const T * a, Maillon<T> * l) {
	for (; l; l = l->s)
		if (a == l->v)
			return l;

	return l;
}

template <class T>
template <class FONCTEUR>
Maillon< T > * Maillon< T >::appartient(Maillon<T> * l, const FONCTEUR & condition) {
	for (; l; l = l->s)
		if (condition(l->v))
			return l;

	return l;
}

template<class T>
void Maillon<T>::insertionOrdonnee(T * a, Maillon<T> * & l, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)) {
	if (!l || estPlusPetitOuEgal(a, l->v))
		l = new Maillon<T>(a, l);
	else
		Maillon<T>::insertionOrdonnee(a, l->s, estPlusPetitOuEgal);
}

template<class T>
bool Maillon<T>::retire(const T * a, Maillon<T> * & l) {
	if (!l)
		return false;
	else
		if (a == l->v) {
			Maillon<T> * r = l; l = l->s; delete r;
			return true;
		}
		else
			return Maillon<T>::retire(a, l->s);
}

template <class T>
T * Maillon<T>::depiler(Maillon<T> * & l) {
	if (!l) throw Erreur("impossible de depiler une pile vide");
	T * a = l->v;
	Maillon<T> * tete = l;

	l = l->s; delete tete;
	return a;

}

template <class T>
Maillon<T> * reunion(Maillon<T> * l1, Maillon<T> * l2) {
	Maillon<T> * r = Maillon<T>::copie1(l2);
	Maillon<T> * pl1;

	for (pl1 = l1; pl1; pl1 = pl1->s)
		if (!Maillon<T>::appartient(pl1->v, r))
			r = new Maillon<T>(pl1->v, r);

	return r;
}

template <class T>
void partage(Maillon<T> * & p, Maillon<T> * & p1) {
	if (p == NULL || p->s == NULL)
		p1 = NULL;
	else {
		Maillon<T> *  r1, *r2;

		r1 = p->s;
		r2 = r1->s;

		partage(r2, p1);

		r1->s = p1;
		p->s = r2;
		p1 = r1;
	}
}

template <class T>
void fusion(Maillon<T> * & p1, Maillon<T> * & p2, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)) {
	if (!p2) return; // p2 est vide, il n'y a rien a faire

	if (!p1) // p1 est vide et p2 ne l'est pas
	{
		p1 = p2; p2 = NULL;
		return;
	}

	// a present, p1 et p2 sont non vides

	if (estPlusPetitOuEgal(p1->v, p2->v)) // p1->v <= p2->v
	{
		Maillon<T> * r;
		r = p1->s;
		fusion(r, p2, estPlusPetitOuEgal);
		p1->s = r;
	}
	else // p1->v > p2->v
	{
		Maillon<T> * r;
		r = p2->s;
		fusion(p1, r, estPlusPetitOuEgal);
		p2->s = p1;
		p1 = p2;
		p2 = NULL;
	}
}

template <class T>
void tri(Maillon<T>* & p, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)) {
	if (p != NULL && p->s != NULL) {
		Maillon<T> * p1;

		partage(p, p1);

		tri(p, estPlusPetitOuEgal); tri(p1, estPlusPetitOuEgal);

		fusion(p, p1, estPlusPetitOuEgal);
	}
}