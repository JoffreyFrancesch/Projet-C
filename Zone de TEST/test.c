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
  Section current_section;

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

typedef enum Section {
  s_in_left,
  s_out_right,
  s_stop_A,
  s_stop_B,
  s_stop_C,
  s_stop_D
} Section;
////////////////////////
char chooseDest(){ ////Choisie la destination
  switch (rand()%4) {
    case 0:
      return 'A';
      break;
    case 1:
      return 'B';
      break;
    case 2:
      return 'C';
      break;
    case 3:
      return 'D';
      break;
  }
  return 'X';
}

listAvion setDest(listAvion tmpAvion){
  switch (tmpAvion->vehicule) {
    case 'A':
      tmpAvion->destination = PORTE_A;
      break;
    case 'B':
      tmpAvion->destination = PORTE_B;
      break;
    case 'C':
      tmpAvion->destination = PORTE_C;
      break;
    case 'D':
      tmpAvion->destination = PORTE_D;
      break;
  }
  if(tmpCar->dangerous)
  {
      tmpCar->vehicle='D';
  }
  return tmpAvion;
}

listAvion newAvion(int x_pos, int y_pos, bool speed, char direction, bool dangerous, Section zone, listCar existingAvion){
  Avion* avionTmp = (Avion*)malloc(sizeof(Avion));
  avionTmp->speed = speed;
  avionTmp->x_pos = x_pos;
  avionTmp->y_pos = y_pos;
  avionTmp->vehicle=direction;
  avionTmp->current_section=zone;
  avionTmp->state= true;
  avionTmp->broken= false;
  avionTmp->next=NULL;
  avionTmp->hs=false;
  avionTmp->dangerous=dangerous;
  avionTmp=setDest(avionTmp);

  if(existingAvion == NULL){
    return avionTmp
  }
  listAvion tmp = existingAvion;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next=avionTmp;

  return existingAvion;
}


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
