#include "../fichier_h/vehicule.h"

#define NRM  "\033[0m" //BLANC
#define RED  "\033[31m"//ROUGE
#define YEL  "\033[33m"//JAUNE
#define BLU  "\033[34m"//BLEU
#define GRN  "\033[32m"//VERT
#define BLK  "\033[30m"//NOIR

int FEUX_DUREE = 15;//TEMPS DES FEUX
int TEMPS_ATTENTE = 4;//TEMPS D'ATTENTE
int PANNE_DUREE = 10;//TEMPS DE LA PANNE
int TRAM_ATTENTE = 12;//TEMPS D'ATTENTE TRAM
int TRAM_STOP = 5;//TEMPS ARRET TRAM

char avionImage[2][11] = {
 	{'|','\\','_','_','_','|','\\','_','_','_',' '},
 	{'|','_','_','_','_','_','_','_','_','_', '\\'}
 };

//suppression de listes des entrees
void freeListeEntree(ENTREE* liste) {
	ENTREE* temp = NULL;
	ENTREE* cour = liste;
	while (cour != NULL) {
		temp = cour;
		cour = cour->next;
		free(temp);
	}
}

//Permet de déterminer si c'est une chaine ou un cractère seul
char checkCharacter(char* chaine, int longeur, char c) {
	int i;
	for (i = 0; i < longeur; i++) {
		if (chaine[i] == c) {
			return 1;
		}
	}
	return 0;
}

//Permet de checker la portée entre a et b utilisee pour les feux
char checkPortee(int num, int a, int b) {
	if (a >= b && a >= num && num >= b){
		return 1;
	}

	if (a <= b && a <= num && num <= b){
		return 1;
	}

	return 0;
}

//Permet d'afficher les caractere non specifique
void printCharacter(int c) {
	switch (c) {
      	case 'H' : printf("═"); break;
      	case 'V' : printf("║"); break;
     	     case 'T' :
     	      case 't' :
                  printf("─");
     		           break;
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
      	case 'm' : printf("\033[46m║\033[0m"); break;
      	case 'G' : printf("▒"); break;
      	case 'P' : printf(GRN "♣" NRM); break;
        case 'l':
        case 'r':
        case 'u':
        case 'd':
        case 'g':
        case 'h':
        case 'i':
        case 'k':

        	printf("\033[40m \033[0m");
        	break;
        case 'Q':
        case 'A':
        case 's':
				case 'a':
        	printf(" ");
        	break;
        case 'R':// Feux rouge
        	printf(RED "█" NRM);
        	break;
        case 'B':// Feux bleu
        	printf(GRN "█" NRM);
        	break;
      default : printf("%c",c);
    }
}

//Permet d'afficher les caractère spécique des voitures et tram
void printCharacterSpe(int c, int terrain) {
	if (c == '$') {
		//Icone pour la voiture
		printf(RED "\033[40m▣" NRM);
	} else if (c == '%') {
		// Icone pour le tram
		printf(YEL "▓" NRM);
  } else if (c == '!'){
    //icone voiture en panne
    printf(YEL "\033[40m✟" NRM);
  } else {//afficher caractère non voiture et non tram
		printCharacter(c);
	}
}

//Afficher la map
void afficherPlan(int** matrice, MAPTAILLE taille, int** plan) {
	int i, j;
	for (i = 0; i < taille.hauteur; i++) {
		for (j = 0; j < taille.largeur; j++) {
			printCharacterSpe(matrice[i][j], plan[i][j]);
		}
		printf("\n");
	}
}
//Dessiner Avion
void dessinerAvion(int** matrice, MAPTAILLE taille, AVION* avion) {
	if (avion != NULL){
		int i, j;
		int posx, posy;
		for (i = 0; i < avion->hauteur; i++){
			for (j = 0; j < avion->largeur; j++){
				posx = avion->x - i;
				posy = avion->y - j;
				if (checkPortee(posx, 0, taille.hauteur-1) && checkPortee(posy, 0, taille.largeur-1)) {
					matrice[posx][posy] = avionImage[avion->hauteur - 1 - i][avion->largeur - 1 - j];
				}
			}
		}
	}
}

