#include "fichier.h"

//Affiche dans le terminal la grille avec les tetrominos
void display(char tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            printf("%c ",tab[i][j]);
        }
        printf("\n");
    }
}
//Affiche dans le terminal un double tableau d'entiers
void display_int(int tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
}
//Remet à 0 tous les entiers de la grille d'entiers afin de pouvoir le modifier avec la fonction "place_t"
void clear(int tab[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
            
                tab[i][j] = 0;
            
        }
        
    }
}

//Modifie la grille de caractère en fonction du tableau d'entiers (un # si on a un 1, un espace sinon) 
//*pourra être changée si on veut des pièces d'apparence différente
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