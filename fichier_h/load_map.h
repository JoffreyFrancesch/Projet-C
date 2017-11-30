#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

typedef struct mapTaille MAPTAILLE;

struct mapTaille {
	int hauteur, largeur;
};


MAPTAILLE getTaille(char *filename);
void initMatrice(int** matrice, char* filename, MAPTAILLE taille);

char key_pressed();
