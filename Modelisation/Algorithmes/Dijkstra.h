//
// Created by Charlotte LANUEL on 18/03/2018.
//

#pragma once

#include "../Graphe/Graphe.h"

#ifndef MODELISATION_DIJKSTRA_H
#define MODELISATION_DIJKSTRA_H

bool aucuneValuationNegative(Maillon<Arc> *lArc) {
    if (lArc != NULL) {
        if (lArc->valeur->cout < 0 || lArc->valeur->temps < 0) return false;
        return aucuneValuationNegative(lArc->suivant);
    }
    // On est arrive a la fin de la liste des arcs, donc on peut renvoyer true
    return true;
}

Maillon<Arc>* dijkstra(const Graphe *g, Sommet* debut, int(*etiquette)(const Sommet*)){
    if(!aucuneValuationNegative(g->lArcs))
        return NULL;
	int k = 0;
	bool fin = false;
	Maillon<Arc> *arcs = g->lArcs->suivant;
	
	Maillon<Sommet> * arcTmp;
	for (; arcTmp; arcTmp)
		arcTmp->valeur->etiquette = INT_MAX;

	Sommet *s = debut;
	s->etiquette = 0;

	Maillon<Sommet> *sommetsMarques;
	//Maillon< pair< Sommet *, Arc* > > *l;
	Maillon<Arc> *arcsAdjacents;
	Maillon<Sommet> *sommetsATraiter;
	while (arcs != NULL && !fin) {
		arcsAdjacents = g->arcsAdjacents(s);
		
		for (Maillon<Arc> *l = arcsAdjacents; l; l->suivant) {
			sommetsATraiter = new Maillon<Sommet>(l->valeur->fin, sommetsATraiter);
			l->valeur->fin->etiquette = etiquette(l->valeur->fin);
		}



		arcs = arcs->suivant;
		sommetsMarques = new Maillon<Sommet>(s, sommetsMarques);
	}
}



#endif //MODELISATION_DIJKSTRA_H
