#include <errno.h>
#include "structs.h"
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
#define LINE 20
#define UTF 8

#define BLOC_MAX 5
#define NUM_CASE DIM*DIM



//Fonctions et procédures
//Jeu
void jeu_tetris(Joueur* J, int tab_principal[LINE][COL],int sauvegarde);
//Tétrominos
void creation_tetrominos(Tetromino *t);
void tetrominoConstructor(char **tab, Tetromino *t);
int move_t(Tetromino *t,Vecteur v,int n);
void place_t(Tetromino *t,int tab[LINE][COL],Vecteur v, int n, int color);
int stillAlive(Tetromino *t, Vecteur v, int tab[LINE][COL], int n);
int isNotBorderR(Tetromino *t, int n);
int isNotBorderL(Tetromino *t, int n);
void reset_piece(Tetromino *t, int n);
//Fonctions du jeu
void sleep_ms(float milliseconds);
void clear_line(int tab[LINE][COL], int nb);
void gravitation(int tab[LINE][COL], int d, int start);
int game_over(int tab[LINE][COL], Tetromino *t, int n);
//Inputs
int get_input();
int key_input();
Vecteur keyToVect(int r);
//Draw
void display(char grille[LINE][COL][UTF], Joueur* J, Tetromino *t, int s);
void display_int(int tab[LINE][COL]);
void clear(int tab[LINE][COL]);
void draw(int tab[LINE][COL], char grille[LINE][COL][UTF]);
void refresh(char grille[LINE][COL][UTF], int tab[LINE][COL], Joueur* J, Tetromino *t, int s);
//Rotation et pièces
void rotation(int rotation, Tetromino *t, int n, int tab[LINE][COL]);
void affichepiece(char **piece);
//Création des pièces
char*** pieces(); // Création de tableau

void lecture(char*** liste_pieces, int var); // Remplissage de tableau
void liberer_pieces(char*** liste_pieces); // Libération de mémoire
void afficheliste(char ***liste_pieces); 
void affichepiece(char **piece);
int scoreGrille(int *tab);

//sauvegarde
void enregistrement_partie(int tab[LINE][COL], Joueur* J);

//pause
int pause();

//Scoreboard
Joueur constru();
void lire_scoreboard(FILE *f);
void enregistrement_score(Joueur* J);

//Atelier
void atelier();
char*** pieces_vide();
void enregistrement(char*** pieces_dessinees);
void menu_enregistrement(char*** pieces_dessinees);
int menu_defaut(char *** pieces_dessinees);


//Conditions de dessin de pièces
int voisin(char*** pieces_dessinees, int piece, int selected);
void lie_centre(char*** pieces_dessinees, int piece, int x, int y, int deja_verif[DIM][DIM]);
int correction(char *** pieces_dessinees, int piece);


//Selection colorée
void print_tab(char ligne, int highlight);
void print_colored(const char *text, int highlight);
void print_colored2(const char *text, int highlight);

int get_input();


void wait_for_enter();
//Menu
void display_menu();

//Sous-menu

void tetris();
void lecture_sauvegarde(FILE *fichier, char tab_char[LINE][COL+1], int tab_int[LINE][COL], Joueur* Joueur);
void sauvegarde();
void scoreboard();
void dessin(); //Atelier
void avantdessin();//Atelier
void affichagepieces();





