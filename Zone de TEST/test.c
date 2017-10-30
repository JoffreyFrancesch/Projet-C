#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <stdbool.h>// librairie pour utiliser un boolean
////////////////////////////
void affiche_map(){
  system("clear");
  FILE * map = fopen("../fichier_txt/map.txt","r");
  char c;
  int arbre;
  while ((c = fgetc(map))!=EOF) {
    //printf("%c",c);
    switch (c) {
      case 'H' : printf("═"); break;
      case 'V' : printf("║"); break;
      case 'T' : printf("─"); break;
      case 'A' : printf("╔"); break;
      case 'B' : printf("╚"); break;
      case 'C' : printf("╝"); break;
      case 'D' : printf("╗"); break;
      case 'b' : printf("│"); break;
      case 'x' : printf("┐"); break;
      case 'y' : printf("┌"); break;
      case 'z' : printf("└"); break;
      case 'w' : printf("┘"); break;
      case 'S' : printf("┬"); break;
      case 'F' : printf("┤"); break;
      case 'f' : printf("├"); break;
      case 'j' : printf("┴"); break;
      case 'E' : printf("█"); break;
      case 'v' : printf("┼"); break;
      case 'm'  : printf("║"); break;
      case 'P' :
         arbre = rand()%4;
         if (arbre == 0) {
           printf("🌳");
         } else if (arbre == 1) {
           printf("🌴");
         } else if (arbre == 2) {
           printf("🌲");
         } else if (arbre == 3) {
           printf("🌵");
         } break;
      default : printf("%c",c);
    }
  }
  printf("\n");
  fclose(map);
}
////////////////////////
struct Avion {
  char vehicule; //definie ce qui va être mis sur le terminal
  bool vitesse; //definie la vitesse
  unsigned short x_pos; //definie la position de la ligne
  unsigned short y_pos; //definie la position de la colonne

  Direction destination; //definie quel porte il va prendre

  bool state;//<Defines if the car has to be deleted (TRUE=active, FALSE=inactive).
  bool broken;//<Defines if the car is broken (TRUE=broken down, FALSE=intact).
  bool hs;//<Defines if the car has broken down by itself (TRUE=broken down, FALSE=intact).
  bool dangerous;//definie le mode de simu choisie

  struct Avion *next; // pointe sur le prochain element
};
typedef struct Avion Avion;
typedef Avion* listAvion;

typedef enum Direction {
  PORTE_A,
  PORTE_B,
  PORTE_C,
  PORTE_D
} Direction;
////////////////////////


int main(int argc, char  *argv[]) {
  system("setterm -cursor off");// supprime l'affichage du curseur sur Linux
  srand(time(NULL));
  system("printf '\e[8;44;177t'");
  affiche_map();
    }
  }


  printf("\033[44;0HEND\n");
  return 0;
}
