#include "fichier.h"

/*Construit une structure Tetromino à partir d'un double tableau de caractère représentant le dessin du tetromino*/
Tetromino tetrominoConstructor(char tab[5][5]){
    Tetromino t;
    int n = 1;
    if (tab[2][2]==' '){
        exit(1);
    }
    t.blocs[0][0] = 2;
    t.blocs[0][1] = 2;
    for (int i = 0; i<5; i++){
        for (int j = 0; j<5; j++){
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

/*Renvoie 1 si le Tetromino touche la bordure gauche*/
int isNotBorderL(Tetromino *t){
	for (int i = 0; i<5; i++){
        	if (t->blocs[i][1] == 0){
        		return 0;
        	}
    }
    return 1;

}
/*Renvoie 1 si le Tetromino touche la bordure gauche*/
int isNotBorderR(Tetromino *t){
	for (int i = 0; i<5; i++){
        	if (t->blocs[i][1] == 9){
        		return 0;
        	}
    }
    return 1;

}
/*Applique un déplacement sur le Tetromino avec un vecteur*/
int move_t(Tetromino *t,Vecteur v){
    for (int j = 0; j<5; j++){
        if(t->blocs[j][0]>=9){
            t->isalive = 0;
           
            return 1;
        }
    }
    for (int i = 0; i<5; i++){
    	if (t->isalive == 1){
    		if (v.y>0 && isNotBorderR(t) && t->blocs[i][0]<9){
    			t->blocs[i][0] =  t->blocs[i][0] + v.x;
            		t->blocs[i][1] =  t->blocs[i][1] + v.y;
    		}
    		if (v.y<0 && isNotBorderL(t) && t->blocs[i][0]<9){
    			t->blocs[i][0] =  t->blocs[i][0] + v.x;
            		t->blocs[i][1] =  t->blocs[i][1] + v.y;
    		}
    	
    	}
    }
    return 0;

}


/*Place le Tetromino dans le tableau principal*/
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