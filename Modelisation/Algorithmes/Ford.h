//
// Created by Charlotte LANUEL on 19/03/2018.
//
#include "../Graphe/Graphe.h"
#include "../Algorithmes/ParcoursDFS.h"


#ifndef MODELISATION_FORD_H
#define MODELISATION_FORD_H

bool detection_circuit_negatif(const Graphe *g){
    for(Maillon<Sommet>*l = g->lSommets; l; l->suivant){
        if(detection_De_Circuit(g, l->valeur){

        }
}


#endif //MODELISATION_FORD_H
