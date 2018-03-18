#pragma once

#include "../Graphe/Graphe.h"

void DFS_recursif(const Graphe* g, const Sommet* depart, Maillon<Sommet>* &SommetsMarques);
void parcours_DFS(const Graphe* g, Sommet* depart = NULL) {
	Maillon<Sommet>* SommetsMarques = NULL;
	if (depart == NULL) depart = g->lSommets->valeur;

	DFS_recursif(g, depart, SommetsMarques);
}

//Les sommets marqués doivent se transmettre lors de la récursion. Or un maillon est est pointeur
//On envoit donc le pointeur par référence (Maillon<..>* &)
void DFS_recursif(const Graphe* g, Sommet* depart, Maillon<Sommet>* &SommetsMarques) {
	Maillon<Sommet>* voisins = NULL;
	if (Maillon<Sommet>::appartient(depart, SommetsMarques))
		return; //Le sommet est marqué.
	else {
		//On marque le sommet actuel
		SommetsMarques = new Maillon<Sommet>(depart, SommetsMarques);

		//Parcourir tous les voisins;
		voisins = g->voisins(depart);
		for (; voisins; voisins = voisins->suivant) {
			DFS_recursif(g, voisins->valeur, SommetsMarques);
		}
	}
}

bool  detection_circuit_recursif(const Graphe* g, Sommet* depart, Maillon<Sommet>* &SommetsMarquesParent);
bool detection_De_Circuit(const Graphe* g, Sommet* depart) {
	Maillon<Sommet>* SommetsMarques = NULL;
	Maillon<Maillon<Sommet>>* circuits;
	if (depart == NULL) depart = g->lSommets->valeur;

	return detection_circuit_recursif(g, depart, SommetsMarques);
}

bool detection_circuit_recursif(const Graphe*  g, Sommet* depart, Maillon<Sommet>* &SommetsMarquesParent) {
	Maillon<Sommet>* voisins = NULL;
	Maillon<Sommet>* SommetsMarques = NULL;
	if (Maillon<Sommet>::appartient(depart, SommetsMarquesParent)) {
		return true; //Le sommet est déjà marqué, il y a donc un circuit.
	}
	else {
		//On marque le sommet actuel pour les fils (dans l'arbre)
		//si la descendance d'un fils peut atteindre la descendance d'un autre fils,
		//cela ne veux pas forcement dire qu'il y a un cycle (car on est dans un graphe orienté)
		//Par contre on garde le marquage de tous les autres sommets parents.

		//Permet d'ignorer les aretes transversale et avant.
		//Or, lors de la detection d'une arete arrière, on a trouvé un cycle
		SommetsMarques = new Maillon<Sommet>(depart, SommetsMarquesParent);

		//Parcourir tous les voisins;
		voisins = g->voisins(depart);
		for (; voisins; voisins = voisins->suivant) {
			if (detection_circuit_recursif(g, voisins->valeur, SommetsMarques)) {
				return true;
			}
		}
		return false;
	}
}