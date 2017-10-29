#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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
void tram1(int pos_l1){
  if (pos_l1 <= 43) {
    printf("\033[0;31m\033[%d;30H█\033[0m\n",pos_l1);
    if (pos_l1 >= 7) {
      printf("\033[0;31m\033[%d;30H█\033[0m\n",pos_l1-1);
    }
    if (pos_l1 >= 8){
      printf("\033[0;31m\033[%d;30H█\033[0m\n",pos_l1-2);
    }
  }
  if (pos_l1-3 >= 6 && pos_l1-3 <= 43){
    printf("\033[%d;30H \n",pos_l1-3);
  }
  if (pos_l1-2 == 41) {
    printf("\033[41;30H \n");
    printf("\033[0;31m\033[42;30H█\033[0m\n");
  }
  if (pos_l1-1 == 42) {
    printf("\033[42;30H \n");
    printf("\033[0;31m\033[43;30H█\033[0m\n");
  }
}
void tram2(int pos_l2){
  if (pos_l2 >= 6) {
    printf("\033[0;31m\033[%d;165H█\033[0m\n",pos_l2);
    if (pos_l2 <= 42) {
      printf("\033[0;31m\033[%d;165H█\033[0m\n",pos_l2+1);
    }
    if (pos_l2 <= 41) {
      printf("\033[0;31m\033[%d;165H█\033[0m\n",pos_l2+2);
    }
  }
  if (pos_l2+3 <= 43 && pos_l2+3 >= 6){
    printf("\033[%d;165H \n",pos_l2+3);
  }
  if (pos_l2+2 == 8) {
    printf("\033[8;165H \n");
    printf("\033[0;31m\033[7;165H█\033[0m\n");
  }
  if (pos_l2+1 == 7) {
    printf("\033[7;165H \n");
    printf("\033[0;31m\033[6;165H█\033[0m\n");
  }
}
////////////////////////


int main(int argc, char  *argv[]) {
  system("setterm -cursor off");// supprime l'affichage du curseur sur Linux
  srand(time(NULL));
  affiche_map();
  int pos_l1 = 6;
  int pos_l2 = 43;
  while (1) {
    tram1(pos_l1);
    tram2(pos_l2);
    pos_l1 = pos_l1+1;
    pos_l2 = pos_l2-1;
    usleep(100000);
    if (pos_l1 == 44 && pos_l2 == 5) {
      pos_l1 =6;
      pos_l2 = 43;
      printf("\033[43;30H \033[6;165H \n");
    }
  /*if (pos_l1 == 14 || pos_l2 == 12) {
      usleep(500000);
    }*/
  }


  printf("\033[44;0HEND\n");
  return 0;
}
