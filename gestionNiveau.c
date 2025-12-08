#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#define HAUTEUR 10
#define LARGEUR 9
#define DUREE 120000
int niveau=1;

lancerNiveau(int xcurseur, int ycurseur, int temps_restant) {
	xcurseur=LARGEUR/2;
	ycurseur=HAUTEUR/2;
	jeu(temps_restant);
	viderGrille();
	genererItems();
	assurerGrilleJouable();
	afficherGrille();
	afficherNumeroDuNiveau(niveau);
	afficherNombreDeVies(vies);
	afficherTempsRestants(temps_fin, temps_restant);
	afficherCoupsRestants(coups_restants);
	afficherRegles();
	afficherItemsRestants(type_items);

	switch(niveau) {
		case 1: printf("");			//Afficher 1e contrat du niveau 1
			break;
		case 2: printf("");			//Afficher le contrat du niveau 2
			malus(ligne, colonne);	//Ajout du malus au niveau 2
			break;
		case 3: printf("");			//Afficher le contrat du niveau 3
			malus(ligne, colonne);	//Ajout du malus au niveau 3
			break;

	}
}


