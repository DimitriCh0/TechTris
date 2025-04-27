#include "fichier.h"

const char *options2[] = {"Piece precedente","Quitter l'Atelier","Defaut","Enregistrer","Piece suivante"};
const char *options3[] = {"Retour en arrière","Continuer"};
#define NUM_OPTIONS2 (sizeof(options2) / sizeof(char*))
#define NUM_OPTIONS3 (sizeof(options3) / sizeof(char*))

//une pièce est définie comme : '1' = bloc et '0' = vide

char*** pieces(){ //procedure qui crée un tableau utilisé pour la lecture des pieces dans le jeu
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

void lecture(char*** liste_pieces,int var){
	FILE* fichier = NULL;
	if (var){
		fichier = fopen("piecesedited.txt","r+");
	}
	else{
		fichier = fopen("piecesdefault.txt","r+");
	}
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
				exit(1);
			}
			fgetc(fichier); 					//passer le '\n' aprés chaque ligne 
		}
		if (fgetc(fichier) != '#'){
			printf("Erreur dans le fichier texte, le separateur n'est pas correcte. \n");
			exit(1);
		}  										//passer le '#' qui est le séparateur de pièce
		fgetc(fichier);  						//passer le '\n' après le '#'
	}
	for (int i = 0; i <NOMBRE_PIECES;i++){
		for (int j = 0; j<DIM;j++){ 
			for (int k = 0; k<DIM;k++){ 
				if (liste_pieces[i][j][k] != '1' && liste_pieces[i][j][k] != '0'){
					printf("Erreur dans le fichier texte, le format n'est pas respecté \n");
					exit(1);
				}
			}
		}
	}
	fclose(fichier);
	
}

void liberer_pieces(char*** liste_pieces){
	if (liste_pieces == NULL){
		return;
	}
	for (int i = 0; i < NOMBRE_PIECES; i++) {
        if (liste_pieces[i] != NULL) {
            for (int j = 0; j < DIM; j++) {
                if (liste_pieces[i][j] != NULL) {
                    free(liste_pieces[i][j]); // Libérer chaque ligne
                }
            }
            free(liste_pieces[i]); // Libérer le tableau de lignes
        }
    }
    free(liste_pieces); // Libérer le tableau des pièces
}

