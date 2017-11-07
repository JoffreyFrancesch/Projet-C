#include "../fichier_h/load_map.h"

typedef struct wagon {
  int pos_l,pos_c;
  struct wagon *succ;
}wagon;

typedef wagon *tram;

void affiche_map(){
  system("clear");
  FILE * map = fopen("./fichier_txt/map.txt","r");
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

char key_pressed() {
	struct termios oldterm, newterm;
	int oldfd;
	char c, result = 0;

	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);

	if (c != EOF) {
		ungetc(c, stdin);
		result = getchar();
	}
	return result;
}
/*void temps(double seconde){
    seconde*=1000000;
    fflush(stdout);
    usleep(seconde);
}*/
