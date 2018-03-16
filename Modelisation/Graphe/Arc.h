#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "../Graphe/Sommet.h"

using namespace std;

// S stocke les infos de l'arête, T stocke les infos des sommets 
// TODO : Trouver un meilleur nom autre que infoArc et infoSommet pour éviter de trop ressembler à Julien
template <class S, class T>
class Arc {
public:
	Sommet <T> *debut, *fin;	// debut et fin peuvent etre interpretees comme des clefs etrangeres vers une table de sommets
	S info;

	Arc(const int clef, const S & v, Sommet<T> * debut, Sommet<T> * fin) : info(v), debut(debut), fin(fin) {
		debut->degre++; fin->degre++;
	}

	~Arc() { debut->degre--; fin->degre--; }

	operator string () const;

	bool estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template <class S, class T>
Arc<S, T>::operator string () const {
	ostringstream oss;

	oss << "Arc  (" << endl;
	oss << "clef debut = " << debut->clef << endl;
	oss << "clef fin = " << fin->clef << endl;
	oss << ")";
	return oss.str();

}

template <class S, class T>
ostream & operator << (ostream & os, const Arc<S, T> & arc) {
	return os << (string)arc;
}
template <class S, class T>
bool Arc<S, T>::estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const {
	// Attention : Nous sommes dans un graphe orienté, et donc s1 doit être le début et s2 la fin
	return s1 == debut && s2 == fin;
}