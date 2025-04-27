#Programme à créer
PROG = projet


#Sources
SRC = menu.c atelier.c scoreboard.c main.c

#Règle par défaut : compile et exécute
all: $(PROG)
	./$(PROG)

#Compilation du programme
$(PROG): $(SRC) fichier.h
	
	gcc -Wall -o $(PROG) $(SRC) -lm

#Nettoyage
clean:
	rm -f $(PROG)
