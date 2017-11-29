#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "load_map.h"

typedef struct pointEntree POINT_ALEATOIRE;
typedef struct voiture VOITURE;
typedef struct point ENTREE;
typedef struct CalculAleatoirePoint CALCUL_POINT_ALEATOIRE;
typedef struct feux FEUX;
typedef struct tram TRAM;
typedef struct point POINT;
typedef struct tramChemin CHEMIN;
typedef struct avion AVION;

struct voiture {
	char direction;
	int posx, posy;
	int vistesse;
	char type;
	char etat;
	int temps;
	int essence;
	POINT_ALEATOIRE* entree;
	struct voiture *next;
	int tempPanne;
};

struct avion {
	int x, y;
	int hauteur, largeur;
	int temp;
};

struct tram {
	char direction;
	int posx, posy;
	char etat;
	int temps;
	int longeur;
	int stopTime;
	POINT* entree;
	POINT* sortie;
	TRAM* next;
};

struct tramChemin {
	POINT* entree;
	POINT* sortie;
	CHEMIN* next;
};

struct point {
	int x, y;
	char direction;
	struct point *next;
};

struct CalculAleatoirePoint {
	int total;
	POINT_ALEATOIRE* liste;
};

struct pointEntree {
	int x, y;
	char direction;
	char occupee; //0 => non, 1 => oui
};

struct feux {
	int x, y;
	char direction;
	char etat; //r -> rouge, v -> vert
	int portee; // nombre de carres affectes par a feux
	int compteur; //compter le temp de feux
	FEUX* next;
};

void freeListeEntree(ENTREE* liste);
char checkCharacter(char* chaine, int longeur, char c);
char checkPortee(int num, int a, int b);
void printCharacterEnBlancSurFontNoir(char* c);
void printCharacter(int c);
void printCharacterSpe(int c, int terrain);
void afficherPlan(int** matrice, MAPTAILLE taille, int** plan);
void dessinerAvion(int** matrice, MAPTAILLE taille, AVION* avion);
void afficherPlan3(int** matrice, MAPTAILLE taille, VOITURE* voitures, FEUX* feux, TRAM* tram, AVION* avion);
CALCUL_POINT_ALEATOIRE* calculEntrees(int** matrice, MAPTAILLE taille);
void ValeurDeFeux(FEUX* feux, int x, int y, int** matrice);
FEUX* Feux(int** matrice, MAPTAILLE taille);
int nbAleatoire(int nb);
int Panne();
void PositionAleatoire(VOITURE* voiture, CALCUL_POINT_ALEATOIRE* listeEntrees, char** occupee);
void eviterPanne(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice);
void AllerEnHaut(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice);
void AllerEnBas(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice);
void AllerADroite(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice);
void AllerAGauche(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice);
void avancerVoiture(VOITURE* voiture, int direction, char** occupee, MAPTAILLE taille, int** matrice);
void changeFeuxEtat(FEUX* feux, char** occupee, MAPTAILLE taille, char bloquee, char etat);
void deplacementVoiture(VOITURE* voitures, CALCUL_POINT_ALEATOIRE* listEntrees, int** matrice, char** occupee, MAPTAILLE taille, int mode);
void feuxVert(FEUX* feux, char** occupee, MAPTAILLE taille);
void feuxRouge(FEUX* feux, char** occupee, MAPTAILLE taille);
void activerFeux(FEUX* feux, char** occupee, MAPTAILLE taille);

VOITURE* CreerListeVoiture(int nombreVoitures, CALCUL_POINT_ALEATOIRE* listeEntrees, char** occupee);
CHEMIN* TramEntree(int** matrice, MAPTAILLE taille);
TRAM* CreerTram(int** matrice, MAPTAILLE taille);
void avancerTram(TRAM* tram, MAPTAILLE taille, int** matrice);
AVION* CreerAvion(int** matrice, MAPTAILLE taille);
void deplacementAvion(AVION* avion, MAPTAILLE taille);
