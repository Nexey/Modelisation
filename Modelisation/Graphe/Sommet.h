#pragma once

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T>
class Sommet {
public:
	int degre;
	// TODO : A compléter avec les informations nécessaires
	Sommet(const T & v) : degre(0) {}

	operator string () const;

};

template <class T>
Sommet<T>::operator string () const {
	ostringstream oss;

	oss << "Sommet(" << endl;
	oss << GElement<T>::operator string() << endl;
	oss << "degre = " << degre << endl;
	oss << ")";
	return oss.str();
}

template <class T>
ostream & operator << (ostream & os, const Sommet<T> & sommet) {
	return os << (string)sommet;
}
