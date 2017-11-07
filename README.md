# Projet C ESIEA 3A 2017

Sujet
-----
L’objectif de ce projet est de programmer en langage C, un simulateur dynamique de circulation
urbaine. Le projet est à réaliser obligatoirement en binôme (ancien & nouveau) sous environnement
GNU/Linux. La simulation du trafic doit se faire comme dans la vraie vie. L’affichage doit
être effectué uniquement sur console.

Screen du Projet
----------------
* Menu

![MENU](https://github.com/JoffreyFrancesch/Projet-C/blob/master/SCREEN/MENU.png "MENU")
* Simulation

![SIMU](https://github.com/JoffreyFrancesch/Projet-C/blob/master/SCREEN/SIMU.png "SIMU")

Installation du projet
----------------------

* Pour installer le projet complet il faut entrer dans un terminal munis de git la commande :
  <pre><code>git clone https://github.com/JoffreyFrancesch/Projet-C</code></pre>

* Pour lancer le projet tapez dans le terminal :
  <pre><code>make</code></pre>

* Si vous n'avez pas git veuillez l'installer avec ceci -> [Télécharger GIT](https://git-scm.com/downloads)

Information sur la compilation du projet
----------------------------------------

Le projet compile simplement grâce au MakeFile
<pre><code>all: EXEC LANCEMENT MRPROPRE

load_map.o : fichier_c/load_map.c fichier_h/load_map.h
  gcc -c fichier_c/load_map.c -Wall

menu.o : fichier_c/menu.c fichier_h/menu.h
  gcc -c fichier_c/menu.c -Wall

vehicules.o : fichier_c/vehicules.c fichier_h/vehicules.h
  gcc -c fichier_c/vehicules.c -Wall

main.o : fichier_c/main.c fichier_h/menu.h fichier_h/load_map.h fichier_h/vehicules.h
  gcc -c fichier_c/main.c -Wall

EXEC : main.o load_map.o menu.o vehicules.o
  gcc -o EXEC main.o load_map.o menu.o vehicules.o -Wall

LANCEMENT :
  ./EXEC

MRPROPRE :
  rm *.o
  rm EXEC
  clear</code></pre>

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

* **SREEN**
  * MENU.png
  * SIMU.png


TODO
----
- [x] Menu de sélection
- [x] Affichage de la map
- [x] Ajout de décoration à la map
- [x] Tram
- [ ] Avion
- [ ] Voiture
- [ ] Parking
- [ ] Piétons
- [x] Feu
