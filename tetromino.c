#include "fichier.h"

//Construit une structure Tetromino à partir d'un double tableau de caractère représentant le dessin du tetromino
Tetromino tetrominoConstructor(char tab[DIM][DIM]){
    Tetromino t;
    int n = 1;
    if (tab[2][2]==' '){
        exit(1);
    }
    t.blocs[0][0] = 2;
    t.blocs[0][1] = 2;
    for (int i = 0; i<DIM; i++){
        for (int j = 0; j<DIM; j++){
            if (tab[i][j]=='#'&&(i!=2 || j!=2)){
                t.blocs[n][0] = i;
                t.blocs[n][1] = j;
                n++;
            }
        }
    }
    t.isalive = 1;
    return t;
}

//Renvoie 1 si le Tetromino ne touche pas la bordure gauche
int isNotBorderL(Tetromino *t){
	for (int i = 0; i<DIM; i++){
        	if (t->blocs[i][1] == 0){
        		return 0;
        	}
    }
    return 1;

}
//Renvoie 1 si le Tetromino ne touche pas la bordure droite
int isNotBorderR(Tetromino *t){
	for (int i = 0; i<DIM; i++){
        	if (t->blocs[i][1] == 9){
        		return 0;
        	}
    }
    return 1;

}
//renvoie 1 si le tetromino est toujours "en vie"
int stillAlive(Tetromino *t, Vecteur v, int tab[LINE][COL]){
    if (t == NULL || tab == NULL){
        exit(1);
    }
    for (int i=0; i<DIM; i++){
        if (t->blocs[i][0]+v.x==10 || tab[t->blocs[i][0]+v.x][t->blocs[i][1]+v.y]==2){
            t->isalive =0;
            return 0;
        }
    }
    return 1;
}



//Applique un déplacement sur tous les blocs du Tetromino avec un vecteur
int move_t(Tetromino *t,Vecteur v){
    for (int i =0; i<DIM;i++){
        t->blocs[i][0]+= v.x;
        t->blocs[i][1]+= v.y;
    }
    return 0;

}




//Place le Tetromino dans le tableau principal
void place_t(Tetromino *t,int tab[LINE][COL],Vecteur v){
    stillAlive(t,v,tab);
    if (((v.y<=0 && isNotBorderL(t)) || (v.y>=0 && isNotBorderR(t))) && t->isalive){
        move_t(t,v);
    }
    
    if (t->isalive){
        for (int i = 0; i<DIM; i++){
            
            tab[t->blocs[i][0]][t->blocs[i][1]] = 1;
        
                
            
        }

    }else{
        for (int j = 0; j<DIM; j++){
            tab[t->blocs[j][0]][t->blocs[j][1]] = 2;
        }
    }
    
}

//Affiche les coordonnées du Tétromino
void showCoordonnates(Tetromino *t){
    for (int i=0; i<DIM; i++)
    {
        printf("x = %d, y = %d\n",t->blocs[i][0],t->blocs[i][1]);
    }
    printf("\n");
}