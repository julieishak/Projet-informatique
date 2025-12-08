#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 

#define HAUTEUR 10
#define LARGEUR 9
#define DUREE 120000
#define PAS_DE_FIGURE 0
#define SUITE_LIGNE 1
#define SUITE_COLONNE 2
#define CARRE 3
#define CROIX 4
#define TAILLE_CARRE 4
#define TAILLE_CROIX 5
#define TAILLE_BONUS_COUPS 5         //Ajout par nous
#define TAILLE_BONUS_EXPLOSION 6     //Bonus imposé par la consigne

char grille[HAUTEUR][LARGEUR];		//Déclaration de la variable globale grille (matrice de taille HAUTEUR*LARGEUR) utilisé dans la majorité des sous-programme de ce module

void eliminerSuiteEnLigne(int ligne, int colonne, int taille) {
	for (int i=0; i<taille; i++) {                      
		grille[ligne][colonne + i] = 0; //Parcourir les cases de la suite de gauche à droite
	}	
}

void eliminerSuiteEnColonne(int ligne, int colonne, int taille) {
	for (int i=0; i<taille; i++) {
		grille[ligne + i][colonne] = 0; //Parcourir les cases de la suite de haut en bas et affecter 0 à chacune de ces cases
	}	
}

void eliminerCarre (int ligne, int colonne) {
	for (int i=0; i<TAILLE_CARRE; i++) {
		grille[ligne][colonne + i] = 0;                 //Parcourir la ligne la plus haute du carre de gauche à droite et affecter 0 à chacune de ces cases
		grille[ligne+TAILLE_CARRE-1][colonne + i] = 0;  //Parcourir la ligne la plus basse du carre de gauche à droite et affecter 0 à chacune de ces cases
	}	
	for (int i=0; i<TAILLE_CARRE; i++) {
		grille[ligne + i][colonne] = 0;                 //Parcourir la ligne la plus à gauche du carre de haut en bas en affectant 0 à chacune de ces cases
		grille[ligne + i][colonne+TAILLE_CARRE-1] = 0;  //Parcourir la ligne la plus à droite du carre de haut en bas en affectant 0 à chacune de ces cases
	}
}

void eliminerCroix (int ligne, int colonne) {
	for (int i=0; i<TAILLE_CROIX; i++) {
		grille[ligne][colonne + i - 2] = 0;				//Se placer au centre de la croix, aller 2 cases vers la gauche et parcourir les cases de gauche à droite en affectant 0 à chacune de ces cases
	}	
	for (int i=0; i<TAILLE_CROIX; i++) {
		grille[ligne + i - 2][colonne] = 0;				//Se placer au centre de la croix, aller 2 cases vers la haut et parcourir les cases de gauche à droite en affectant 0 à chacune de ces cases
	}	
}

void eliminerFigure (int type, int ligne, int colonne, int taille) {			//Elimine la fonction adéquate en fonction du type de la figure
	switch(type) {															
	case SUITE_LIGNE : eliminerSuiteEnLigne (ligne, colonne, taille);
		break;
	case SUITE_COLONNE : eliminerSuiteEnColonne (ligne, colonne, taille);
		break;
	case CARRE : eliminerCarre(ligne, colonne);
		break;
	case CROIX : eliminerCroix (ligne, colonne);
		break;
	}
}

void melangerItems() {									//Echange les coordonnées de deux items choisis aléatoirement
	int l1, int c1, int l2, int c2, int temp;
	l1 = rand() % HAUTEUR;
	l2 = rand() % HAUTEUR;
	c1 = rand() % LARGEUR;
	c2 = rand() % LARGEUR;

	temp = grille[l1][c1];							
	grille[l1][c1] = grille[l2][c2];				
	grille[l2][c2] = temp;
}


int jeu (int temps_restant) {
	int type, int ligne, int colonne, int taille;
	int touche_pressee;

	srand(time(NULL));
	 do {
	 	detecterFigure(&type, &ligne, &colonne, &taille);
	 	if (type!=PAS_DE_FIGURE) {
	 		printf("Il y a deja des combinaisons possibles. Melange en cours ...");
			melangerItems();	
	 	}
	} while (type!=PAS_DE_FIGURE);	
	
	deplacementTouches(touche_pressee);
	selectionItems(touche_pressee);
	appliquerGravite();
	detecterSuiteEnLigne();
	eliminerSuiteEnLigne(ligne, colonne, taille);
	detecterSuiteEnColonne();
	eliminerSuiteEnColonne(ligne, colonne, taille);
	detecterCroix();
	eliminerCroix(ligne, colonne);
	detecterCarre();
	eliminerCarre(ligne, colonne);
	decterFigure();
	eliminerFigure(type_items, ligne, colonne, taille);

	if (gererContrat==1) {
		gererVictoireNiveau(duree, temps_restant);
	}
	if (temps_restant==0&&gererContrat!=1) {
		gererPerteVies(vies);
		gererEchecNiveau(vies);
	}
}


