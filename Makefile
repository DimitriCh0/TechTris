#Programme à créer
PROG = projet


#Sources
SRC = main.c input.c tetromino.c draw.c piecesetrotation.c

#Règle par défaut : compile et exécute
all: $(PROG)
	./$(PROG)

#Compilation du programme
$(PROG): $(SRC) fichier.h
	
	gcc -Wall -o $(PROG) $(SRC) -lm

#Nettoyage
clean:
	rm -f $(PROG)