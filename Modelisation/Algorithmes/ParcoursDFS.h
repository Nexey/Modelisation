#pragma once

#include "../Graphe/Graphe.h"

//Retourne la composante connexe depuis le sommet Depart
void DFS_recursif(const Graphe* g, const Sommet* depart, Graphe* gRetour);
Graphe* parcours_DFS(const Graphe* g, Sommet* depart = NULL){
	Graphe* gRetour =  new Graphe();
	if(depart==NULL) depart = g->lSommets->valeur;

	DFS_recursif(g, depart, gRetour);

	return gRetour;
}

//Les sommets marqués seront les sommets dans le graphe de retour (qui sera la composante connexe)
void DFS_recursif(const Graphe* g, Sommet* depart, Graphe* gRetour){
	bool dejaMarque;
	Maillon<pair<Sommet*, Arc*>>* adjacence = NULL;
	//On marque le sommet actuel en l'ajoutant au graphe
	gRetour->creeSommet(depart);

	//Parcourir tous les voisins;
	adjacence = g->adjacences(depart);
	for(; adjacence; adjacence = adjacence->suivant){
		dejaMarque = Maillon<Sommet>::appartient(adjacence->valeur->first, gRetour->lSommets);
		gRetour->creeArc(adjacence->valeur->second);
		if(!dejaMarque)
			DFS_recursif(g, adjacence->valeur->first, gRetour);
	}
}





bool  detection_circuit_recursif(const Graphe* g, Sommet* depart, Maillon<Sommet>* SommetsMarquesParent);
bool detection_De_Circuit(const Graphe* g, Sommet* depart){
	Maillon<Sommet>* SommetsMarques = NULL;
	if(depart==NULL) depart = g->lSommets->valeur;

	return detection_circuit_recursif(g, depart, SommetsMarques);
}

bool detection_circuit_recursif(const Graphe*  g, Sommet* depart, Maillon<Sommet>* SommetsMarquesParent){
	Maillon<Sommet>* voisins = NULL;
	Maillon<Sommet>* SommetsMarques = NULL;

	//On marque le sommet actuel pour les fils (dans l'arbre)
	//si la descendance d'un fils peut atteindre la descendance d'un autre fils,
	//cela ne veux pas forcement dire qu'il y a un cycle (car on est dans un graphe orienté)
	//Par contre on garde le marquage de tous les autres sommets parents.

	//Permet d'ignorer les aretes transversale et avant.
	//Or, lors de la detection d'une arete arrière, on a trouvé un cycle
	SommetsMarques = new Maillon<Sommet>(depart, SommetsMarquesParent);

	//Parcourir tous les voisins;
	voisins = g->voisins(depart);
	for(; voisins; voisins = voisins->suivant){
		//Evite un appel récursif inutile (un simple return true) pour éviter les stack overflow sur les gros graphes
		if(Maillon<Sommet>::appartient(voisins->valeur, SommetsMarquesParent)) return true;

		if(detection_circuit_recursif(g, voisins->valeur, SommetsMarques)){
			return true;
		}
	}
	return false;
}