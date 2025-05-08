#include "fichier.h"
//Affiche une ligne line du tetromino t
void display_tetromino(Tetromino *t, int line){
    if (t==NULL){
        printf("ERREUR de pointeur dans Draw !!!\n");
        exit(70);
    }
    int bloc_placed = 0;
    int dx = 2 - t->blocs[0][0]; //Distance x entre le centre du tetromino et la case (2,2), qui est le centre d'un tableau 5*5
    int dy = 2 - t->blocs[0][1]; //Distance y...
    printf("▦      ▦ ");
    for (int i = 0; i<DIM; i++){
        for (int j=0; j<t->nb_blocs;j++){
            if(t->blocs[j][0]+dx == line && t->blocs[j][1]+dy == i){
                bloc_placed = 1;
            }
        }
        if(bloc_placed){
            printf("# ");
        }else{
            printf("  ");
        }
        bloc_placed = 0;
    }
    printf("|\n");
}

//Affiche dans le terminal la grille avec les tetrominos
void display(char tab[LINE][COL], Joueur* J, Tetromino *t, int s){
    if (t==NULL || J==NULL){
        printf("ERREUR de pointeur dans Draw !!!\n");
        exit(71);
    }
    for (int i = 0; i<LINE; i++){
        printf("      ▦ ");
        for (int j = 0; j<COL; j++){
            printf("%c ",tab[i][j]);
        }
        
        if (i == 2){
            printf("▦      Pseudo : %s\n",J->pseudo);
        }else if(i==3){
            printf("▦      Difficulté : %d\n",J->difficulte);
        }else if(i==4){
            printf("▦      Score : %d\n",J->score);
        }else if (LINE >12 && i>5 && i<=12 && s){
            if (i==6){
                printf("▦      *************\n");
            }else if(i>6 && i<=11){
                display_tetromino(t,i-7);
            }else if(i==12){
                printf("▦      *************\n");
            }
        }else {
            printf("▦\n");
        }
    }
    printf("      ***********************\n");
    
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
            	if (tab[i][j] <8){
                       tab[i][j] = 0;
                       }
            
        }
        
    }
}

//Modifie la grille de caractère en fonction du tableau d'entiers (un # si on a un 1, un espace sinon) 
//*pourra être changée si on veut des pièces d'apparence différente
void draw(int tab[LINE][COL], char grille[LINE][COL]){
    for (int i = 0; i<LINE; i++){
        for (int j = 0; j<COL; j++){
                if(tab[i][j]==0){
                grille[i][j]=" ";
            }
            else{
                if (tab[i][j] <0 || tab[i][j]>14 || tab==NULL){
                    printf("Erreur de saisie.\n");
                    exit(10); 
                } 
                switch(tab[i][j]%7+1){
                    case 1:
                        grille[i][j]="🟥";
                        break;
                    case 2:
                        grille[i][j]="🟧";
                        break;
                    case 3:
                        grille[i][j]="🟨";
                        break;
                    case 4:
                        grille[i][j]="🟩";
                        break;
                    case 5:
                        grille[i][j]="🟫";
                        break;
                    case 6:
                        grille[i][j]="🟪";
                        break;
                    case 7:
                        grille[i][j]="🟦";
                        break;
                }
            }
        }
    }

}

//Permet de rassembler toutes les fonctions qui modifie le terminal en une seule
void refresh(char grille[LINE][COL], int tab[LINE][COL], Joueur* J,Tetromino *t, int s){
    if (t==NULL || J==NULL){
        printf("ERREUR de pointeur dans Draw !!!\n");
        exit(72);
    }
    system("clear");
    clear(tab);
    display(grille,J,t,s);
}
