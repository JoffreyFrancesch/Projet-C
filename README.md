# Projet C ESIEA 3A 2017

Sujet
-----
L’objectif de ce projet est de programmer en langage C, un simulateur dynamique de circulation
urbaine. Le projet est à réaliser obligatoirement en binôme (ancien & nouveau) sous environnement
GNU/Linux. La simulation du trafic doit se faire comme dans la vraie vie. L’affichage doit
être effectué uniquement sur console.

Structure du projet
-------------------

* **Fichier TXT**
  * map.txt --> carte de l'aéroport
  * map_cp.txt --> copie de la carte sans déco pour accéder au coordonnées réelle

* **Fichier .H**
  * load_map.h
  * menu.h
  * vehicules.h

* **Fichier .C**
  * load_map.c --> charge la carte dans le terminal
  * menu.c --> charge le menu dans le terminal
  * vehicules.c --> effectue la simulation
  * main.c --> lancement de tout les codes

* **Zone de test**
  * test.c --> fichier de test
  * lancement_rapide.sh --> compile et lance rapidement

* **MakeFile**
* **README.md**
* **EXEC**

TODO
----
- [x] Menu de sélection
- [x] Affichage de la map
- [ ] Ajout de décoration à la map
- [x] Tram
- [ ] Avion
- [ ] Voiture
- [ ] Parking
- [ ] Piétons
- [x] Feu
