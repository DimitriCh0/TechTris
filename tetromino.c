#include "fichier.h"

//Construit une structure Tetromino à partir d'un double tableau de caractère représentant le dessin du tetromino
//Elle remplit le tableau "blocs" avec les coordonnées de chaque bloc (représenté par un 1)
//Le premier élément du tableau blocs contient toujours les coordonnées du bloc central (2,2)
//Si le programme détecte que la pièce dessinée ne contient pas de bloc central (si la case (2,2) est un 0), celui-ci renvoie une erreur et s'arrête 
Tetromino tetrominoConstructor(char **tab){
    Tetromino t;
    int n = 1;
    if (tab[2][2]=='0'){
        exit(1);
    }
    t.blocs[0][0] = 2;
    t.blocs[0][1] = 2;
    for (int i = 0; i<DIM; i++){
        for (int j = 0; j<DIM; j++){
            if (tab[i][j]=='1'&&(i!=2 || j!=2)){
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
//Renvoie 1 si le tetromino est toujours "en vie"
//Cette fonction, contrairement aux deux précédentes ne va pas vérifier directement les coordonnées du Tétromino mais vérifie si celui-ci, avec le déplacement du vecteur, ne touche pas le sol ou
//s'il ne touche pas un tétromino déjà "mort" représenté par des 2 dans le tableau principal 
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




//Place le Tetromino dans le tableau principal à l'aide des coordonnées contenues dans le double tableau "blocs"
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

//Affiche les coordonnées des blocs du Tétromino pour les tests
void showCoordonnates(Tetromino *t){
    for (int i=0; i<DIM; i++)
    {
        printf("x = %d, y = %d\n",t->blocs[i][0],t->blocs[i][1]);
    }
    printf("\n");
}