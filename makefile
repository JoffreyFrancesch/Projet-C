all: EXEC LANCEMENT MRPROPRE

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
