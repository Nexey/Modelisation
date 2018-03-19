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
    // On est arriv� � la fin de la liste des arcs, donc on peut renvoyer true
    return true;
}

Maillon<Arc>* dijkstra(const Graphe *g, const Sommet* debut){
    if(!aucuneValuationNegative(g->lArcs))
        return NULL;
    debut->
}



#endif //MODELISATION_DIJKSTRA_H
