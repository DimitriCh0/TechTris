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
#define LINE 10

//Fonctions et procédures
//Tétrominos
void tetrominoConstructor(char **tab, Tetromino *t);
int move_t(Tetromino *t,Vecteur v);
void place_t(Tetromino *t,int tab[LINE][COL],Vecteur v);
int stillAlive(Tetromino *t, Vecteur v, int tab[LINE][COL]);
int isNotBorderR(Tetromino *t);
int isNotBorderL(Tetromino *t);
void reset_piece(Tetromino *t);
//Fonctions du jeu
void clear_line(int tab[LINE][COL], int nb);
void gravitation(int tab[LINE][COL], int d, int start);
int game_over(int tab[LINE][COL], Tetromino *t);
//Inputs
int get_input();
int key_input();
Vecteur keyToVect(int r);
//Draw
void display(char tab[LINE][COL]);
void display_int(int tab[LINE][COL]);
void clear(int tab[LINE][COL]);
void draw(int tab[LINE][COL], char grille[LINE][COL]);
void refresh(char grille[LINE][COL], int tab[LINE][COL]);
//Rotation et pièces
void rotation(int rotation, Tetromino *t);
void affichepiece(char **piece);
//Création des pièces
char*** pieces();

void print_colored(const char *text, int highlight);
void atelier();

void jeu_tetris();
void display_menu();
void wait_for_enter();






