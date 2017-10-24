#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
////////////////////////////
void affiche_map(){
  system("clear");
  FILE * map = fopen("../fichier_txt/map.txt","r");
  char c;
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
      default : printf("%c",c);
    }
  }
  printf("\n");
  fclose(map);
}
////////////////////////
void tram1(int pos_l1){
  if (pos_l1 <= 43) {
    printf("\033[%d;30H█\n",pos_l1);
  }
  if (pos_l1-1 >= 6 && pos_l1-1 <= 43){
    printf("\033[%d;30H \n",pos_l1-1);
  }
}
void tram2(int pos_l2){
  if (pos_l2 >= 6) {
    printf("\033[%d;165H█\n",pos_l2);
  }
  if (pos_l2+1 <= 43 && pos_l2+1 >= 6){
    printf("\033[%d;165H \n",pos_l2-1);
  }
}
////////////////////////


int main(int argc, char  *argv[]) {
  affiche_map();
  int pos_l1 = 6;
  int pos_l2 = 43;
  while (1) {
    tram1(pos_l1);
    tram2(pos_l2);
    pos_l1 = pos_l1+1;
    pos_l2 = pos_l2-1;
    usleep(100000);

    //tram2(43,164);
  }


  printf("\033[44;0HEND\n");
  return 0;
}
