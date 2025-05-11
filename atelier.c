#include "fichier.h"

//Affichage d'une case colorée et si la case est sélectionnée
void choix_couleur2(char valeur, const char *Couleur, int highlight){
	if (Couleur==NULL){
		printf("Erreur : void choix_couleur2 !\n");
        	exit(30);
        }
	if (highlight){	//Case sélectionnée
		switch(valeur){ 
			case '0':
				printf("⬛ ");
				break;
			case '1':
				printf("\033[47m%s \033[0m",Couleur);
				break;
		}
	}
	else{
		switch(valeur){
			case '0':
				printf("⬜ ");
				break;
			case '1':
				printf("%s ",Couleur);
				break;
		}
	}
}

//Affiche la case colorée dans l'atelier
void print_tab(char valeur, int highlight, int piece) {
	if (piece<0){
		printf("Erreur : void print_tab !\n");
        	exit(31);
        }
	const char *couleurs[NOMBRE_PIECES] = {"🟧","🟨","🟩","🟫","🟪","🟦","🟥"};
        choix_couleur2(valeur,couleurs[piece],highlight);
}

//Naviguer dans les options sous la grille
void print_colored2(const char *text, int highlight) { 
	if (text==NULL){
		printf("Erreur : void print_colored2 !\n");
        	exit(32);
        }
	if (highlight) {
        	printf("> \033[1;32m%s\033[0m < ", text); // Texte vert si sélectionné
	} 
	else {
        	printf("  %s ", text);
	}
}

//Enregistrement des pièces contenues dans le triple pointeur dans le fichier "piecesmodifiees.txt"
void enregistrement(char*** pieces_dessinees){
	if (pieces_dessinees==NULL){
		printf("Erreur : void enregistrement !\n");
        	exit(33);
        }
        for (int i = 0;i<NOMBRE_PIECES;i++){ 		
		for (int j = 0; j<DIM;j++){ 			
			for (int k = 0; k<DIM;k++){
				if (pieces_dessinees[i][j][k] != '0' && pieces_dessinees[i][j][k] != '1'){
					printf("Erreur dans le tableau de pièces, valeur incorrecte \n");
					exit(34);
				}
			}
		}
	}
	FILE* fichier = NULL;
	fichier = fopen("piecesmodifiees.txt","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (35);
	}
	
	for (int i = 0;i<NOMBRE_PIECES;i++){ 		
		for (int j = 0; j<DIM;j++){ 			
			fputs(pieces_dessinees[i][j],fichier); //ligne par ligne
			fputs("\n",fichier);
		}
		fputs("#\n",fichier); //séparateur
	}
	fclose(fichier);
	fichier = fopen("sauvegarde.txt","w+"); //Supprime la sauvegarde existante pour éviter de jouer à la même partie avec des sets de pièces différents
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (36);
	}
	fclose(fichier);
}

