#include <errno.h>
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

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
Tetromino tetrominoConstructor(char tab[5][5]);
int move_t(Tetromino *t,Vecteur v);
void place_t(Tetromino *t,int tab[LINE][COL],Vecteur v);
int stillAlive(Tetromino *t, Vecteur v, int tab[LINE][COL]);
int isNotBorderR(Tetromino *t);
int isNotBorderL(Tetromino *t);
//Inputs
int key_input();
Vecteur keyToVect(int r);
//Draw
void display(char tab[LINE][COL]);
void display_int(int tab[LINE][COL]);
void clear(int tab[LINE][COL]);
void draw(int tab[LINE][COL], char grille[LINE][COL]);
//Rotation et pièces
void rotation(int rotation, Tetromino *t);
char*** pieces();






