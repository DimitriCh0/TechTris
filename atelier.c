#include "fichier.h"

#define NUM_CASE DIM*DIM
const char *options2[] = {"Piece precedente","Quitter l'Atelier","Defaut","Enregistrer","Piece suivante"};
#define NUM_OPTIONS2 (sizeof(options2) / sizeof(char*))

void print_tab(char ligne, int highlight) { //Naviguer dans la grille du dessin de la piece
	if (highlight) {
        	printf("  \033[1;32m%c\033[0m", ligne); // Texte vert si sélectionné
	} 
	else {
        	printf("  %c", ligne);
	}
}

void print_colored2(const char *text, int highlight) { //Naviguer dans les options sous la grille
	if (highlight) {
        	printf("> \033[1;32m%s\033[0m < ", text); // Texte vert si sélectionné
	} 
	else {
        	printf("  %s ", text);
	}
}

void enregistrement(){

}

void atelier(){
	char*** piecesedited = NULL; //Créer un tableau de tableau à 2 dimensions rempli de '\0' qui contiendra les dessins
	piecesedited = calloc(NOMBRE_PIECES,sizeof(char**)); 		//Créer le tableau qui contiendra chaque pièce (une pièce étant un tableau a 2 dimensions)
	if (piecesedited == NULL){
		exit(10);
	}
	for (int i = 0;i<NOMBRE_PIECES;i++){
		*(piecesedited+i) = calloc(DIM,sizeof(char*)); 		//Créer les tableaux qui contiendront les chaines de caractères correspondant à chaque ligne qui forme une pièce (5 lignes)
		if (*(piecesedited+i) == NULL){
			exit(10);
		}
		for (int j = 0; j<DIM;j++){
			*(*(piecesedited+i)+j) = calloc((DIM+1),sizeof(char)); 		//Créer les chaines de caractères qui contiendront les pièces ligne par ligne + (DIM+1) pour contenir '\0'
			if (*(*(piecesedited+i)+j) == NULL){
				exit(10);
			}
		}
	}
	for (int p = 0; p < NOMBRE_PIECES; p++){
		for (int i = 0; i<DIM; i++){
			for (int j = 0; j<DIM; j++){
				piecesedited[p][i][j] = '0';
			}
		}
		piecesedited[p][DIM/2][DIM/2] = '1'; //Règle de dessin : le bloc au centre est forcément fixe
	}

	int selected = 0;
	int input;
	int piece = 0; //Savoir quelle pièce on dessine parmi les 7
	int t = 1;
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Atelier =====", 0);
		printf("\n    Piece #%d \n \n",piece+1);

		for (int i = 0; i < DIM; i++) {
			for (int j = 0; j < DIM; j++) {
		    		print_tab(piecesedited[piece][i][j], (i*DIM+j) == selected);
			}
			printf("\n");
		}
		printf("\n");
		for (int i = NUM_CASE; i < NUM_OPTIONS2+NUM_CASE; i++) {
		    print_colored2(options2[i-NUM_CASE], i == selected);
		}
		
		printf("\n");
		printf("\nUtilise Z (haut), S (bas), D (droite), Q (gauche), E (valider)\n");

		input = get_input();
		
		//Se déplacer
		if (input == 'z' || input == 'Z') {
			if ((selected - DIM) >= 0){
				selected = selected - DIM;
			}
		} 
		else if (input == 's' || input == 'S') {
			if ((selected + DIM) < NUM_CASE+DIM){
				selected = selected + DIM;
			}
		}
		if (input == 'd' || input == 'D') {
			selected = (selected + 1) % DIM + DIM * (selected/DIM);
		} 
		else if (input == 'q' || input == 'Q') {
			selected = (selected - 1+DIM) % DIM + DIM * (selected/DIM);
		}  
		else if (input == 'e' || input == 'E') {
			switch (selected) {
				case((NUM_CASE-1) / 2):
					break; //Bloquer la modification du bloc au milieu
		        	case (NUM_CASE):
		            		if (piece - 1 >= 0){
		            			piece --; //Changer de pièce à modifier
		            		}
		            		break;
		        	case (NUM_CASE+1):
		            		t = 0; //Quitter l'Atelier
		            		break;
		        	case (NUM_CASE+2):
		            		
		            		break;
				case (NUM_CASE+3):
					enregistrement();
					break;
				case (NUM_CASE+4):
					if (piece + 1 < 7){
		            			piece ++; //Changer de pièce à modifier
		            		}
					break;
				default:
					if (piecesedited[piece][selected/DIM][selected%DIM] == '0'){
						piecesedited[piece][selected/DIM][selected%DIM] = '1';
					}
					else{
						piecesedited[piece][selected/DIM][selected%DIM] = '0';
					}
					break;
			}
		}
	}
	
}
