#pragma once

#include "../Graphe/Graphe.h"

//On initialise le marquage des sommets
//0 -> pas marqué
//1 -> ouvert
//2 -> fermé
void mettre_a_zero(Graphe* g){
        Maillon<Sommet>* liste;
        for(liste = g->lSommets; liste; liste = liste->suivant)
                liste->valeur->etiquette = 0;
}

//Utile dans la fonction de recherche de circuit
typedef Maillon<pair<Sommet*, Maillon <Arc>*>> liste_circuits;

//Definitions pour les appels de fonction.
void DFS_recursif(Graphe* g, Sommet* actuel, Graphe* gRetour);
bool existe_Chemin_Recursif(Graphe* g, Sommet* s1, Sommet* s2);
bool  detection_circuit_recursif(Graphe* g, Sommet* actuel);
void recherche_Circuit_Recursif(Graphe* g, Sommet* actuel, liste_circuits* &liste);




//Retourne la composante connexe depuis le sommet Depart
Graphe* parcours_DFS(Graphe* g, Sommet* depart = nullptr){
        if(depart == nullptr) depart = g->lSommets->valeur;
        Graphe* gRetour =  new Graphe()
        mettre_a_zero(g);

        DFS_recursif(g, depart, gRetour);

        return gRetour;
}

//Les sommets marqués seront les sommets dans le graphe de retour (qui sera la composante connexe)
void DFS_recursif(Graphe* g, Sommet* actuel, Graphe* gRetour){
        Maillon<pair<Sommet*, Arc*>>* adjacence = nullptr;

        //On marque le sommet actuel  et on l'ajoute au graphe
        actuel->etiquette = 1;
        gRetour->creeSommet(actuel);

        //Parcourir tous les voisins;
        adjacence = g->adjacences(actuel);
        for(; adjacence; adjacence = adjacence->suivant){
                gRetour->creeArc(adjacence->valeur->second);

                if(adjacence->valeur->first->etiquette == 0)
                        DFS_recursif(g, adjacence->valeur->first, gRetour);
        }

        actuel->etiquette = 2;
}




//Verifie l'existence d'un chemin de S1 vers S2
bool existe_Chemin(Graphe* g, Sommet* s1, Sommet* s2){
        mettre_a_zero(g);

        return existe_Chemin_Recursif(g, s1, s2);
}

bool existe_Chemin_Recursif(Graphe* g, Sommet* s1, Sommet* s2){
        bool dejaMarque;
        Maillon<Sommet>* voisins = nullptr;

        //On marque le sommet actuel
        s1->etiquette = 1;

        //Parcourir tous les voisins;
        voisins = g->voisins(s1);
        for(; voisins; voisins = voisins->suivant){
                if(voisins->valeur->etiquette != 0) {
                        if (voisins->valeur == s2) return true;
                        if (existe_Chemin_Recursif(g, voisins->valeur, s2))return true;
                }
        }

        //On ferme le sommet actuel
        s1->etiquette = 2;
        return false;
}




//Renvoie true dès qu'un circuit à été détecté
bool detection_De_Circuit(Graphe* g, Sommet* depart = nullptr){
        if(depart == nullptr) depart = g->lSommets->valeur;
        mettre_a_zero(g);

        return detection_circuit_recursif(g, depart);
}

bool detection_circuit_recursif(Graphe*  g, Sommet* actuel){
        Maillon<Sommet>* voisins = nullptr;
        actuel->etiquette = 1;

        //Parcourir tous les voisins;
        //Si le voisin est ouvert, c'est un sommet parent donc un arete arriere -> CYCLE
        //Si le sommet est fermé, c'est une arete transversale, donc inutile dans notre cas
        //Sinon, recursion sur le sommet
        voisins = g->voisins(actuel);
        for(; voisins; voisins = voisins->suivant){
                if(voisins->valeur->etiquette == 1) return true;

                if(detection_circuit_recursif(g, voisins->valeur)){
                        return true;
                }
        }
        actuel->etiquette = 2;
        return false;
}




//Renvoie une liste de circuit
Maillon<Maillon<Arc>>* recherche_Circuit(Graphe* g, Sommet* depart = nullptr){
        if(depart == nullptr) depart = g->lSommets->valeur;
        mettre_a_zero(g);
        liste_circuits* liste;

        recherche_Circuit_Recursif(g, depart, liste);

        Maillon<Maillon<Arc>>* res = nullptr;
        for(;liste; liste = liste->suivant){
                res = new Maillon<Maillon<Arc>>(liste->valeur->second, res);
        }
}

void recherche_Circuit_Recursif(Graphe* g, Sommet* actuel, liste_circuits* &liste){
        Maillon<pair<Sommet*, Arc*>>* adjacence = nullptr;
        actuel->etiquette = 1;

        adjacence = g->adjacences(actuel);
        for(; adjacence; adjacence = adjacence->suivant){

                if(adjacence->valeur->first->etiquette == 0)
                        //Si il n'est pas visité on fait la recursion
                        recherche_Circuit_Recursif(g, adjacence->valeur->first, liste);

                if(adjacence->valeur->first->etiquette == 1)
                        //Si il est ouvert, c'est que adjacence->second est une arete remontante (= cycle)
                        //Le sommet adjacence->first est donc le début de ce cycle dans l'ordre de parcour
                        liste = new liste_circuits(new pair<Sommet*, Maillon<Arc>*>(adjacence->valeur->first, new Maillon<Arc>(adjacence->valeur->second, nullptr)));
        }

        liste_circuits* tmp = liste;
        for(;tmp;tmp = tmp->suivant){
                if(tmp->valeur->first != nullptr){
                        if(tmp->valeur->first == actuel) tmp->valeur->first = nullptr;
                        else{
                                tmp->valeur->second = new Maillon<Arc>(g->getArcParSommets(actuel, tmp->valeur->second->valeur->debut),tmp->valeur->second);
                        }
                }
        }
}