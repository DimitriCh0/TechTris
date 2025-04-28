#include "fichier.h"



const char *options[] = {"Jouer","Scoreboard","Atelier","Pieces","Quitter"};
#define NUM_OPTIONS (sizeof(options) / sizeof(char*))

//surlignage
void print_colored(const char *text, int highlight) {
	if (highlight) {
        	printf("> \033[1;32m%s\033[0m <\n", text); // Texte vert si sélectionné
	} 
	else {
        	printf("  %s\n", text);
	}
}


void wait_for_enter() {
	printf("\n\nAppuie sur Entrée pour continuer..."); 
	getchar();
}

void tetris() { 
	system("clear");
	Joueur J = constru();
	jeu_tetris(&J);
	enregistrement_score(J);
}

void scoreboard() { //Afficher le scoreboard
	system("clear");
	printf(" Scoreboard\n\n");
	printf(" Pseudo  Score  Difficulte \n");
	FILE* fichier = NULL;
	fichier = fopen("scoreboard.txt","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (1);
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
		print_colored("===== MENU =====", 0);
		printf("\n");

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
		            		scoreboard();
		            		break;
		        	case 2:
		            		avantdessin();
		            		break;
		            	case 3:
		            		affichagepieces();
		            		break;
				case 4:
					system("clear");;
					print_colored("À bientôt !", 0);
					t = 0;
					break;
		    }
		}
	}

}

