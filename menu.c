#include "fichier.h"

//Coloration pour la sélection
void afficher_colore(const char *text, int surligner) {
	if (text == NULL){
		exit(10);
	}
	if (surligner) {
        	printf("             > \033[1;32m%s\033[0m <\n", text); // Texte vert si sélectionné
	} 
	else {
        	printf("              %s\n", text); //Texte normal sinon
	}
}

//Pause avant de changer de menu / sous-menu, on attend que le joueur appuie sur Entrée
void attendre_pour_entree() {
	int ch;
	printf("\n\nAppuie sur Entrée pour continuer..."); 
	do {
        	ch = getchar();
    	} while (ch != '\n' && ch != EOF);
}


//Lire la grille et le joueur sauvegardée dans le fichier sauvegarde.txt
void lecture_sauvegarde(FILE *fichier, char tab_char[LIGNE][COL+1], int tab_int[LIGNE][COL], Joueur* J){
	char c;
	int len;
	int verif = 0;
	if (fichier == NULL || tab_char == NULL || J== NULL){
		printf("Erreur : void lecture_sauvegarde !\n");
		exit(11);
	}
	rewind(fichier);
	for (int i = 0;i<LIGNE;i++){ 
		if (fgets(tab_char[i],COL+2,fichier) == NULL){     //COL + 2 permet de consommer le \n et laisse une case pour le \0
			printf("Erreur dans le fichier texte, la lecture d'une ligne de la grille n'a pas abouti. \n");
			exit(12);
		}
		len = strlen(tab_char[i]);
		if (len < COL || (tab_char[i][COL] != '\n' && tab_char[i][COL] != '\0')) {
        		printf("Erreur dans le fichier texte, la grille n'est pas correctement dessinée \n");
        		exit(13);
        	}
        	if (tab_char[i][len - 1] == '\n') {
        		tab_char[i][len - 1] = '\0';
    		}
    		for (int j = 0; j < COL; j++) {
    			if (tab_char[i][j] < '0' || tab_char[i][j] > '7') {
        			printf("Erreur dans la lecture, les valeurs récupérées ne sont pas correctes \n");
        			exit(14);
    			}
		}	
	}
	for (int i = 0; i <LIGNE;i++){
		for (int j = 0; j<COL;j++){
			if (tab_char[i][j] == '0'){
				tab_int[i][j] = 0;
			}
			else {
				switch(tab_char[i][j]){//Transforme le tableau de caractères récupéré plus tôt en tableau d'entiers représentant les blocs morts, les différentes valeurs indiquant les couleurs
		            		case '1':
				        	tab_int[i][j] = 14;
				        	break;
		          		case '2':
		                		tab_int[i][j] = 8;
		                		break;
		            		case '3':
		               			tab_int[i][j] = 9;
		                		break;
		            		case '4':
		                		tab_int[i][j] = 10;
		                		break;
		            		case '5':
		                		tab_int[i][j] = 11;
		                		break;
		            		case '6':
		                		tab_int[i][j] = 12;
		                		break;
		            		case '7':
		                		tab_int[i][j] = 13;
		                		break;
		        	}
			}
		}
	}
	if (fgetc(fichier) != '@'){
		printf("Erreur dans le fichier texte, mauvais séparateur \n");
		exit(15);
	}
	while((c=fgetc(fichier))!=EOF){ //Lecture des infos du joueur (pseudo, score et difficulté)
	        if(c=='#'){
	        	if ((fgets(J->pseudo,sizeof(J->pseudo),fichier)) != NULL && J->pseudo[0] != '\n'){// Lire la ligne.
	            		J->pseudo[strcspn(J->pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n		}
	            	}
	            	else {
	            		printf("Erreur dans la lecture du pseudo \n");
	            		exit(16);
	            	}
	            	verif ++;
	        }
	        else if (c=='&'){
	        	if (fscanf(fichier,"%d ",&J->score)!=1 || J->score >999999){
	        		printf("Erreur dans la lecture du score \n");
	            		exit(17);
	        	}
	        	verif ++;
	        }
	        else if (c=='/'){
	        	if (fscanf(fichier,"%d ",&J->difficulte) != 1 || J->difficulte < 0 || J->difficulte > 4){
	        		printf("Erreur dans la lecture de la difficulté \n");
	            		exit(18);
	        	}
	        	verif ++;
		}
    	}
    	if (verif != 3){ //Vérifie que les 3 informations du joueur soient bien présentes
			printf("Erreur dans la lecture du joueur\n");
	            	exit(19);
	}
}

//Sous-menu Rejouer, il récupère la sauvegarde contenue dans le fichier sauvegarde.txt
void sauvegarde(){
	char tab_char[LIGNE][COL+1];
	int tab_int [LIGNE][COL] ={0};
	Joueur J;
	system("clear");
	FILE* fichier = NULL;
	fichier = fopen("sauvegarde.txt","r");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (10);
	}
	if (fgetc(fichier) == EOF){ //Si le fichier est vide
		printf("\n\n Aucune sauvegarde detectee ! \n\n");
		attendre_pour_entree();
	}
	else { //Sinon on lit la sauvegarde et lance le jeu
		lecture_sauvegarde(fichier,tab_char,tab_int,&J);

		jeu_tetris(&J,tab_int);
		
		scoreboard(); //Affiche le score après la partie
	}
}

