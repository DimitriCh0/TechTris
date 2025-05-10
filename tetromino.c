#include "fichier.h"

//Construit une structure Tetromino à partir d'un double tableau de caractère représentant le dessin du tetromino
//Elle remplit le tableau "blocs" avec les coordonnées de chaque bloc (représenté par un 1)
//Le premier élément du tableau blocs contient toujours les coordonnées du bloc central (2,2)
//Si le programme détecte que la pièce dessinée ne contient pas de bloc central (si la case (2,2) est un 0), celui-ci renvoie une erreur et s'arrête 
void tetrominoConstructor(char **tab, Tetromino *t){
   if (t==NULL){
        printf("Erreur de pointeur dans tetromino !\n");
        exit(50);
   }
    int n = 1;
    if (tab[2][2]=='0'){
    	printf("Pas de Bloc central dans la pièce !!!\n");
        exit(50);
    }
    t->blocs[0][0] = 2;
    t->blocs[0][1] = 2+COL/2-2;
    for (int i = 0; i<DIM; i++){
        for (int j = 0; j<DIM; j++){
            if (tab[i][j]=='1'&&(i!=2 || j!=2)){
                t->blocs[n][0] = i;
                t->blocs[n][1] = j+COL/2-2;
                n++;
            }
        }
    }
    t->nb_blocs = n;
    t->isalive = 1;
    
    
}

//Renvoie 1 si le Tetromino ne touche pas la bordure gauche
int isNotBorderL(Tetromino *t,int n){
	if (t==NULL){
        printf("Erreur de pointeur dans tetromino !\n");
        exit(51);
	}
	for (int i = 0; i<n; i++){
        	if (t->blocs[i][1] == 0){
        		return 0;
        	}
	}
	return 1;

}
//Renvoie 1 si le Tetromino ne touche pas la bordure droite
int isNotBorderR(Tetromino *t, int n){
	if (t==NULL){
        printf("Erreur de pointeur dans tetromino !\n");
        exit(52);
	}
	for (int i = 0; i<n; i++){
        	if (t->blocs[i][1] == COL-1){
        		return 0;
        	}
	}
	return 1;

}
//Renvoie 1 si le tetromino est toujours "en vie"
//Cette fonction, contrairement aux deux précédentes ne va pas vérifier directement les coordonnées du Tétromino mais vérifie si celui-ci, avec le déplacement du vecteur, ne touche pas le sol ou
//s'il ne touche pas un tétromino déjà "mort" représenté par des 2 dans le tableau principal 
int stillAlive(Tetromino *t, Vecteur v, int tab[LINE][COL],int n){
	if (t == NULL || tab == NULL){
		printf("Erreur de pointeur dans tetromino !\n");
        	exit(53);
    	}
    	if (v.x == 0){
    		for (int i=0; i<n; i++){
    			if (tab[t->blocs[i][0]][t->blocs[i][1]+v.y]>=8){
    				return 0;
    			}
    		}
    
    	}
    	else {
    		for (int i=0; i<n; i++){
    			if(t->blocs[i][0]+v.x==LINE || tab[t->blocs[i][0]+v.x][t->blocs[i][1]]>=8){
    				t->isalive = 0;
    				return 0;
    			}	
    		}
    	}
    	return 1;
}



//Applique un déplacement sur tous les blocs du Tetromino avec un vecteur
void move_t(Tetromino *t,Vecteur v, int n){
    if (t==NULL){
        printf("Erreur de pointeur dans tetromino !\n");
        exit(54);
   }
    for (int i =0; i<n;i++){
        t->blocs[i][0]+= v.x;
        t->blocs[i][1]+= v.y;
    }
}




//Place le Tetromino dans le tableau principal à l'aide des coordonnées contenues dans le double tableau "blocs"
void place_t(Tetromino *t,int tab[LINE][COL],Vecteur v, int n, int color){
    	if (t==NULL){
		printf("Erreur de pointeur dans tetromino !\n");
        	exit(55);
   	}
    	int st = stillAlive(t,v,tab,t->nb_blocs);
    	if (((v.y<=0 && isNotBorderL(t,t->nb_blocs)) || (v.y>=0 && isNotBorderR(t,t->nb_blocs))) && t->isalive && st){
        	move_t(t,v,t->nb_blocs);
    	}
    
    	if (t->isalive){
        	for (int i = 0; i<n; i++){
            		tab[t->blocs[i][0]][t->blocs[i][1]] = color;  
        	}

    	}else{
        	for (int j = 0; j<n; j++){
            		tab[t->blocs[j][0]][t->blocs[j][1]] = color + 7;
        	}
    	}
}

//Permet de remmettre les paramètres de base d'une pièce dans le cadre d'un jeu continu
void reset_piece(Tetromino *t,int n){
    	if (t==NULL){
        	printf("Erreur de pointeur dans tetromino !\n");
        	exit(56);
  	}
    	t->isalive = 1;
    	int dx = 2-t->blocs[0][0]; //distance entre le centre du tetromino et le point (2,2)
	int dy = 2-t->blocs[0][1]; //distance entre le centre du tetromino et le point (2,2)
    	for (int i=0; i<n; i++){
        	t->blocs[i][0]+=dx;
        	t->blocs[i][1]+=dy+COL/2-2;
    	}
}

//Cette procédure supprime une ligne en mettant toutes les valeurs à 0
void clear_line(int tab[LINE][COL], int nb){
    	if (tab==NULL){
        	printf("Erreur de pointeur dans tetromino !\n");
        	exit(57);
   	}
        for (int j = 0; j<COL; j++){
            	tab[nb][j] = 0;
    	}
    
	}

//Fait descendre tous les blocs de tétrominos "mort" d'un nombre correspondant au nombre de lignes que l'on a supprimées
void gravitation(int tab[LINE][COL], int d, int start){
    	int temp;
    	if (tab==NULL){
        	printf("Erreur de pointeur dans tetromino !\n");
        	exit(58);
   	}
    	if(d!=0){
    		for (int i=start; i>=0; i--){
        		for (int j=0; j<COL; j++){
            			temp = tab[i][j];
            			if (temp>=8){
                			tab[i][j] = 0;
                			tab[i+d][j] = temp;
            			}
        		}
    		}
    	}
}
//Arrête le jeux si les blocs ont atteint le haut de la grille 
int game_over(int tab[LINE][COL], Tetromino *t, int n){
    	if (tab==NULL || t == NULL){
        	printf("Erreur de pointeur dans tetromino !\n");
        	exit(59);
   	}
    	for (int i = 0; i<n;i++){
       		if (tab[t->blocs[i][0]][t->blocs[i][1]] >=8 && t->blocs[i][0]<4){
            		return 1;
       		}
    	}
    	return 0;
}

//Affiche les coordonnées des blocs du Tétromino pour les tests
void showCoordonnates(Tetromino *t, int n){
    	for (int i=0; i<n; i++)
    	{
        	printf("x = %d, y = %d\n",t->blocs[i][0],t->blocs[i][1]);
    	}
    	printf("\n");
}