void afficheliste(char ***liste_pieces){
	for (int i = 0;i<DIM;i++){
		for (int j = 0; j<NOMBRE_PIECES;j++){
			printf("%s",liste_pieces[j][i]);
			printf("    ");
			
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

void enregistrement(char*** pieces_dessinees){
	FILE* fichier = NULL;
	fichier = fopen("piecesedited.txt","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (1);
	}
	
	//
	for (int i = 0;i<NOMBRE_PIECES;i++){ 		
		for (int j = 0; j<DIM;j++){ 			
			fputs(pieces_dessinees[i][j],fichier);
			fputs("\n",fichier);
		}
		fputs("#\n",fichier);
	}
	fclose(fichier);
}


void menu_enregistrement(char*** pieces_dessinees){
	int selected = 0;
	int input;
	int t = 1;
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Enresgistrement =====", 0);
		printf("\n  Sauvegarder les modifications ? \n \n");

		for (int i = 0; i < NUM_OPTIONS3; i++) {
		    print_colored2(options3[i], i == selected);
		}
		
		printf("\n");
		printf("\nD (droite), Q (gauche), E (valider)\n");

		input = get_input();
		if (input == 27){ //Probleme : quand la fleche gauche est appuyé, cela déplace le curseur car dans le terminal, flèche gauche = ^[[D, donc cette partie empêche les conflits de touches
			input = get_input();
			if (input == '['){
				input = get_input();
				if (input == 'D'){
					//fait rien
				}
			}
		}
		//Se déplacer
		if (input == 'd' || input == 'D') { //Probleme : quand fleche gauche appuyé
			selected = (selected + 1)%NUM_OPTIONS3;
		} 
		else if (input == 'q' || input == 'Q') {
			selected = (selected - 1 + NUM_OPTIONS3)%NUM_OPTIONS3;
		}  
		else if (input == 'e' || input == 'E') {
			switch (selected) {
				case 0:
					t=0;
					break;
		        	case 1:
		            		enregistrement(pieces_dessinees);
		            		t=0;
		            		break;
		        }
		}
	}
}

char*** pieces_vide(){ //Créer un tableau de tableau à 2 dimensions rempli de '\0' qui contiendra les dessins
	char*** pieces = NULL; 
	pieces = calloc(NOMBRE_PIECES,sizeof(char**)); 		//Créer le tableau qui contiendra chaque pièce (une pièce étant un tableau a 2 dimensions)
	if (pieces == NULL){
		exit(10);
	}
	for (int i = 0;i<NOMBRE_PIECES;i++){
		*(pieces+i) = calloc(DIM,sizeof(char*)); 		//Créer les tableaux qui contiendront les chaines de caractères correspondant à chaque ligne qui forme une pièce (5 lignes)
		if (*(pieces+i) == NULL){
			exit(10);
		}
		for (int j = 0; j<DIM;j++){
			*(*(pieces+i)+j) = calloc((DIM+1),sizeof(char)); 		//Créer les chaines de caractères qui contiendront les pièces ligne par ligne + (DIM+1) pour contenir '\0'
			if (*(*(pieces+i)+j) == NULL){
				exit(10);
			}
		}
	}
	for (int p = 0; p < NOMBRE_PIECES; p++){
		for (int i = 0; i<DIM; i++){
			for (int j = 0; j<DIM; j++){
				pieces[p][i][j] = '0';
			}
		}
		pieces[p][DIM/2][DIM/2] = '1'; //Règle de dessin : le bloc au centre est forcément fixe
	}
	return pieces;
}

int voisin(char*** pieces_dessinees, int piece, int selected) { //condition pour placer un bloc
    int x = selected / DIM;
    int y = selected % DIM;
    int bool = 0;
    if ((x > 0 && pieces_dessinees[piece][x-1][y] == '1') ||(x < DIM-1 && pieces_dessinees[piece][x+1][y] == '1') ||(y > 0 && pieces_dessinees[piece][x][y-1] == '1') ||(y < DIM-1 && pieces_dessinees[piece][x][y+1] == '1')){
    	bool = 1;
    }
    return bool;
}

// La procedure / fonction suivantes permettent de verifier si les blocs placés sont bien tous reliés au centre en [2][2] qui est forcément placé
void lie_centre(char*** pieces_dessinees, int piece, int x, int y, int deja_verif[DIM][DIM]){ // récursivité terminal partant du centre jusqu'aux bords
	if (x < 0 || x >= DIM || y < 0 || y >= DIM){ //Hors limite
		return;
	}
	if (deja_verif[x][y]) { //Déjà vérifié
		return;
	}
	if (pieces_dessinees[piece][x][y] != '1'){ //Pas un chemin
		return;
	}
	
	deja_verif[x][y] = 1;
	
	lie_centre(pieces_dessinees,piece,x-1,y,deja_verif);
	lie_centre(pieces_dessinees,piece,x+1,y,deja_verif);
	lie_centre(pieces_dessinees,piece,x,y-1,deja_verif);
	lie_centre(pieces_dessinees,piece,x,y+1,deja_verif);
}

int correction(char *** pieces_dessinees, int piece){ //Applique les changements de 1 en 0 s'il n'existe pas de chemin jusqu'au centre
	int bloc_enleve=0;
	int deja_verif[DIM][DIM]={0}; //Tableau servant de booléen pour savoir si une case a déjà été visité ou non
	if (pieces_dessinees[piece][2][2] == '1'){
		lie_centre(pieces_dessinees,piece,2,2,deja_verif);
	}
	for (int i = 0; i<DIM; i++){
		for (int j = 0; j<DIM; j++){
			if (pieces_dessinees[piece][i][j] == '1' && deja_verif[i][j] == 0){
				pieces_dessinees[piece][i][j]='0';
				bloc_enleve++;
			}
		}
	}
	return bloc_enleve;
}

int menu_defaut(char *** pieces_dessinees){
	int selected = 0;
	int input;
	int t = 1;
	int statut = 0;
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Defaut =====", 0);
		printf("\n  Jouer avec les pièces de TETRIS par défaut ? \n \n");

		for (int i = 0; i < NUM_OPTIONS3; i++) {
		    print_colored2(options3[i], i == selected);
		}
		
		printf("\n");
		printf("\nD (droite), Q (gauche), E (valider)\n");

		input = get_input();
		if (input == 27){ //Probleme : quand la fleche gauche est appuyé, cela déplace le curseur car dans le terminal, flèche gauche = ^[[D, donc cette partie empêche les conflits de touches
			input = get_input();
			if (input == '['){
				input = get_input();
				if (input == 'D'){
					//fait rien
				}
			}
		}
		//Se déplacer
		if (input == 'd' || input == 'D') { //Probleme : quand fleche gauche appuyé
			selected = (selected + 1)%NUM_OPTIONS3;
		} 
		else if (input == 'q' || input == 'Q') {
			selected = (selected - 1 + NUM_OPTIONS3)%NUM_OPTIONS3;
		}  
		else if (input == 'e' || input == 'E') {
			switch (selected) {
				case 0:
					t=0;
					statut = 1;
					break;
		        	case 1:
		            		lecture(pieces_dessinees,0);
		            		enregistrement(pieces_dessinees);
		            		liberer_pieces(pieces_dessinees);
		            		t=0;
		            		break;
		        }
		}
	}
	return statut;
}
	
void atelier(){
	char ***pieces_dessinees = pieces_vide();
	int selected = 0;
	int input;
	int bloc_dispo[NOMBRE_PIECES]; // Nombre de blocs disponibles par piece
	for (int i = 0; i < NOMBRE_PIECES;i++){
		bloc_dispo[i] = BLOC_MAX-1;
	} 
	int piece = 0; //Savoir quelle pièce on dessine parmi les 7
	int t = 1;
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Atelier =====", 0);
		printf("\n    Piece #%d \n \n",piece+1);

		for (int i = 0; i < DIM; i++) {
			for (int j = 0; j < DIM; j++) {
		    		print_tab(pieces_dessinees[piece][i][j], (i*DIM+j) == selected);
			}
			printf("\n");
		}
		printf("\n  Blocs disponibles : %d \n ",bloc_dispo[piece]);
		printf("\n");
		for (int i = NUM_CASE; i < NUM_OPTIONS2+NUM_CASE; i++) {
		    print_colored2(options2[i-NUM_CASE], i == selected);
		}
		
		printf("\n");
		printf("\nUtilise Z (haut), S (bas), D (droite), Q (gauche), E (valider)\n");

		input = get_input();
		
		if (input == 27){ //Probleme : quand la fleche gauche est appuyé, cela déplace le curseur car dans le terminal, flèche gauche = ^[[D, donc cette partie empêche les conflits de touches
			input = get_input();
			if (input == '['){
				input = get_input();
				if (input == 'D'){
					//fait rien
				}
			}
		}
		//Se déplacer
		else if (input == 'z' || input == 'Z') {
			if ((selected - DIM) >= 0){
				selected = selected - DIM;
			}
		} 
		else if (input == 's' || input == 'S') {
			if ((selected + DIM) < NUM_CASE+DIM){
				selected = selected + DIM;
			}
		}
		else if (input == 'd'|| input == 'D') { 
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
		        		liberer_pieces(pieces_dessinees);
		            		t = 0; //Quitter l'Atelier
		            		break;
		        	case (NUM_CASE+2):
		            		t=menu_defaut(pieces_dessinees);
		            		break;
				case (NUM_CASE+3):
					menu_enregistrement(pieces_dessinees);
					break;
				case (NUM_CASE+4):
					if (piece + 1 < 7){
		            			piece ++; //Changer de pièce à modifier
		            		}
					break;
				default:
					if (pieces_dessinees[piece][selected/DIM][selected%DIM] == '0' && bloc_dispo[piece] > 0 && voisin(pieces_dessinees,piece,selected)){
						pieces_dessinees[piece][selected/DIM][selected%DIM] = '1';
						bloc_dispo[piece]--;
					}
					else if (pieces_dessinees[piece][selected/DIM][selected%DIM] == '1' && bloc_dispo[piece] < 4){
						pieces_dessinees[piece][selected/DIM][selected%DIM] = '0';
						bloc_dispo[piece]++;
						
					}
					bloc_dispo[piece]+=correction(pieces_dessinees,piece);
					break;
			}
		}
	}
	
}
