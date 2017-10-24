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
      default : printf("%c",c);
    }
  }
  printf("\n");
  fclose(map);
}
////////////////////////
void tram1(){
  int pos_l = 43;
  int pos_c = 29;
  while (pos_l != 17) {
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if(pos_l+1 <= 43){
      printf("\033[%d;%dH│\n",(pos_l+1),pos_c);
    }
    if(pos_l == 30){
      usleep(500000);
    }
    usleep(100000);
    pos_l = pos_l-1;
  }
  pos_l = 18;
  while(pos_c != 49){
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if(pos_c-1 == 29){
      printf("\033[18;29H┌\n");
    }
    if(pos_c-1 >= 30) {
      printf("\033[%d;%dH─\n",pos_l,pos_c-1);
    }
    if (pos_c == 40) {
      usleep(500000);
    }
    usleep(100000);
    pos_c = pos_c+1;
  }
  printf("\033[18;48H─\n");
  usleep(100000);
  pos_c = 150;
  while (pos_c != 170) {
      printf("\033[%d;%dH█\n",pos_l,pos_c);
      if ((pos_c-1 > 149) && (pos_c-1 <169)) {
        printf("\033[%d;%dH─\n",pos_l,pos_c-1);
      }
      if(pos_c == 158){
        usleep(500000);
      }
      usleep(100000);
      pos_c = pos_c+1;
  }
  pos_c = 169;
  while (pos_l != 44) {
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if (pos_l-1 == 18) {
      printf("\033[18;169H┐\n");
    }
    if(pos_l-1 >= 19){
      printf("\033[%d;%dH│\n",(pos_l-1),pos_c);
    }
    if(pos_l == 30){
      usleep(500000);
    }
    usleep(100000);
    pos_l = pos_l+1;
    }
  printf("\033[43;169H│\n");
}
void tram2(){
  int pos_l = 43;
  int pos_c = 164;
  while (pos_l != 19) {
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if (pos_l+1 <= 43) {
      printf("\033[%d;%dH│\n",(pos_l+1),pos_c);
    }
    if (pos_l == 30){
      usleep(500000);
    }
    usleep(100000);
    pos_l = pos_l-1;
  }
  pos_l = 20;
  while (pos_c != 149) {
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if(pos_c+1 == 164){
      printf("\033[20;164H┐\n");
    }
    if(pos_c+1 <= 163){
      printf("\033[%d;%dH─\n",pos_l,pos_c+1);
    }
    if(pos_c == 158){
      usleep(500000);
    }
    usleep(100000);
    pos_c = pos_c-1;
  }
  printf("\033[20;150H─\n");
  usleep(100000);
  pos_c = 48;
  while (pos_c != 33) {
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if ((pos_c+1 > 34) && (pos_c+1 <49)) {
      printf("\033[%d;%dH─\n",pos_l,pos_c+1);
    }
    if(pos_c == 40){
      usleep(500000);
    }
    usleep(100000);
    pos_c = pos_c-1;
  }
  pos_c = 34;
  while (pos_l != 44) {
    printf("\033[%d;%dH█\n",pos_l,pos_c);
    if (pos_l-1 == 20) {
      printf("\033[20;34H┌\n");
    }
    if(pos_l-1 >= 21){
      printf("\033[%d;%dH│\n",(pos_l-1),pos_c);
    }
    if(pos_l == 30){
      usleep(500000);
    }
    usleep(100000);
    pos_l = pos_l+1;
    }
  printf("\033[43;34H│\n");

}
////////////////////////

int main(int argc, char  *argv[]) {
  affiche_map();
  while (1) {
    tram1();
    tram2();
  }

  printf("\033[44;0HEND\n");
  return 0;
}
