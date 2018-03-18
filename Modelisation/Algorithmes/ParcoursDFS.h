#pragma once

#include "../Graphe/Graphe.h"

void DFS_recursif(const Graphe& g, const Sommet* depart, Maillon<Sommet>* &SommetsMarques);
Maillon<Sommet>* parcours_DFS(const Graphe& g, Sommet* depart = NULL){
        Maillon<Sommet>* SommetsMarques = NULL;
        if(depart==NULL) depart = g.lSommets->valeur;

        DFS_recursif(g, depart, SommetsMarques);

        return SommetsMarques;
}

//Les sommets marqués doivent se transmettre lors de la récursion. Or un maillon est est pointeur
//On envoit donc le pointeur par référence (Maillon<..>* &)
void DFS_recursif(const Graphe& g, Sommet* depart, Maillon<Sommet>* &SommetsMarques){
        Maillon<Sommet>* voisins = NULL;
        if(Maillon<Sommet>::appartient(depart, SommetsMarques)){
                return; //Le sommet est marqué.
        }
        else{
                //On marque le sommet actuel
                SommetsMarques = new Maillon<Sommet>(depart, SommetsMarques);

                //Parcourir tous les voisins;
                voisins = g.voisins(depart);
                for(; voisins; voisins = voisins->suivant){
                        DFS_recursif(g, voisins->valeur, SommetsMarques);
                }
        }
}