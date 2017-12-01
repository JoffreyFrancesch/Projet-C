#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../fichier_h/menu.h"
#include "../fichier_h/vehicule.h"

int main() {
  system("clear");
  srand(time(NULL));
  system("setterm -cursor off");//désactive le curseur (uniquement Ubuntu)
  int i, j;
  char* fichier = "fichier_txt/map_cp.txt";

  MAPTAILLE taille = getTaille(fichier);
  //matrice de la carte
  int** matrice = (int**) malloc(taille.hauteur * sizeof(int*));
  for (i = 0; i < taille.hauteur; i++) {
    matrice[i] = (int*) malloc(taille.largeur * sizeof(int));
  }
  //matrice pour les information des casses si elle sont occupee ou non
  char** occupee = (char**) malloc(taille.hauteur * sizeof(char*));
	for (i = 0; i < taille.largeur; i++) {
		occupee[i] = (char*) malloc(taille.largeur * sizeof(char));
	}
  //on met la matrice occupee = 0 partout 
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
      printf("\033[10;83H");
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
        case '4' :
          printf("EASTER EGG\n");
          mode = 4;
          flag = 1;
          break;
        default :
          printf("Choix inconnu\n");
      }
    }

    int nombre_Voitures;

    if(mode == 1){
      nombre_Voitures = 20;//NORMAL
    } else if(mode == 4) {
      nombre_Voitures = 60;//EASTER EGG
    } else {
      nombre_Voitures = 40;//DANGER
    }

  initMatrice(matrice, fichier, taille);
  //calcul des entree
  CALCUL_POINT_ALEATOIRE* calcul = calculEntrees(matrice, taille);
  //creation de la listes des feux
  FEUX* listeFeux = Feux(matrice, taille);
  //creation de la listes des voitures
	VOITURE* setupVoitures = CreerListeVoiture(nombre_Voitures, calcul, occupee);
  //creation des tram
  TRAM* listeTram = CreerTram(matrice, taille);
  //creation de l'avion
	AVION* avion = CreerAvion(matrice, taille);


  system("clear");
  //on afficher une premiere fois la map
  afficherPlanFinal(matrice, taille, setupVoitures, listeFeux, listeTram, avion);
  do {//boucle jusqu'a que 'q' soit rentree
    usleep(100000);//attente regle aussi la vitesse de la simulation
    //Deplacer tout vehicule (avion tram voiture et les feux)
    avancerTram(listeTram, taille, matrice);
    deplacementAvion(avion, taille);
    deplacementVoiture(setupVoitures, calcul, matrice, occupee, taille, mode);
    activerFeux(listeFeux, occupee, taille);
    //positionement du curseur tout en haut
    printf("\033[1;1H");
    //afficher le nouveaux plan avec les nouvelles position des vehicules
    afficherPlanFinal(matrice, taille, setupVoitures, listeFeux, listeTram, avion);
    printf("\033[5;40;1;31m\033[44;1H TAPEZ 'q' pour quitter\033[0m\n");
} while(key_pressed()!=113);

  system("clear");
  //menu de remerciement
  menu_quitter();
  usleep(5000000);
  system("setterm -cursor on");//réactive le curseur (uniquement ubuntu)
  return 0;
}
