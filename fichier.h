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

#define BLOC_MAX 5
#define NUM_CASE DIM*DIM


char*** pieces();
char*** lecture(char*** liste_pieces, int var);
void enregistrement(char*** pieces_dessinees);
void menu_enregistrement(char*** pieces_dessinees);
void liberer_pieces(char*** liste_pieces);
void print_tab(char ligne, int highlight);
void print_colored2(const char *text, int highlight);
char*** pieces_vide();
int voisin(char*** pieces_dessinees, int piece, int selected);
void lie_centre(char*** pieces_dessinees, int piece, int x, int y, int deja_verif[DIM][DIM]);
int correction(char *** pieces_dessinees, int piece);
void afficheliste(char ***liste_pieces);
void affichepiece(char **piece);

void print_colored(const char *text, int highlight);
int get_input();

void atelier();

void wait_for_enter();
void tetris();
void scoreboard();
void dessin();
void avantdessin();
void affichagepieces();


