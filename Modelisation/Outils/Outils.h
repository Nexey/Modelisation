#pragma once
#include "../Graphe/Graphe.h"

int coutArc(const Arc* a) {
	return a->coutArc;
}

int tempsArc(const Arc* a) {
	return a->tempsArc;
}

int binfSommet(const Sommet* s) {
	return s->inf;
}

int bsupSommet(const Sommet* s) {
	return s->sup;
}

// Renvoie true si il existe une valuation négative
bool aucuneValuationNegative(const Arc *a) {
	return (a->coutArc >= 0 && a->tempsArc >= 0);
}

// Renvoie true si les deux données sont à 0
bool toutesValuationsPositivesStrictes(const Arc *a) {
	return (a->coutArc > 0 && a->tempsArc > 0);
}

// Renvoie true si il existe une valuation négative
bool aucuneValuationNegative(const Sommet *s) {
	return (s->inf >= 0 && s->sup >= 0);
}

// Renvoie true si les deux données sont à 0
bool toutesValuationsPositivesStrictes(const Sommet *s) {
	return (s->inf > 0 && s->sup > 0);
}

template<class TYPE>
bool respecteCondition(Maillon<TYPE> *listeElem, bool(*condition)(const TYPE*)) {
	if (listeElem != NULL) {
		if (condition(listeElem->valeur)) return respecteCondition(listeElem->suivant, condition);
		return false;
	}
	// On est arrive a la fin de la liste des arcs, donc on peut renvoyer true
	return true;
}

// Si toutes les conditions sont respectées, j'ai obtenu true à chacune
bool respecteToutesConditions(const Graphe *g) {
	bool v1 = respecteCondition(g->lArcs, aucuneValuationNegative),
		v2 = respecteCondition(g->lArcs, toutesValuationsPositivesStrictes),
		v3 = respecteCondition(g->lSommets, aucuneValuationNegative),
		v4 = respecteCondition(g->lSommets->suivant, toutesValuationsPositivesStrictes);
	return 
		// Il ne doit y avoir aucun arc avec une valuation négative
		v1 &&
		// Toutes les valuations doivent êtres positives
		v2 &&
		// Les bornes inférieures et supérieures doivent être positives
		v3 &&
		// Le premier sommet est initialisé à [0; 0], je dois donc commencer avec le deuxième sommet pour vérifier qu'ils sont positifs stricts
		v4;
}