//Afficher la map final avec voiture , tram, feux, et avion
void afficherPlanFinal(int** matrice, MAPTAILLE taille, VOITURE* voitures, FEUX* feux, TRAM* tram, AVION* avion) {
	int i, j;
	int** planAAficher = (int**) malloc(taille.hauteur * sizeof(int*));
	for (i = 0; i < taille.hauteur; i++) {
		planAAficher[i] = (int*) malloc(taille.largeur * sizeof(int));
	}

	for (i = 0; i < taille.hauteur; i++) {
		for (j = 0; j < taille.largeur; j++) {
			planAAficher[i][j] = -1;
		}
	}

	VOITURE* voiture = voitures;
	while (voiture != NULL) {
		if (voiture->posx >= 0 && voiture->posy >= 0) {
      if(voiture->etat == 'p'){
          planAAficher[voiture->posx][voiture->posy] = '!';
      } else {
			planAAficher[voiture->posx][voiture->posy] = '$';
    }
		}
		voiture = voiture->next;
	}

	FEUX* feu = feux;
	while (feu != NULL) {
		if (feu->etat == 'r') {
			planAAficher[feu->x][feu->y] = 'R';
		} else if (feu->etat == 'b') {
			planAAficher[feu->x][feu->y] = 'B';
		}
		feu = feu->next;
	}

	TRAM* train = tram;
	while (train != NULL) {
		if (train->direction == 'd'){
			for (i = train->posx; i > train->posx - train->longeur; i--){
				if (checkPortee(i, train->entree->x, train->sortie->x)){
					planAAficher[i][train->posy] = '%';
				}
			}
		} else if (train->direction == 'u'){
			for (i = train->posx; i < train->posx + train->longeur; i++){
				if (checkPortee(i, train->entree->x, train->sortie->x)){
					planAAficher[i][train->posy] = '%';
				}
			}
		}
		train = train->next;
	}

	dessinerAvion(planAAficher, taille, avion);

	for (i = 0; i < taille.hauteur; i++) {
		for (j = 0; j < taille.largeur; j++) {
			if (planAAficher[i][j] == -1) {
				planAAficher[i][j] = matrice[i][j];
			}
		}
	}

	afficherPlan(planAAficher, taille, matrice);

	for (i = 0; i < taille.hauteur; i++) {
		free(planAAficher[i]);
	}
	free(planAAficher);
}

