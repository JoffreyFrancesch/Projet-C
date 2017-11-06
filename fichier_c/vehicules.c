/////FONCTION TRAM GAUCHE
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
/////FONCTION TRAM DE DROITE
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
/////FEU TRICOLORE//////
void feu(int temps_feu){
  switch (temps_feu) {
    case 1:
      printf("\033[1;32m \033[40;45H▀\033[31;152H▀\033[0m");//VERT POUR LES FEUX SUR VOIE PRINCIPALE
      printf("\033[1;31m \033[32;46H▄\033[39;151H▀\033[0m");//ROUGE POUR LES FEUX SUR VOIE PARKING
      break;
    case 10:
      printf("\033[1;33m \033[40;45H▀\033[31;152H▀\033[0m");//ORANGE POUR LES FEUX SUR VOIE PRINCIPALE
      break;
    case 15:
      printf("\033[1;32m \033[40;45H▀\033[31;152H▀\033[0m");//VERT PARKING
      printf("\033[1;33m \033[40;45H▀\033[31;152H▀\033[0m");//ROUGE PRINCIPALE
      break;
    case 20:
      printf("\033[1;33m \033[40;45H▀\033[31;152H▀\033[0m");//ORANGE PARKING
      break;
  }
}
/////FONCTION DE MOUVEMENT
void mouvement(){
  int pos_l1 = 6;
  int pos_l2 = 43;
  int temps_feu = 1;
  while (1) {
    tram1(pos_l1);
    tram2(pos_l2);
    feu(temps_feu);
    temps_feu = temps_feu + 1;
    if (temps_feu == 25) {
      temps_feu = 1;
    }
    pos_l1 = pos_l1+1;
    pos_l2 = pos_l2-1;
    usleep(100000);
    if (pos_l1 == 44 && pos_l2 == 5) {
      pos_l1 =6;
      pos_l2 = 43;
      printf("\033[43;30H \033[6;165H \n");
    }
  }
}
//////////////////////////
