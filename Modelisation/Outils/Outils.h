#pragma once
#include "../Graphe/Graphe.h"


bool aucuneValuationNegative(Maillon<Arc> *lArc) {
	if (lArc != NULL) {
		if (lArc->valeur->coutArc < 0 || lArc->valeur->tempsArc < 0) return false;
		return aucuneValuationNegative(lArc->suivant);
	}
	// On est arrive a la fin de la liste des arcs, donc on peut renvoyer true
	return true;
}