//Afficher le scoreboard
void scoreboard() { 
	system("clear");
	int c;
	FILE* fichier = NULL;
	fichier = fopen("scoreboard.txt","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (11);
	}
	rewind(fichier);
	c = fgetc(fichier);
	if (c=='0'){ //0 dans le scoreboard.txt signifie qu'il n'y a pas de score enregistré dans le fichier
		if ((c=fgetc(fichier)) != EOF){//Vérification du format du fichier, le 0 doit être tout seul dans le fichier
			printf("Erreur dans le fichier scoreboard !\n");
			exit(12);
		}
    	printf("\n     Il n'y a pas de score enregistré ! \n\n");
		
    }
	else { //Sinon on affiche le score des joueurs enregistrés
		printf("         ===== Scoreboard =====\n\n");
		printf("  Pseudo    |     Score    |  Difficulte \n");
		lire_scoreboard(fichier); 
	}
	fclose(fichier);
	attendre_pour_entree();
}

//Lancer le jeu tetris
void tetris() { 
	system("clear");
	int tab[LIGNE][COL]= {0};
	Joueur J = constru();
	jeu_tetris(&J,tab);//On lance le jeu avec un nouveau joueur
	scoreboard();
}

//Lance la procédure permettant de dessiner les pièces
void dessin() { 
	atelier();
}

//Affiche le règlement pour dessiner les pièces
void avantdessin() { 
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
	attendre_pour_entree();
	dessin();
}

//Sous-menu Pieces
void affichagepieces(){
	system("clear");
	printf("Voici les pieces avec lesquelles vous allez jouer !\n\n");
	char *** piecesactives=pieces();
	lecture(piecesactives,1); //Mettre les pièces contenues dans le fichier piecesmodifiees.txt dans triple pointeur 
	afficheliste(piecesactives); //Affiche chaque pièce
	liberer_pieces(piecesactives); //Libère l'espace mémoire alloué au triple pointeur
	attendre_pour_entree();
}

//Menu principal
void afficher_menu() {
	int selectionne = 0; //Savoir où se trouve le "curseur"
	int entree;
	int t = 1;
	const char *options[] = {"Jouer","Rejouer","Scoreboard","Atelier","Pieces","Quitter"};
	int num_options = (sizeof(options) / sizeof(char*));
	char*** pieces_dessinees = pieces();
	lecture(pieces_dessinees,0); //Mettre les pièces par défaut de Tetris contenues dans le fichier piecesdefauts.txt
	enregistrement(pieces_dessinees); //Enregistre les pièces par défaut dans le fichier piecesdmodifiees.txt
	liberer_pieces(pieces_dessinees);//Libère l'espace mémoire alloué au triple pointeur
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

		for (int i = 0; i < num_options; i++) { //Affiche les options du menu
		    afficher_colore(options[i], i == selectionne);
		}

		printf("\n\n\nUtilise Z (haut), S (bas), E (valider)\n");

		entree = saisir_entree();

		// Se déplacer
		if (entree == 'z' || entree == 'Z') { 
			selectionne = (selectionne - 1 + num_options) % num_options;
		} 
		else if (entree == 's' || entree == 'S') {
			selectionne = (selectionne + 1) % num_options;
		} 
		else if (entree == 'e' || entree == 'E') { //Selectionner
			switch (selectionne) {//Si le joueur valide, on lance l'une des procédures suivantes en fonction de selectionne
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
				case 5: //Dans ce cas on quitte le jeu et arrête le programme
					system("clear");
					printf("\n\n");
					afficher_colore("À bientôt !", 0);
					printf("\n\n");
					t = 0;
					break;
			}
		}
	}

}

