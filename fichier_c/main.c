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



  MAPTAILLE taille = getTaille(fichier);

  int** matrice = (int**) malloc(taille.hauteur * sizeof(int*));
  for (i = 0; i < taille.hauteur; i++) {
    matrice[i] = (int*) malloc(taille.largeur * sizeof(int));
  }

  char** occupee = (char**) malloc(taille.hauteur * sizeof(char*));
	for (i = 0; i < taille.largeur; i++) {
		occupee[i] = (char*) malloc(taille.largeur * sizeof(char));
	}
	for (i = 0; i < taille.hauteur; i++) {
		for (j = 0; j < taille.largeur; j++) {
			occupee[i][j] = 0;
		}
	}
  affichage_menu();
    char choix;
    int mode;
    int flag=0;
    while (flag!=1) {
      scanf("%c",&choix);
      switch (choix) {
        case '1' :
          printf("Vous avez choisi le mode NORMAL\n");
          flag = 1;
          mode = 1;
          break;
        case '2' :
          printf("Vous avez choisi le mode DANGER\n");
          flag = 1;
          mode = 2;
          break;
        case '3' :
          printf("Vous avez quittez\n");
          flag = 1;
          system("clear");
          menu_quitter();
          usleep(5000000);
	        return 0;
          break;
        default :
          printf("Choix inconnu\n");
      }
    }
    int nombre_Voitures;
    if(mode == 1){
      nombre_Voitures = 20;
    } else {
      nombre_Voitures = 40;
    }
  initierMatrice(matrice, fichier, taille);
  CALCUL_POINT_ALEATOIRE* calcul = calculEntrees(matrice, taille);
  FEUX* listeFeux = Feux(matrice, taille);


	VOITURE* setupVoitures = CreerListeVoiture(nombre_Voitures, calcul, occupee);

  TRAM* listeTram = CreerTram(matrice, taille);
	AVION* avion = CreerAvion(matrice, taille);


  afficherPlanFinal(matrice, taille, setupVoitures, listeFeux, listeTram, avion);
  do {
    usleep(200000);
    avancerTram(listeTram, taille, matrice);
    deplacementAvion(avion, taille);
    deplacementVoiture(setupVoitures, calcul, matrice, occupee, taille, mode);
    activerFeux(listeFeux, occupee, taille);
    system("c                                             lear");
    afficherPlanFinal(matrice, taille, setupVoitures, listeFeux, listeTram, avion);
    printf("\033[5;40;1;31m\033[44;1H TAPEZ 'q' pour quitter\033[0m\n");
} while(key_pressed()!=113);

  for (i = 0; i < taille.hauteur; i++) {
		free(matrice[i]);
	}
	free(matrice);

  system("clear");
  menu_quitter();
  usleep(5000000);

  return 0;
}
