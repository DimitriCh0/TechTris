#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define NOMBRE_PIECES 7
#define DIM 5
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
	return liste_pieces;
}

char*** lecture(char ***liste_pieces){
	FILE* fichier = NULL;
	fichier = fopen("piecesdefault.txt","r+");
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



void rotation(int rotation, char** piece){ // rotation : 4 si gauche, 5 si droite ; 'piece' sera le tableau contenant la pièce actif sur la grille
	if (piece == NULL){
		exit(10);
	}
	char **tmp = malloc (DIM*sizeof(char*)); //création d'un tableau temporaire qui stockera la pièce avec la rotation voulue
	if (tmp == NULL){
		exit(10);
	}
	for (int i = 0; i<DIM;i++){
		*(tmp+i) = malloc((DIM+1)*sizeof(char));
		if (*(tmp+i) == NULL){
			exit(10);
		}
	}
	
	if (rotation == 4){ //tourne de 90 degrés vers la gauche la pièce
		for (int i = 0; i < DIM; i++){
			for (int j = 0; j < DIM; j++){
				tmp[i][j] = piece[j][DIM-i-1];
			}
			tmp[i][DIM] = '\0';
		}
	}
	else if (rotation == 5){ //tourne de 90 degrés vers la droite la pièce
		for (int i = 0; i < DIM; i++){
			for (int j = 0; j < DIM; j++){
				tmp[i][j] = piece[DIM-j-1][i];
			}
			tmp[i][DIM] = '\0';
		}
	}
	for (int i = 0; i < DIM; i++){ //change la pièce active
		for (int j = 0; j < DIM; j++){
			piece[i][j]=tmp[i][j];
		}
	}
	for (int i = 0; i < DIM; i++) { //libère le tableau tmp et les chaînes de caractères contenues dans le tableau
	free(tmp[i]);
	}
	free(tmp);
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

