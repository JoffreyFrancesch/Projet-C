#include "../fichier_h/load_map.h"

//récupération de la taille de la carte dans le fichier .txt
MAPTAILLE getTaille(char* filename) {
	FILE *fichier=NULL;
	MAPTAILLE taille;
	int c;

	fichier = fopen(filename, "r");

	taille.hauteur = 0;
	taille.largeur = 0;

	if (fichier == NULL) printf("ERREUR\n");

	while ((c = fgetc(fichier)) != EOF) {

		if (taille.hauteur == 0) {
			taille.largeur++;
		}
		if (c == '\n') {
			taille.hauteur++;
		}
	}
	taille.hauteur++;
	taille.largeur--;
	fclose(fichier);
	return taille;
}

//permet de mettre la carte dans la matrice defini dans le main
void initMatrice(int** matrice, char* filename, MAPTAILLE taille) {
	FILE *fichier;
	int c;
	int i = 0, j = 0;
	fichier = fopen(filename, "r");
	while ((c = fgetc(fichier)) != EOF) {
		if (c == '\n') {
			j = 0;
			i++;
		} else {
			matrice[i][j] = c;
			j++;
		}
	}
	fclose(fichier);
}

//fonction qui permet de faire la condition de sortie de la boucle pour la simulation
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
