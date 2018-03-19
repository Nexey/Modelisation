//
// Created by Charlotte LANUEL on 19/03/2018.
//
#include "../Graphe/Graphe.h"
#include "../Algorithmes/ParcoursDFS.h"
#include "../Outils/Outils.h"


#ifndef MODELISATION_FORD_H
#define MODELISATION_FORD_H

bool detection_circuit_negatif(const Graphe *g, Sommet *depart, Maillon<Sommet>* SommetsMarquesParent){
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


Maillon<Sommet> * Ford(const Graphe *g, Sommet *debut, int(*etiquette)(const Arc*)){
    if(!detection_circuit_negatif((g, debut, )))
        std::cerr << "L'algorithme n'est pas applicable car un circuit négatif est présent" << endl;

    sommetATraiter = new Maillon<Sommet>(g->lSommets);

    for(; sommetATraiter; sommetATraiter = sommetATraiter->suivant)
        sommetATraiter->valeur->etiquette = INT8_MAX;

    debut->etiquette = 0;
    Maillon<Sommet> sommetsMarques;
    sommetsMarques = new Maillon<Sommet>(debut, sommetsMarques);

    do{
        Maillon<Arc> adj = g->adjacences(sommetATraiter->valeur);
        for(; adj; adj->suivant){
            int coutSommetPlusArc = sommetTraiter->valeur->etiquette + adj->valeur->coutArc;
            int coutAModifier = sommetATraiter->suivant->valeur->etiquette;
            if(coutSommetPlusArc < coutAModifier)
                sommetATraiter->suivant->valeur->etiquette = coutSommetPlusArc;
        }

        for(; adj; adj->suivant){

        }

        sommetATraiter = sommetATraiter->suivant;
    }while(sommetATraiter->suivant != NULL);



}


#endif //MODELISATION_FORD_H
