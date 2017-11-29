#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "../fichier_h/load_map.h"
#include "../fichier_h/menu.h"
#include "../fichier_h/vehicule.h"

int main() {
  system("clear");
  srand(time(NULL));
  //system("play -q &");
  int i, j;
  char* fichier = "fichier_txt/map_cp.txt";

  printf("OK\n");

  MAPTAILLE taille = getTaille(fichier);
  printf("OK1\n");
  int** matrice = (int**) malloc(taille.hauteur * sizeof(int*));
  for (i = 0; i < taille.hauteur; i++) {
    matrice[i] = (int*) malloc(taille.largeur * sizeof(int));
  }
  printf("OK2\n");

  char** occupee = (char**) malloc(taille.hauteur * sizeof(char*));
	for (i = 0; i < taille.largeur; i++) {
		occupee[i] = (char*) malloc(taille.largeur * sizeof(char));
	}
	for (i = 0; i < taille.hauteur; i++) {
		for (j = 0; j < taille.largeur; j++) {
			occupee[i][j] = 0;
		}
	}
  printf("OK3\n");

  initierMatrice(matrice, fichier, taille);
  CALCUL_POINT_ALEATOIRE* calcul = calculEntrees(matrice, taille);
  FEUX* listeFeux = Feux(matrice, taille);

  int nombre_Voitures = 15;
	VOITURE* setupVoitures = CreerListeVoiture(nombre_Voitures, calcul, occupee);

  TRAM* listeTram = CreerTram(matrice, taille);
	AVION* avion = CreerAvion(matrice, taille);

  int mode = 1;
  afficherPlan3(matrice, taille, setupVoitures, listeFeux, listeTram, avion);
  for (i = 0; i < 2000; i++) {

    usleep(200000);
    avancerTram(listeTram, taille, matrice);
    deplacementAvion(avion, taille);
    deplacementVoiture(setupVoitures, calcul, matrice, occupee, taille, mode);
    activerFeux(listeFeux, occupee, taille);
    system("Clear");
    afficherPlan3(matrice, taille, setupVoitures, listeFeux, listeTram, avion);
  }

  for (i = 0; i < taille.hauteur; i++) {
		free(matrice[i]);
	}
	free(matrice);

  return 0;
}
