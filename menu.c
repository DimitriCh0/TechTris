#include "fichier.h"



const char *options[] = {"Jouer","Rejouer","Scoreboard","Atelier","Pieces","Quitter"};
#define NUM_OPTIONS (sizeof(options) / sizeof(char*))

//surlignage
void print_colored(const char *text, int highlight) {
	if (highlight) {
        	printf("             > \033[1;32m%s\033[0m <\n", text); // Texte vert si sélectionné
	} 
	else {
        	printf("              %s\n", text);
	}
}


void wait_for_enter() {
	int ch;
	printf("\n\nAppuie sur Entrée pour continuer..."); 
	do {
        	ch = getchar();
    	} while (ch != '\n' && ch != EOF);
}

void tetris() { 
	system("clear");
	int tab[LINE][COL]= {0};
	Joueur J = constru();
	jeu_tetris(&J,tab,0);
}

void lecture_sauvegarde(FILE *fichier, char tab_char[LINE][COL+1], int tab_int[LINE][COL], Joueur* Joueur){
	char variable;
	if (fichier == NULL || tab_char == NULL || Joueur == NULL){
		exit(10);
	}
	rewind(fichier);
	for (int i = 0;i<LINE;i++){ 
		if (fgets(tab_char[i],COL+1,fichier) == NULL){
			printf("Erreur dans le fichier texte, la lecture d'une ligne de la grille n'a pas abouti. \n");
			exit(1);
		}
		fgetc(fichier); 					//passer le '\n' après chaque ligne 
	}
	for (int i = 0; i <LINE;i++){
		for (int j = 0; j<COL;j++){
			if (tab_char[i][j] == '0'){
				tab_int[i][j] = 0;
			}
			else {
				switch(tab_char[i][j]){
		            		case '1':
				        	tab_int[i][j] = 8;
				        	break;
		          		case '2':
		                		tab_int[i][j] = 9;
		                		break;
		            		case '3':
		               			tab_int[i][j] = 10;
		                		break;
		            		case '4':
		                		tab_int[i][j] = 11;
		                		break;
		            		case '5':
		                		tab_int[i][j] = 12;
		                		break;
		            		case '6':
		                		tab_int[i][j] = 13;
		                		break;
		            		case '7':
		                		tab_int[i][j] = 14;
		                		break;
		        	}
			}
		}
	}
	if (fgetc(fichier) != '@'){
		printf("Erreur dans le fichier texte, mauvais séparateur \n");
		exit(1);
	}
	while ((variable=fgetc(fichier)) != EOF){
		if(variable=='#'){
            		if ((fgets(Joueur->pseudo,sizeof(Joueur->pseudo),fichier)) != NULL){// Lire la ligne.
            			Joueur->pseudo[strcspn(Joueur->pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n
            		}
        	}
        	else if (variable=='&'){
            		fscanf(fichier,"%d ",&Joueur->score);
        	}
		else if (variable=='/'){
			fscanf(fichier,"%d ",&Joueur->difficulte);
		}
    	}
}


void sauvegarde(){
	char tab_char[LINE][COL+1];
	int tab_int [LINE][COL] ={0};
	Joueur J;
	system("clear");
	FILE* fichier = NULL;
	fichier = fopen("sauvegarde.txt","r");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (1);
	}
	if (fgetc(fichier) == EOF){
		printf("\n\n Aucune sauvegarde detectee ! \n\n");
		wait_for_enter();
	}
	else {
		lecture_sauvegarde(fichier,tab_char,tab_int,&J);
		jeu_tetris(&J,tab_int,1);
	}
}

void scoreboard() { //Afficher le scoreboard
	system("clear");
	printf("         ===== Scoreboard =====\n\n");
	printf("  Pseudo    |     Score    |  Difficulte \n");
	FILE* fichier = NULL;
	fichier = fopen("scoreboard.txt","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (157);
	}
	lire_scoreboard(fichier);
	fclose(fichier);
	wait_for_enter();
}

void dessin() { //Lance la procédure permettant de dessiner les pièces
	atelier();
}

void avantdessin() { //Affiche le règlement pour dessiner les pièces (à finir)
	system("clear");
	printf("Bienvenue dans le menu pour dessiner tes pieces ! \n");
	printf("Quelques regles avant de commencer : \n\n");
	printf(" - Vous avez 7 pieces a dessiner. \n\n");
	printf(" - Il y a un bloc placé par défaut, celui du centre. \n\n");
	printf(" - Vous disposez de 4 blocs à placer pour créer votre propre piece. \n\n");
	printf(" - Il n'est pas obligatoire d'utiliser les 4 blocs. \n\n");
	printf(" - A partir du bloc que vous placez, vous devez pouvoir acceder au centre de la piece. \n\n");
	printf(" - 'Defaut' permet de jouer avec les pieces de base de Tetris. \n\n");
	printf(" - 'Enregistrer' permet de sauvegarder vos pieces apres les avoir dessiner. \n\n");
	printf(" - ATTENTION une fois sauvegardée, vous ne pourrez pas remodifier les pieces si vous quittez l'Atelier. \n\n");
	wait_for_enter();
	dessin();
}

void affichagepieces(){
	system("clear");
	printf("Voici les pieces avec lesquelles vous allez jouer !\n\n");
	char *** piecesactives=pieces();
	lecture(piecesactives,1);
	afficheliste(piecesactives);
	liberer_pieces(piecesactives);
	wait_for_enter();
}

void display_menu() {
	int selected = 0; //Savoir où se trouve le "curseur"
	int input;
	int t = 1;
	char*** pieces_dessinees = pieces();
	lecture(pieces_dessinees,0);
	enregistrement(pieces_dessinees);
	liberer_pieces(pieces_dessinees);
	while (t) {
		system("clear");
		printf("\n\n\n");
		printf(" _____ _____ _____ _____ _ ______  \n");
    		printf("|_   _|  ___|_   _|  _  | |      | \n");
    		printf("  | | | |___  | | | |_| | |  ____| \n");
    		printf("  | | |  ___| | | |    _| |____  | \n");
    		printf("  | | | |___  | | | || || |      | \n");
    		printf("  |_| |_____| |_| |_| |_|_|______| \n\n\n");
		printf("         ===== MENU =====");
		printf("\n\n");

		for (int i = 0; i < NUM_OPTIONS; i++) { //Affiche les options du menu
		    print_colored(options[i], i == selected);
		}

		printf("\nUtilise Z (haut), S (bas), E (valider)\n");

		input = get_input();

		// Se déplacer
		if (input == 'z' || input == 'Z') { 
			selected = (selected - 1 + NUM_OPTIONS) % NUM_OPTIONS;
		} 
		else if (input == 's' || input == 'S') {
			selected = (selected + 1) % NUM_OPTIONS;
		} 
		else if (input == 'e' || input == 'E') { //Selectionner
			switch (selected) {
		        	case 0:
		            		tetris();
		            		break;
		            	case 1:
		            		sauvegarde();
		            		break;
		        	case 2:
		            		scoreboard();
		            		break;
		        	case 3:
		            		avantdessin();
		            		break;
		            	case 4:
		            		affichagepieces();
		            		break;
				case 5:
					system("clear");
					printf("\n\n");
					print_colored("À bientôt !", 0);
					printf("\n\n");
					t = 0;
					break;
		    }
		}
	}

}

