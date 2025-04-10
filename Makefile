#Programme à créer
PROG = projet


#Sources
SRC = main.c input.c tetromino.c draw.c

#Règle par défaut : compile et exécute
all: $(PROG)
	./$(PROG)

#Compilation du programme
$(PROG): $(SRC) fichier.h
	
	gcc -Wall -o $(PROG) $(SRC) -lSDL2main -lSDL2

#Nettoyage
clean:
	rm -f $(PROG)