//Sous-menu Enregistrer pour valider ou non
void menu_enregistrement(char*** pieces_dessinees){
	if (pieces_dessinees==NULL){
		printf("Erreur : void menu_enregistrement !\n");
        	exit(37);
        }
	int selected = 0;
	int input;
	int t = 1;
	const char *options3[] = {"Retour","Continuer"};
	int num_options3 = (sizeof(options3) / sizeof(char*));
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Enregistrement =====", 0);
		printf("\n            Sauvegarder les modifications ? \n \n");
		printf("    ");
		for (int i = 0; i < num_options3; i++) {
		    print_colored3(options3[i], i == selected);
		}
		
		printf("\n\n Attention, si vous avez une partie sauvegardée, cette dernière sera supprimée ! \n");
		printf("\n\n\n D (droite), Q (gauche), E (valider)\n");

		input = get_input();
		
		//Se déplacer
		if (input == 'd' || input == 'D') { //Probleme : quand fleche gauche appuyé
			selected = (selected + 1)%num_options3;
		} 
		else if (input == 'q' || input == 'Q') {
			selected = (selected - 1 + num_options3)%num_options3;
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
//Créer un tableau de tableau à 2 dimensions rempli de '\0' qui contiendra les dessins
char*** pieces_vide(){ 
	char*** pieces = NULL; 
	pieces = calloc(NOMBRE_PIECES,sizeof(char**)); 		//Créer le tableau qui contiendra chaque pièce (une pièce étant un tableau a 2 dimensions)
	if (pieces == NULL){
		exit(38);
	}
	for (int i = 0;i<NOMBRE_PIECES;i++){
		*(pieces+i) = calloc(DIM,sizeof(char*)); 		//Créer les tableaux qui contiendront les chaines de caractères correspondant à chaque ligne qui forme une pièce (5 lignes)
		if (*(pieces+i) == NULL){
			exit(39);
		}
		for (int j = 0; j<DIM;j++){
			*(*(pieces+i)+j) = calloc((DIM+1),sizeof(char)); 		//Créer les chaines de caractères qui contiendront les pièces ligne par ligne + (DIM+1) pour contenir '\0'
			if (*(*(pieces+i)+j) == NULL){
				exit(30);
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

//Condition pour placer un bloc, avoir un "1" collé
int voisin(char*** pieces_dessinees, int piece, int selected) { 
	if (pieces_dessinees==NULL || piece < 0){
		printf("Erreur : int voisin !\n");
        	exit(31);
        }
    	int x = selected / DIM;
    	int y = selected % DIM;
    	int var = 0;
    	if ((x > 0 && pieces_dessinees[piece][x-1][y] == '1') ||(x < DIM-1 && pieces_dessinees[piece][x+1][y] == '1') ||(y > 0 && pieces_dessinees[piece][x][y-1] == '1') ||(y < DIM-1 && pieces_dessinees[piece][x][y+1] == '1')){
    		var = 1;
    	}
    	return var;
}

// La procedure / fonction suivantes permettent de verifier si les blocs placés sont bien tous reliés au centre en [2][2] qui est forcément placé
void lie_centre(char*** pieces_dessinees, int piece, int x, int y, int deja_verif[DIM][DIM]){ // récursivité terminal partant du centre jusqu'aux bords
	if (pieces_dessinees==NULL || piece < 0){
		printf("Erreur : void lie_centre !\n");
        	exit(32);
        }
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

//Applique les changements de 1 en 0 s'il n'existe pas de chemin jusqu'au centre, retourne le nombre de blocs enlevés et possible à remettre
int correction(char *** pieces_dessinees, int piece){ 
	if (pieces_dessinees==NULL || piece < 0){
		printf("Erreur : int correction !\n");
        	exit(33);
        }
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

//Sous-menu Defaut pour jouer avec le set de pièces par défaut de Tetris 
int menu_defaut(char *** pieces_dessinees){
	if (pieces_dessinees==NULL){
		printf("Erreur : int menu_defaut !\n");
        	exit(34);
        }
	int selected = 0;
	int input;
	int t = 1;
	int statut = 0;
	const char *options3[] = {"Retour","Continuer"};
	int num_options3 = (sizeof(options3) / sizeof(char*));
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Defaut =====", 0);
		printf("\n   Jouer avec les pièces de TETRIS par défaut ? \n \n");

		for (int i = 0; i < num_options3; i++) {
		    print_colored3(options3[i], i == selected);
		}
		
		printf("\n\n Attention, si vous avez une partie sauvegardée, cette dernière sera supprimée ! \n");
		printf("\n\n\nD (droite), Q (gauche), E (valider)\n");

		input = get_input();
		
		//Se déplacer
		if (input == 'd' || input == 'D') { //Probleme : quand fleche gauche appuyé
			selected = (selected + 1)%num_options3;
		} 
		else if (input == 'q' || input == 'Q') {
			selected = (selected - 1 + num_options3)%num_options3;
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
	
//Menu Atelier 
void atelier(){
	const char *options2[] = {"Piece precedente","Quitter l'Atelier","Defaut","Enregistrer","Piece suivante"};
	int num_options2 = (sizeof(options2) / sizeof(char*));
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
		printf("\n                   Piece #%d \n \n",piece+1);

		for (int i = 0; i < DIM; i++) { //Afficher le tableau case par case
			printf("                ");
			for (int j = 0; j < DIM; j++) {
		    		print_tab(pieces_dessinees[piece][i][j], (i*DIM+j) == selected,piece);
			}
			printf("\n");
		}
		printf("\n             Blocs disponibles : %d \n ",bloc_dispo[piece]);
		printf("\n");
		for (int i = NUM_CASE; i < num_options2+NUM_CASE; i++) {
		    print_colored2(options2[i-NUM_CASE], i == selected);
		}
		
		printf("\n\n\nUtilise Z (haut), S (bas), D (droite), Q (gauche), E (valider)\n");

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
				default: //placer les blocs selon les conditions
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
