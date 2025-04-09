
#include "structs.h"
#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#define COL 10
#define LINE 10
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

Tetromino tetrominoConstructor(char tab[5][5]);
int move_t(Tetromino *t,Vecteur v);
void place_t(Tetromino *t,int tab[LINE][COL]);
void prepareScene(void);
void initSDL(void);
void doInput(void);
void presentScene(void);









