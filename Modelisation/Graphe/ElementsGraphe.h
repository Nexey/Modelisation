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
    //info = valuation du sommet : poids arete ascendante + valuation sommmet pere
    Sommet* pere;

    Sommet(int borneInf, int borneSup) : degre(0), inf(borneInf), sup(borneSup){}

    operator string () const;

};


class Arc {
public:
    Sommet *debut, *fin;

    int cout;
    int temps;

    Arc(int cout, int temps, Sommet * debut, Sommet * fin) : cout(cout), debut(debut), fin(fin) {
            debut->degre++;
            fin->degre++;
    }

    ~Arc() { debut->degre--; fin->degre--; }

    operator string () const;

    bool estEgal(const Sommet * debut, const Sommet * fin) const;
};


//#########SOMME
Sommet::operator string () const {
        ostringstream oss;

        oss << "Sommet[" << "degre:" << degre <<  "]";
        return oss.str();
}

ostream & operator << (ostream & os, const Sommet & sommet) {
        return os << (string)sommet;
}

//#########ARC
Arc::operator string () const {
        ostringstream oss;

        oss << "Arc[" << "debut:" << debut <<  "fin:" << fin <<  "]";
        return oss.str();

}

ostream & operator << (ostream & os, const Arc& arc) {
        return os << (string)arc;
}

bool Arc::estEgal(const Sommet * deb, const Sommet * fi) const {
        // Attention : Nous sommes dans un graphe orienté, et donc s1 doit être le début et s2 la fin
        return deb == debut && fi == fin;
}


