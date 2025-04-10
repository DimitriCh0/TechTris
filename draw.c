#include "fichier.h"


void display(char tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            printf("%c ",tab[i][j]);
        }
        printf("\n");
    }
}
void display_int(int tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
}
void clear(int tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            
                tab[i][j] = 0;
            
        }
        
    }
}

void draw(int tab[LINE][COL], char grille[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            if (tab[i][j] == 1 || tab[i][j]==2){
                    grille[i][j] = '#';
            }else{
                grille[i][j] = ' ';
            }
        }
    }
}