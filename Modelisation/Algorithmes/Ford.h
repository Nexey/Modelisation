//
// Created by Charlotte LANUEL on 19/03/2018.
//
#pragma once


#include "../Graphe/Graphe.h"
#include "../Algorithmes/ParcoursDFS.h"
#include "../Outils/Outils.h"

int avec_cout_Arc(Arc* a){return a->coutArc;}

int avec_temps_Arc(Arc* a){return a->tempsArc;}


bool detection_circuit_negatif(Graphe *g, Sommet *depart,int(*valuation)(Arc*)){
    Maillon<Maillon<Arc>>* circuits = recherche_Circuit(g, depart);
    int val;

    for(; circuits; circuits = circuits->suivant){
		val = 0;
        for(; circuits->valeur; circuits->valeur = circuits->valeur->suivant){
			val += valuation(circuits->valeur->valeur);
        }
        if(valuation < 0) return true;

    }
    return false;
}


Maillon<Arc> * Ford(Graphe *g, Sommet *debut, int(*valuation)(Arc*)= &avec_cout_Arc){
   // if(!detection_circuit_negatif(g, debut, valuation))	std::cerr << "L'algorithme n'est pas applicable car un circuit negatif est present" << endl;

	Maillon<Sommet> *lTmp = g->lSommets;
	Sommet *fin = NULL;
	for (; lTmp; lTmp = lTmp->suivant)
		fin = lTmp->valeur;

    Maillon<Sommet>* sommetATraiter = g->lSommets;
    Maillon<Sommet>* prochainSommetATraiter = new Maillon<Sommet>(debut, nullptr);
    Maillon<pair<Sommet*,Arc*>>* adj;

    for(; sommetATraiter; sommetATraiter = sommetATraiter->suivant)
        sommetATraiter->valeur->etiquette = INT8_MAX;

    debut->etiquette = 0;

    do{
        sommetATraiter = prochainSommetATraiter;
        prochainSommetATraiter = nullptr;

        for(; sommetATraiter; sommetATraiter = sommetATraiter->suivant) {
            adj = g->adjacences(sommetATraiter->valeur);
            for (; adj; adj = adj->suivant) {
                int coutSommetPlusArc = adj->valeur->first->etiquette + valuation(adj->valeur->second);
                int coutAModifier = adj->valeur->second->fin->etiquette;
                if (coutSommetPlusArc < coutAModifier) {
                    adj->valeur->second->fin->etiquette = coutSommetPlusArc;
                    prochainSommetATraiter = new Maillon<Sommet>(adj->valeur->second->fin, prochainSommetATraiter);
                }
            }
        }

	} while (prochainSommetATraiter != nullptr);


    Maillon<Arc>* chemin = nullptr;
    bool continuer = true;
    Sommet* actuel = debut;
    Arc* arcActuel = nullptr;
    int min;


    while (actuel != fin){
        adj = g->adjacences(actuel);
        min = INT8_MAX;
        for (; adj; adj = adj->suivant) {
			if (adj->valeur->first->etiquette < min) {
                min = adj->valeur->first->etiquette;
            }
			arcActuel = adj->valeur->second;
        }

		if (arcActuel) {
			chemin = new Maillon<Arc>(arcActuel, chemin);
			actuel = arcActuel->fin;
		}
	}

    return chemin;


}

