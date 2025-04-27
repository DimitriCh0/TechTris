#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

//CONSTANTES
//Le nombre de pièces (Tétrominos)
#define NOMBRE_PIECES 7
//Le nombre fixe de blocs composant chaque pièce
#define DIM 5
//Les dimensions de la grille principale
#define COL 10
#define LINE 10

char*** pieces();
void afficheliste(char ***liste_pieces);
void affichepiece(char **piece);

void print_colored(const char *text, int highlight);
int get_input();

void atelier();


