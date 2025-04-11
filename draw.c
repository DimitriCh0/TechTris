#include "fichier.h"

//dessine dans le terminal la grille avec les tetrominos
void display(char tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            printf("%c ",tab[i][j]);
        }
        printf("\n");
    }
}
//dessine un double tableau d'entiers
void display_int(int tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
}
//remet à 0 tous les entiers de la grille d'entiers
void clear(int tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            
                tab[i][j] = 0;
            
        }
        
    }
}

//modifie la grille de caractère en fonction du tableau d'entiers
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