//Calculer tout les entrées possibles
CALCUL_POINT_ALEATOIRE* calculEntrees(int** matrice, MAPTAILLE taille) {
	ENTREE* tete = NULL;
	ENTREE* cour = NULL;

	int largeur = taille.largeur, hauteur = taille.hauteur;
	int i;
	int compteur = 0;
	for (i = 0; i < largeur - 2; i++) {
		if (matrice[0][i] == 'd' && matrice[0][i + 1] == 'd'
				&& matrice[0][i + 2] == 'd') {
			if (tete == NULL) {
				tete = malloc(sizeof(ENTREE));
				cour = tete;
			} else {
				cour->next = malloc(sizeof(ENTREE));
				cour = cour->next;
			}
			cour->x = 0;
			cour->y = i + 1;
			cour->direction = 'd';
			cour->next = NULL;
			compteur++;
		}

		if (matrice[hauteur - 1][i] == 'u' && matrice[hauteur - 1][i + 1] == 'u'
				&& matrice[hauteur - 1][i + 2] == 'u') {
			if (tete == NULL) {
				tete = malloc(sizeof(ENTREE));
				cour = tete;
			} else {
				cour->next = malloc(sizeof(ENTREE));
				cour = cour->next;
			}
			cour->x = hauteur - 1;
			cour->y = i + 1;
			cour->direction = 'u';
			cour->next = NULL;
			compteur++;
		}
	}

	for (i = 0; i < hauteur - 2; i++) {
		if (matrice[i][0] == 'r' && matrice[i + 1][0] == 'r'
				&& matrice[i + 2][0] == 'r') {
			if (tete == NULL) {
				tete = malloc(sizeof(ENTREE));
				cour = tete;
			} else {
				cour->next = malloc(sizeof(ENTREE));
				cour = cour->next;
			}
			cour->x = i + 1;
			cour->y = 0;
			cour->direction = 'r';
			cour->next = NULL;
			compteur++;
		}

		if (matrice[i][largeur - 1] == 'l' && matrice[i + 1][largeur - 1] == 'l'
				&& matrice[i + 2][largeur - 1] == 'l') {
			if (tete == NULL) {
				tete = malloc(sizeof(ENTREE));
				cour = tete;
			} else {
				cour->next = malloc(sizeof(ENTREE));
				cour = cour->next;
			}
			cour->x = i + 1;
			cour->y = largeur - 1;
			cour->direction = 'l';
			cour->next = NULL;
			compteur++;
		}
	}

	POINT_ALEATOIRE* liste = NULL;
	CALCUL_POINT_ALEATOIRE* calcul = NULL;
	if (compteur > 0) {
		liste = malloc(compteur * sizeof(POINT_ALEATOIRE));
		cour = tete;
		for (i = 0; i < compteur /*&& compteur != NULL*/; i++) {
			liste[i].x = cour->x;
			liste[i].y = cour->y;
			liste[i].direction = cour->direction;
			liste[i].occupee = 0;
			cour = cour->next;
		}

		calcul = malloc(sizeof(CALCUL_POINT_ALEATOIRE));
		calcul->total = compteur;
		calcul->liste = liste;
		freeListeEntree(tete);
		tete = NULL;
	}
	return calcul;
}

//Permet de calculer le rayon d'action des feux
void ValeurDeFeux(FEUX* feux, int x, int y, int** matrice) {
	feux->x = x;
	feux->y = y;
	feux->compteur = 0;
	int i=0, j=0;
	if(checkCharacter("udlr", 4, matrice[x-1][y])){
		i = -1;
		j = 0;
		feux->direction = 'u';
	} else if (checkCharacter("udlr", 4, matrice[x+1][y])){
		i = 1;
		j = 0;
		feux->direction = 'd';
	} else if (checkCharacter("udlr", 4, matrice[x][y-1])){
		i = 0;
		j = -1;
		feux->direction = 'l';
	} else if (checkCharacter("udlr", 4, matrice[x][y+1])){
		i = 0;
		j = 1;
		feux->direction = 'r';
	}

	char voie = matrice[x + i][y + j];
	int temp_X = x + i, temp_Y = y + j;
	int portee = 0;
	while (matrice[temp_X][temp_Y] == voie) {
		temp_X += i;
		temp_Y += j;
		portee++;
	}
	feux->portee = portee;
}

//Permet de mettre l'etat des feux R -> rouge B -> vert
FEUX* Feux(int** matrice, MAPTAILLE taille) {
	FEUX* tete = NULL;
	FEUX* cour = NULL;
	int i, j;
	for (i = 0; i < taille.hauteur; i++) {
		for (j = 0; j < taille.largeur; j++) {
			if (matrice[i][j] == 'R' || matrice[i][j] == 'B') {
				if (tete == NULL) {
					tete = malloc(sizeof(FEUX));
					cour = tete;
				} else {
					cour->next = malloc(sizeof(FEUX));
					cour = cour->next;
				}
				cour->next = NULL;
				if (matrice[i][j] == 'R'){
					cour->etat = 'r';
				} else {
					cour->etat = 'b';
				}
				ValeurDeFeux(cour, i, j, matrice);
			}
		}
	}
	return tete;
}

//Calcul un nombre aléatoire utiliser pour le choix de direction des voiture
int nbAleatoire(int nb) {
	return rand() % nb;
}

