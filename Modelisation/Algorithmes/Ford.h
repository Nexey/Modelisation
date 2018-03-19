//
// Created by Charlotte LANUEL on 19/03/2018.
//
#include "../Graphe/Graphe.h"
#include "../Algorithmes/ParcoursDFS.h"
#include "../Outils/Outils.h"


#ifndef MODELISATION_FORD_H
#define MODELISATION_FORD_H

bool detection_circuit_negatif(const Graphe *g, Sommet *depart){
    if(aucuneValuationNegative(g->lArcs))
        return false;

    for(Maillon<Sommet>*l = g->lSommets; l; l->suivant){
        Maillon<Sommet>* voisins = NULL;
        Maillon<Sommet>* SommetsMarques = NULL;


        SommetsMarques = new Maillon<Sommet>(depart, SommetsMarquesParent);

        //Parcourir tous les voisins;
        voisins = g->voisins(depart);
        for(; voisins; voisins = voisins->suivant){
            //Evite un appel récursif inutile (un simple return true) pour eviter les stack overflow sur les gros graphes
            if(Maillon<Sommet>::appartient(voisins->valeur, SommetsMarquesParent)){
                for(Maillon<Arc> *m = g->lArcs; m; m->suivant){
                    if(m->valeur->fin->equals(voisins->valeur) && (m->valeur->coutArc < 0))
                        return true;
                }

            }}

            if(detection_circuit_recursif(g, voisins->valeur, SommetsMarques)){
                return true;
            }
        }
        return false;
}


Maillon<Arc> * Ford(const Graphe *g, Sommet *debut, Sommet* fin, int(*etiquette)(const Arc*)){
    if(!detection_circuit_negatif((g, debut, )))
        std::cerr << "L'algorithme n'est pas applicable car un circuit negatif est present" << endl;

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
            for (; adj; adj->suivant) {
                int coutSommetPlusArc = adj->valeur->first->etiquette + adj->valeur->second->coutArc;
                int coutAModifier = adj->valeur->second->fin->etiquette;
                if (coutSommetPlusArc < coutAModifier) {
                    adj->valeur->second->fin->etiquette = coutSommetPlusArc;
                    prochainSommetATraiter = new Maillon<Sommet>(adj->valeur->second->fin, prochainSommetATraiter);
                }
            }
        }

    }while(prochainSommetATraiter);


    Maillon<Arc>* chemin = nullptr;
    bool continuer = true;
    Sommet* actuel = debut;
    Arc* arcActuel = nullptr;
    int min;


    while (actuel != fin){
        adj = g->adjacences(actuel);
        min = INT8_MAX;
        for (; adj; adj->suivant) {
            if(adj->valeur->first->etiquette < min){
                min = adj->valeur->first->etiquette;
                arcActuel = adj->valeur->second;
            }
        }
        chemin = new Maillon<Arc>(arcActuel, chemin);
        actuel = arcActuel->fin;
    }

    return chemin;


}


#endif //MODELISATION_FORD_H
