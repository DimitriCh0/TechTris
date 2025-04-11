#include <errno.h>
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NOMBRE_PIECES 7
#define DIM 5
#define COL 10
#define LINE 10


Tetromino tetrominoConstructor(char tab[5][5]);
int move_t(Tetromino *t,Vecteur v);
void place_t(Tetromino *t,int tab[LINE][COL],Vecteur v);
int stillAlive(Tetromino *t, Vecteur v, int tab[LINE][COL]);
int key_input();
Vecteur keyToVect(int r);
void display(char tab[LINE][COL]);
void display_int(int tab[LINE][COL]);
void clear(int tab[LINE][COL]);
void draw(int tab[LINE][COL], char grille[LINE][COL]);
int isNotBorderR(Tetromino *t);
int isNotBorder(Tetromino *t);
void rotation(int rotation, Tetromino *t);
char*** pieces();