//Faire tomber en panne une voiture avec probabilité de 1/20
int Panne() {
	int i = rand() % 20;
	return i > 0 ? 0 : 1;//return i si i > 0 return 1 si i = 0
}

/*
 * Mettre une voiture a l'entree. Si tous les entrees sont occupees, la voiture doit attendre une duree de TEMPS_ATTENTE
 * Apres cette duree, si il n'y a pas une entree disponible, la voiture doit attendre jusqu'a ce qu'il y ait une disponible
*/
void PositionAleatoire(VOITURE* voiture, CALCUL_POINT_ALEATOIRE* listeEntrees, char** occupee) {
	int i;
	int entreeDisponible = 0;
	for (i = 0; i < listeEntrees->total; i++) {
		if (!listeEntrees->liste[i].occupee) {
			entreeDisponible++;
		}
	}

	if (entreeDisponible > 0 && voiture->temps == 0) {
		int position = nbAleatoire(entreeDisponible);
		int cour = 0;
		for (i = 0; i < listeEntrees->total && cour <= position; i++) {
			if (!listeEntrees->liste[i].occupee && cour < position) {
				cour++;
			} else if (!listeEntrees->liste[i].occupee && cour == position) {
				POINT_ALEATOIRE* point = listeEntrees->liste+i;
				occupee[point->x][point->y] = 1;
				voiture->posx = point->x;
				voiture->posy = point->y;
				voiture->direction = point->direction;
				voiture->etat = 'm';
				voiture->entree = point;
				point->occupee = 1;
				cour++;
			}
		}
	} else if (entreeDisponible > 0 && voiture->temps > 0){
		voiture->temps--;
	} else if (entreeDisponible == 0 && voiture->temps == 0 && voiture->etat == 'm') {
		voiture->posx = -1;
		voiture->posy = -1;
		voiture->temps = TEMPS_ATTENTE;
		voiture->etat = 'h';
	}
}

