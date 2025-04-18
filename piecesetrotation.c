#include "fichier.h"

//une pièce est définie comme : '1' = bloc et '0' = vide

char*** pieces(){
	char*** liste_pieces = NULL;
	liste_pieces = malloc(NOMBRE_PIECES*sizeof(char**)); 		//Créer le tableau qui contiendra chaque pièce (une pièce étant un tableau a 2 dimensions)
	if (liste_pieces == NULL){
		exit(10);
	}
	for (int i = 0;i<NOMBRE_PIECES;i++){
		*(liste_pieces+i) = malloc(DIM*sizeof(char*)); 		//Créer les tableaux qui contiendront les chaines de caractères correspondant à chaque ligne qui forme une pièce (5 lignes)
		if (*(liste_pieces+i) == NULL){
			exit(10);
		}
		for (int j = 0; j<DIM;j++){
			*(*(liste_pieces+i)+j) = malloc((DIM+1)*sizeof(char)); 		//Créer les chaines de caractères qui contiendront les pièces ligne par ligne + (DIM+1) pour contenir '\0'
			if (*(*(liste_pieces+i)+j) == NULL){
				exit(10);
			}
		}
	}
	FILE* fichier = NULL;
	fichier = fopen("pieces.txt","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (1);
	}
	
	//Cette partie du code nécessite que le fichier texte contenant les pièces est une forme bien spécifique !!!
	for (int i = 0;i<NOMBRE_PIECES;i++){ 		//récupère pièce par pièce
		for (int j = 0; j<DIM;j++){ 			//récupère ligne par ligne les pièces qui se trouvent dans le fichier texte dans le tableau liste_pieces
			if (fgets(liste_pieces[i][j],DIM+1,fichier) == NULL){
				printf("Erreur dans le fichier texte, la lecture d'une ligne de la piece n'a pas abouti. \n");
			}
			fgetc(fichier); 					//passer le '\n' aprés chaque ligne 
		}
		if (fgetc(fichier) != '#'){
			printf("Erreur dans le fichier texte, le separateur n'est pas correcte. \n");
		}  										//passer le '#' qui est le séparateur de pièce
		fgetc(fichier);  						//passer le '\n' après le '#'
	}
	
	fclose(fichier);
	return liste_pieces;
}



void rotation(int rotation, Tetromino *t){ // rotation : 4 si gauche, 5 si droite ; 'piece' sera le tableau contenant la pièce actif sur la grille
	int temp;
	int posx;
	int posy;
	int dx,dy;
	if (t == NULL){
		exit(10);
	}
	
	if (t->isalive && isNotBorderL(t) && isNotBorderR(t)){
	//On calcule les distances x et y du centre du tetromino pour déplacer tous les blocs en haut à gauche de la grille pour faire comme si il se trouvait dans un tableau de 5 par 5,
	//ensuite on change les coordonnées pour tourner le tétromino, puis on redéplace tous les blocs à l'endroit initial grâce à dx et dy
	if (rotation == 5){ //tourne de 90 degrés vers la gauche la pièce
		for (int i = DIM-1; i >=0; i--){
			dx = 2-t->blocs[0][0]; //distance entre le centre du tetromino et le point (2,2)
			dy = 2-t->blocs[0][1]; //distance entre le centre du tetromino et le point (2,2)
			posx = t->blocs[i][0]+dx;
			posy = t->blocs[i][1]+dy;
			temp = posy;
			posy = posx;
			posx = DIM - temp -1;
			if (posx>=0 && posx<LINE && posy>=0 && posy<COL){
				t->blocs[i][0] = posx-dx;
				t->blocs[i][1] = posy-dy;
			}else{
				return;
			}
		}
	}

	else if (rotation == 1){ //tourne de 90 degrés vers la droite la pièce
		//Même chose mais dans l'autre sens
		for (int i = DIM-1; i >=0; i--){
			dx = 2-t->blocs[0][0];
			dy = 2-t->blocs[0][1];
			posx = t->blocs[i][0]+dx;
			posy = t->blocs[i][1]+dy;
			temp = posx;
			posx = posy;
			posy = DIM - temp -1;
			if (posx>=0 && posx<LINE && posy>=0 && posy<COL){
				t->blocs[i][0] = posx-dx;
				t->blocs[i][1] = posy-dy;
			}
		}
	}
	}
}


void afficheliste(char ***liste_pieces){
	for (int i = 0;i<NOMBRE_PIECES;i++){
		for (int j = 0; j<DIM;j++){
			printf("%s",liste_pieces[i][j]);
			printf("\n");
			
		}
		printf("\n");
	}
}


void affichepiece(char **piece){
	for (int j = 0; j<DIM;j++){
		printf("%s",piece[j]);
		printf("\n");		
	}
}