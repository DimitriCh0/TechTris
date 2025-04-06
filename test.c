#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COL 10
#define LINE 10

typedef struct{
    int x;
    int y;
}Vecteur;

typedef struct{
    int blocs[5][2];
    int isalive;

}Tetromino;


Tetromino tetrominoConstructor(char tab[5][5]){
    Tetromino t;
    int n = 0;
    if (tab[2][2]==' '){
        exit(1);
    }
    for (int i = 0; i<5; i++){
        for (int j = 0; j<5; j++){
            if (tab[i][j]=='#'){
                t.blocs[n][0] = i;
                t.blocs[n][1] = j;
                n++;
            }
        }
    }
    t.isalive = 1;
    return t;
}

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

int move_t(Tetromino *t,Vecteur v){
    for (int j = 0; j<5; j++){
        if(t->blocs[j][0]>=9){
            t->isalive = 0;
           
            return 1;
        }
    }
    for (int i = 0; i<5; i++){
        if (t->isalive == 1 && t->blocs[i][0]<9 && t->blocs[i][1]<9){
            t->blocs[i][0] =  t->blocs[i][0] + v.x;
            t->blocs[i][1] =  t->blocs[i][1] + v.y;
        }
    }
    return 0;

}

void place_t(Tetromino *t,int tab[LINE][COL]){
    if (t->isalive){
        for (int i = 0; i<5; i++){
            
            tab[t->blocs[i][0]][t->blocs[i][1]] = 1;
        
                
            
        }

    }else{
        for (int j = 0; j<5; j++){
            tab[t->blocs[j][0]][t->blocs[j][1]] = 2;
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



int main(){
    int tab_principal[LINE][COL] = {0};
    char grille[LINE][COL];

    char truc[5][5] = 
   {"     ",
    "  #  ",
    " ### ",
    "  #  ",
    "     "};

    Tetromino test = tetrominoConstructor(truc);
   /* for (int j = 0; j<5; j++){
        printf("x=%d y=%d\n",test.blocs[j][0],test.blocs[j][1]);
    }*/

    Vecteur v;
    v.x = 1;
    v.y = 0;
    int temp;
    printf("*******************\n");
    system("clear");
    for (int i = 0; i<10; i++){
        temp = move_t(&test,v);
        if (temp){
            return 0;
        }
        place_t(&test,tab_principal);
        draw(tab_principal,grille);
        display(grille);
        printf("*******************\n");
        sleep(1);
        clear(tab_principal);
        system("clear");
    }
    
    return 0;
}
