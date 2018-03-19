#pragma once

#include "../Graphe/Graphe.h"
#include "../Outils/Outils.h"

Maillon<Sommet>* dijkstra(const Graphe *g, int(*etiquette)(const Arc*)) {
	if (!respecteToutesConditions(g))
		return NULL;

	bool fin = false;
	Maillon<Arc> *arcs = g->lArcs->suivant;
	
	Maillon<Sommet> * sommetTmp = new Maillon<Sommet>(*g->lSommets);
	for (; sommetTmp; sommetTmp = sommetTmp->suivant)
		sommetTmp->valeur->etiquette = INT_MAX;

	Sommet *s = g->lSommets->valeur;
	s->etiquette = 0;

	Maillon<Sommet> *sommetsMarques = NULL;
	sommetsMarques = new Maillon<Sommet>(s, sommetsMarques);
	//Maillon< pair< Sommet *, Arc* > > *l;
	Maillon<Arc> *arcsAdjacents;
	Maillon<Sommet> *sommetsATraiter;

	while (arcs != NULL && !fin) {
		arcsAdjacents = g->arcsAdjacents(s);
		sommetsATraiter = NULL;
		
		for (Maillon<Arc> *l = arcsAdjacents; l; l = l->suivant) {
			// Le sommet n'est pas marqué
			if (sommetsMarques->appartient(l->valeur->fin, sommetsMarques) == NULL) {
				if (sommetsATraiter->appartient(l->valeur->fin, sommetsATraiter) == NULL) {

					sommetsATraiter = new Maillon<Sommet>(l->valeur->fin, sommetsATraiter);

					// Mise à jour de l'étiquette du sommet distant
					// De base, l'étiquette distante vaut INT_MAX
					l->valeur->fin->etiquette = minimum(l->valeur->fin->etiquette, etiquette(l->valeur) + s->etiquette);
				}
			}
		}

		arcs = arcs->suivant;
		
		if (sommetsATraiter != NULL) {
			s = sommetsATraiter->depiler(sommetsATraiter);
			for (; sommetsATraiter; sommetsATraiter = sommetsATraiter->suivant) {
				if (s->etiquette > sommetsATraiter->valeur->etiquette)
					s = sommetsATraiter->valeur;
			}
		}

		fin = s->etiquette == INT_MAX;
		if (!fin)
			if (sommetsMarques->appartient(s, sommetsMarques) == NULL) 
				sommetsMarques = new Maillon<Sommet>(s, sommetsMarques);
	}
	return sommetsMarques;
}