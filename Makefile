#Programme à créer
PROG = projet


#Sources
SRC = main.c input.c tetromino.c

#Règle par défaut : compile et exécute
all: $(PROG)
	./$(PROG)

#Compilation du programme
$(PROG): $(SRC) fichier.h
	sudo apt-get install libsdl2-2.0-0
	sudo apt-get install libsdl2-dev
	gcc -Wall -o $(PROG) $(SRC)

#Nettoyage
clean:
	rm -f $(PROG)