//Eviter une voiture en panne
void eviterPanne(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice) {
	int posx = voiture->posx, posy = voiture->posy;
	printf("EVITER\n");
	if (voiture->direction == 'l') {
		if ((occupee[posx-1][posy-1] != 2 && checkCharacter("lmaqthsi j", 9, matrice[posx-1][posy-1])) &&
			(occupee[posx-1][posy] == 0 && checkCharacter("lmaqthsi j", 9, matrice[posx-1][posy]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posx = posx-1;
		} else if ((occupee[posx+1][posy-1] != 2 && checkCharacter("lmaqthsi j", 9, matrice[posx+1][posy-1])) &&
					(occupee[posx+1][posy] == 0 && checkCharacter("lmaqthsi j", 9, matrice[posx+1][posy]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posx = posx+1;
		}
	} else if (voiture->direction == 'r') {
		if ((occupee[posx-1][posy+1] != 2 && checkCharacter("rbnqthsi j", 9, matrice[posx-1][posy+1])) &&
			(occupee[posx-1][posy] == 0 && checkCharacter("rbnqthsi j", 9, matrice[posx-1][posy]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posx = posx-1;
		} else if ((occupee[posx+1][posy+1] != 2 && checkCharacter("rbnqthsi j", 9, matrice[posx+1][posy+1])) &&
					(occupee[posx+1][posy] == 0 && checkCharacter("rbnqthsi j", 9, matrice[posx+1][posy]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posx = posx+1;
		}
	} else if (voiture->direction == 'd') {
		if ((occupee[posx+1][posy+1] != 2 && checkCharacter("dabqthsi j", 9, matrice[posx+1][posy+1])) &&
			(occupee[posx][posy+1] == 0 && checkCharacter("dabqthsi j", 9, matrice[posx][posy+1]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posy = posy+1;
		} else if ((occupee[posx+1][posy-1] != 2 && checkCharacter("dabqthsi j", 9, matrice[posx+1][posy-1])) &&
					(occupee[posx][posy-1] == 0 && checkCharacter("dabqthsi j", 9, matrice[posx][posy-1]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posy = posy-1;
		}
	} else if (voiture->direction == 'u') {
		if ((occupee[posx-1][posy+1] != 2 && checkCharacter("umnqthsi j", 9, matrice[posx-1][posy+1])) &&
			(occupee[posx][posy+1] == 0 && checkCharacter("umnqthsi j", 9, matrice[posx][posy+1]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posy = posy+1;
		} else if ((occupee[posx-1][posy-1] != 2 && checkCharacter("umnqthsi j", 9, matrice[posx-1][posy-1])) &&
					(occupee[posx][posy-1] == 0 && checkCharacter("umnqthsi j", 9, matrice[posx][posy-1]))) {
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
			voiture->posy = posy-1;
		}
	}

}

//Deplacer la voiture vers le haut
void AllerEnHaut(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice) {
	int newX = voiture->posx, newY = voiture->posy;
	char eviter = 0;
	if (newX > 0) {
		if (!occupee[newX - 1][newY]) {
			occupee[newX][newY] = 0;
			newX--;
			occupee[newX][newY] = 1;
			voiture->etat = 'm';
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
		} else { // Si le carre devant est occupee
			if (occupee[newX - 1][newY] == 1) { // Dans le cas du feux rouge
				voiture->etat = 's';
			} else if (occupee[newX - 1][newY] == 2) { // Dans le cas d'une voiture devant est en panne
				eviter = 1;
			}
		}
	} else {
		occupee[newX][newY] = 0;
		newX = -1;
		newY = -1;
		voiture->temps = TEMPS_ATTENTE;
		voiture->etat = 'h';
	}
	if (!eviter) {
		voiture->posx = newX;
		voiture->posy = newY;
	} else {
		eviterPanne(voiture, occupee, taille, matrice);
	}

	voiture->direction = 'u';
}

//Déplacer la voiture vers le bas
void AllerEnBas(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice) {
	int newX = voiture->posx, newY = voiture->posy;
	char eviter = 0;
	if (newX < taille.hauteur - 1) {
		// Si la position de devant n'est pas occupee
		if (!occupee[newX + 1][newY]) {
			occupee[newX][newY] = 0;
			newX++;
			occupee[newX][newY] = 1;
			voiture->etat = 'm';
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
		} else { // Si la position devant est occupee
			if (occupee[newX + 1][newY] == 1) { // Dans le cas du feux rouge
				voiture->etat = 's';
			} else if (occupee[newX + 1][newY] == 2) { // Dans le cas d'une voiture devant est en panne
				eviter = 1;
			}
		}
	} else {
		occupee[newX][newY] = 0;
		newX = -1;
		newY = -1;
		voiture->temps = TEMPS_ATTENTE;
		voiture->etat = 'h';
	}
	if (!eviter) {
		voiture->posx = newX;
		voiture->posy = newY;
	} else {
		eviterPanne(voiture, occupee, taille, matrice);
	}
	voiture->direction = 'd';
}

//Deplacement vers la droite
void AllerADroite(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice) {
	int newX = voiture->posx, newY = voiture->posy;
	char eviter = 0;
	if (newY < taille.largeur - 1) {
		if (!occupee[newX][newY + 1]) {
			occupee[newX][newY] = 0;
			newY++;
			occupee[newX][newY] = 1;
			voiture->etat = 'm';
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
		} else { //Position de devant est occupee
			if (occupee[newX][newY + 1] == 1) { // Dans le cas du feux rouge
				voiture->etat = 's';
			} else if (occupee[newX][newY + 1] == 2) { // Dans le cas d'une voiture devant est en panne
				eviter = 1;
			}
		}
	} else {
		occupee[newX][newY] = 0;
		newX = -1;
		newY = -1;
		voiture->temps = TEMPS_ATTENTE;
		voiture->etat = 'h';
	}
	if (!eviter) {
		voiture->posx = newX;
		voiture->posy = newY;
	} else {
		eviterPanne(voiture, occupee, taille, matrice);
	}

	voiture->direction = 'r';
}
//Deplacement vers la gauche
void AllerAGauche(VOITURE* voiture, char** occupee, MAPTAILLE taille, int** matrice) {
	int newX = voiture->posx, newY = voiture->posy;
	char eviter = 0;
	if (newY > 0) {
		if (!occupee[newX][newY - 1]) {
			occupee[newX][newY] = 0;
			newY--;
			occupee[newX][newY] = 1;
			voiture->etat = 'm';
			if (voiture->entree != NULL) {
				voiture->entree->occupee = 0;
				voiture->entree = NULL;
			}
		} else { // Si la posistion devant est occupee
			if (occupee[newX][newY - 1] == 1) { // Dans le cas du feux rouge
				voiture->etat = 's';
			} else if (occupee[newX][newY - 1] == 2) { // Dans le cas d'une voiture devant est en panne
				eviter = 1;
			}
		}
	} else {
		occupee[newX][newY] = 0;
		newX = -1;
		newY = -1;
		voiture->temps = TEMPS_ATTENTE;
		voiture->etat = 'h';
	}
	if (!eviter) {
		voiture->posx = newX;
		voiture->posy = newY;
	} else {
		eviterPanne(voiture, occupee, taille, matrice);
	}
	voiture->direction = 'l';
}

//Permet de faire avancer la voiture
void avancerVoiture(VOITURE* voiture, int direction, char** occupee, MAPTAILLE taille, int** matrice) {
	int posx = voiture->posx, posy = voiture->posy;
	if (matrice[posx][posy] == 'S'){
		occupee[posx][posy] = 0;
		voiture->posx = -1;
		voiture->posy = -1;
		voiture->temps = TEMPS_ATTENTE;
		voiture->etat = 'h';
		return;
	}
  //permet de faire le changement de direction s'il arrive sur un point critique
  //ou de deplacer normalement vers le bas ou vers le haut
	switch (direction) {
	case 'd':
		AllerEnBas(voiture, occupee, taille, matrice);
		break;
	case 'u':
		AllerEnHaut(voiture, occupee, taille, matrice);
		break;
	case 'l':
		AllerAGauche(voiture, occupee, taille, matrice);
		break;
	case 'r':
		AllerADroite(voiture, occupee, taille, matrice);
		break;
	case 'k':
		if (nbAleatoire(2)) {
			AllerEnBas(voiture, occupee, taille, matrice);
		} else {
			AllerADroite(voiture, occupee, taille, matrice);
		}
		break;
	case 'h':
		if (nbAleatoire(2)) {
			AllerEnBas(voiture, occupee, taille, matrice);
		} else {
			AllerAGauche(voiture, occupee, taille, matrice);
		}
		break;
	case 'g':
		if (nbAleatoire(2)) {
			AllerEnHaut(voiture, occupee, taille, matrice);
		} else {
			AllerAGauche(voiture, occupee, taille, matrice);
		}
		break;
	case 'i':
		if (nbAleatoire(2)) {
			AllerEnHaut(voiture, occupee, taille, matrice);
		} else {
			AllerADroite(voiture, occupee, taille, matrice);
		}
		break;
	case ' ':
		avancerVoiture(voiture, voiture->direction, occupee, taille, matrice);
		break;
	}
}

//Changer l'état des feux
void changeFeuxEtat(FEUX* feux, char** occupee, MAPTAILLE taille, char bloquee, char etat) {
	feux->etat = etat;
	int i, j, k;
	switch (feux->direction) {
	case 'u':
		i = -1;
		j = 0;
		break;
	case 'd':
		i = 1;
		j = 0;
		break;
	case 'l':
		i = 0;
		j = -1;
		break;
	case 'r':
		i = 0;
		j = 1;
		break;
	}
	int tx = feux->x + i, ty = feux->y;
	for (k = 0; k < feux->portee; k++) {
		if (tx > 0 && tx < taille.hauteur && ty > 0 && ty < taille.largeur) {
			occupee[tx][ty] = bloquee;
		}
		tx += i;
		ty += j;
	}
}

//deplacement de toute les voitures
void deplacementVoiture(VOITURE* voitures, CALCUL_POINT_ALEATOIRE* listeEntrees, int** matrice, char** occupee, MAPTAILLE taille, int mode) {
	VOITURE* voiture = voitures;
	while (voiture != NULL) {
		if (voiture->posx >= 0 && voiture->posy >= 0) {
			int direction = matrice[voiture->posx][voiture->posy];
			if (voiture->etat != 'p') {
				if (Panne() && (mode == 2 || mode == 4)) {
					voiture->etat = 'p';
					occupee[voiture->posx][voiture->posy] = 2;
					voiture->tempsPanne = PANNE_DUREE;
				} else {
					avancerVoiture(voiture, direction, occupee, taille, matrice);
				}
			} else {
				voiture->tempsPanne--;
				if (voiture->tempsPanne == 0) {
					voiture->etat = 'm';
					occupee[voiture->posx][voiture->posy] = 1;
				}
			}
		} else {
			//Cette voiture est hors de plan. Rentrer le aleatoirement
			PositionAleatoire(voiture, listeEntrees, occupee);
		}
		voiture = voiture->next;
	}
}

//Feux vert
void feuxVert(FEUX* feux, char** occupee, MAPTAILLE taille) {
	changeFeuxEtat(feux, occupee, taille, 0, 'b');
}

//Feux rouge
void feuxRouge(FEUX* feux, char** occupee, MAPTAILLE taille) {
	changeFeuxEtat(feux, occupee, taille, 1, 'r');
}

//Controle des feux avec un compteur qui s'incremente pour le changement de couleur du feux
void activerFeux(FEUX* feux, char** occupee, MAPTAILLE taille) {
	FEUX* cour = feux;
	while (cour != NULL) {
		if (cour->compteur == FEUX_DUREE) {
			if (cour->etat == 'b') {
				feuxRouge(cour, occupee, taille);
			} else if (cour->etat == 'r') {
				feuxVert(cour, occupee, taille);
			}
			cour->compteur = 0;
		} else if (cour->compteur > FEUX_DUREE) {
			cour->compteur = 0;
		} else {
			cour->compteur++;
		}

		cour = cour->next;
	}
}


//Creer la listes des voitures
VOITURE* CreerListeVoiture(int nombreVoitures, CALCUL_POINT_ALEATOIRE* listeEntrees, char** occupee) {
	int i;
	VOITURE* tete = NULL;
	VOITURE* cour = NULL;
	for (i = 0; i < nombreVoitures; i++) {
		if (tete == NULL) {
			tete = malloc(sizeof(VOITURE));
			cour = tete;
		} else {
			cour->next = malloc(sizeof(VOITURE));
			cour = cour->next;
		}
		cour->temps = 0;
		cour->etat = 'm';
		PositionAleatoire(cour, listeEntrees, occupee);
		cour->next = NULL;
	}
	return tete;
}

//Calcul des entrees du tram
CHEMIN* TramEntree(int** matrice, MAPTAILLE taille) {
	int i, j;
	POINT* entrees = malloc(2 * sizeof(POINT));
	POINT* sorties = malloc(2 * sizeof(POINT));
	int c1=0, c2=0;
	for (i=0; i<taille.hauteur; i++){
		for (j=0; j<taille.largeur; j++){
			if (matrice[i][j] == 'Q' || matrice[i][j] == 'A'){
				entrees[c1].x = i;
				entrees[c1].y = j;
				entrees[c1].direction = (matrice[i][j] == 'Q'?'d':'u');
				entrees[c1].next = NULL;
				c1++;
			}

			if (matrice[i][j] == 's'){
				sorties[c2].x = i;
				sorties[c2].y = j;
				sorties[c2].next = NULL;
				c2++;
			}
		}
	}
	CHEMIN* chemin = malloc(sizeof(CHEMIN));
	CHEMIN* cour = chemin;
	cour->next = malloc(sizeof(CHEMIN));
	cour->next->next = NULL;
	cour->entree = entrees;
	cour->next->entree = entrees + 1;

	if (entrees[0].y == sorties[0].y){
		cour->sortie = sorties;
		cour->next->sortie = sorties + 1;
	} else {
		cour->sortie = sorties + 1;
		cour->next->sortie = sorties;
	}

	return chemin;
}

//Creer liste des trams
TRAM* CreerTram(int** matrice, MAPTAILLE taille) {
	CHEMIN* chemin = TramEntree(matrice, taille);
	TRAM* tete = NULL;
	TRAM* cour = NULL;

	while (chemin != NULL){
		if (tete == NULL){
			tete = malloc(sizeof(TRAM));
			cour = tete;
		} else {
			cour->next = malloc(sizeof(TRAM));
			cour = cour->next;
		}
		cour->direction = chemin->entree->direction;
		cour->posx = chemin->entree->x;
		cour->posy = chemin->entree->y;
		cour->entree = chemin->entree;
		cour->sortie = chemin->sortie;
		cour->longeur = 3;
		cour->stopTime = 0;
		cour->etat = 'm';
		cour->temps = 0;
		cour->next = NULL;
		chemin = chemin->next;
	}

	return tete;
}

//Avancer tram si on rencontre la valeur 'a' le tram marque un arret
void avancerTram(TRAM* tram, MAPTAILLE taille, int** matrice){
	while(tram != NULL){
		if (tram->stopTime == 0){
			if (tram->etat == 'm'){
				if (tram->direction == 'd'){
					tram->posx++;
					if (tram->posx - tram->longeur >= tram->sortie->x){
						tram->posx = tram->entree->x - 1;
						tram->temps = TRAM_ATTENTE;
						tram->etat = 'h';
					} else {
						if (checkPortee(tram->posx, 0, taille.hauteur-1) && matrice[tram->posx][tram->posy] == 'a'){
              system("play -q fichier_son/sonnette.wav &");
              tram->stopTime = TRAM_STOP;
						}
					}
				} else if (tram->direction == 'u'){
					tram->posx--;
					if (tram->posx + tram->longeur <= tram->sortie->x){
						tram->posx = tram->entree->x + 1;
						tram->temps = TRAM_ATTENTE;
						tram->etat = 'h';
					} else {
						//Train stop for a while
						if (checkPortee(tram->posx, 0, taille.hauteur-1) && matrice[tram->posx][tram->posy] == 'a'){
							system("play -q fichier_son/sonnette.wav &");
							tram->stopTime = TRAM_STOP;
						}
					}
				}
			} else {
				tram->temps--;
				if (tram->temps == 0){
					tram->etat = 'm';
				}
			}
		} else {
			tram->stopTime--;
		}

		tram = tram->next;
	}
}

//Creation de l'avion
AVION* CreerAvion(int** matrice, MAPTAILLE taille) {
	AVION* avion = NULL;
	int i, j;
	for (i=0; i<taille.hauteur; i++){
		for (j=0; j<taille.largeur; j++){
			if (matrice[i][j] == 't'){
				avion = malloc(sizeof(AVION));
				avion->x = i;
				avion->y = j;
				avion->temp = 0;
				avion->hauteur = 11;
				avion->largeur = 2;
				break;
			}
		}
		if (avion != NULL){
			break;
		}
	}
	return avion;
}

//Deplacement de l'avion de gauche vers la droite
void deplacementAvion(AVION* avion, MAPTAILLE taille){
	if (avion->temp > 0){
		avion->temp--;
	} else {
		if (avion->y - avion->largeur >= taille.largeur - 1){
			avion->y = -2;
			avion->temp = 10;
		} else {
			avion->y += 2;
		}
	}
}
