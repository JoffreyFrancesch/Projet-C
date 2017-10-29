# Projet C ESIEA 3A 2017

Sujet
-----
L’objectif de ce projet est de programmer en langage C, un simulateur dynamique de circulation
urbaine. Le projet est à réaliser obligatoirement en binôme (ancien & nouveau) sous environnement
GNU/Linux. La simulation du trafic doit se faire comme dans la vraie vie. L’affichage doit
être effectué uniquement sur console.

Informations sur la compilation
-------------------------------

Pour lancer le projet complet tapez :

<p>Voici un code en C :</p>

<pre><code>int main()
{
    printf("Hello world!\n");
    return 0;
}
</code></pre>

Structure du projet
-------------------

* **Fichier TXT**
  * map.txt --> carte de l'aéroport

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

...
