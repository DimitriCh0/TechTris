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
	float r;
	float alpha;
	if (t == NULL){
		exit(10);
	}
	if (t->isalive && isNotBorderL(t) && isNotBorderR(t)){
	if (rotation == 5){ //tourne de 90 degrés vers la gauche la pièce
		showCoordonnates(t);
		for (int i = 1; i < DIM; i++){
			
			r = sqrt((t->blocs[i][0]-t->blocs[0][0])*(t->blocs[i][0]-t->blocs[0][0]) +(t->blocs[i][1]-t->blocs[0][1])*(t->blocs[i][1]-t->blocs[0][1]));
			
			if (t->blocs[i][0]!=t->blocs[0][0] && t->blocs[i][1]!=t->blocs[0][1]){
				alpha = atan((t->blocs[i][1]-t->blocs[0][1])/(t->blocs[i][0]-t->blocs[0][0]));
			}else{
				alpha = acos((t->blocs[i][1]-t->blocs[0][1])/r);//Trigo sin(alpha)=opposé(y)/r
			}
			
			alpha += 3.14/2;
			
			t->blocs[i][0] = FLOAT_TO_INT(r*cos(alpha))+t->blocs[0][0];
	
			t->blocs[i][1] = FLOAT_TO_INT(r*sin(alpha))+t->blocs[0][1];

			printf("alpha = %.2f  r = %.2f\n",alpha,r);
			printf("x = %.2f  y = %.2f --->  ",r*cos(alpha),r*sin(alpha));
			printf("x = %d  y = %d\n",t->blocs[i][0],t->blocs[i][1]);
			printf("\n");
			
		}
		showCoordonnates(t);
	}
	else if (rotation == 1){ //tourne de 90 degrés vers la droite la pièce
		for (int i = 0; i < DIM; i++){
			temp = t->blocs[i][1];
			t->blocs[i][1] = t->blocs[i][0];
			t->blocs[i][0] = DIM - temp -1;
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