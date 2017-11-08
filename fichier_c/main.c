#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../fichier_h/load_map.h"
#include "../fichier_h/menu.h"
#include "../fichier_h/vehicules.h"

int main() {
  system("clear");
  srand(time(NULL));
  //system("printf '\e[8;44;177t'");
  affichage_menu();
  char choix;
  int flag=0;
  while (flag!=1) {
    scanf("%c",&choix);
    switch (choix) {
      case '1' :
        printf("Vous avez choisi le mode NORMAL\n");
        affiche_map();
        mouvement();
        flag = 1;
        break;
      case '2' :
        printf("Vous avez choisi le mode DANGER\n");
        affiche_map();
        flag = 1;
        break;
      case '3' :
        printf("Vous avez quittez\n");
        flag = 1;
        return 0;
        break;
      default :
        printf("Choix inconnu\n");
    }
  }
printf("SUCESS\n");


  return 0;
}
