#include "fichier.h"

//Naviguer dans les options du menu Pause
void afficher_colore_tetris(const char *texte, int surligner) { 
	if (texte == NULL){
		exit(60);
	}
	if (surligner) {
        	printf("         > \033[1;32m%s\033[0m < ", texte); // Texte vert si sélectionné
	} 
	else {
        	printf("         %s ", texte); //Si non selectionné
	}
}

void sleep_ms(float milliseconds){
	usleep(milliseconds * 1000);//Convertit les millisecondes en microsecondes
}

//Procédure qui crée les tétrominos à partir du fichier piecesmodifiees.txt
void creation_tetrominos(Tetromino *t){//Prend en argument le pointeur du tableau de tetromino, donc du premier tetromino
	printf("Construction des Tétrominos...\n");
	if (t == NULL){
		printf("Erreur : void creation_tetrominos ! \n");
		exit(61);
	}
	char ***liste = pieces();
	lecture(liste,1);
	for (int i = 0; i<NOMBRE_PIECES; i++){
		tetrominoConstructor(*(liste+i),t+i);
	}
	liberer_pieces(liste);
   
}
//Fonction qui a le rôle de vérifier si une ligne est pleine
int scoreGrille(int *tab){
	if (tab == NULL){
		printf("Erreur : int scoreGrille ! \n");
		exit(62);
	}
	int cpt=0;
	for(int i=0;i<COL;i++){
        	if(tab[i]>=8 && tab[i]<15){ 
            		cpt++;
        	}
            	if(cpt==COL){
                	return 1;
            	}
        }
	return 0;
}

//Incrémentation du score en fonction des lignes complétées et si la grille est totalement vide de blocs
void score(Joueur* J,int tab_principal[LIGNE][COL],int nb_lignes){
	if (tab_principal == NULL || J == NULL){
		printf("Erreur : void score ! \n");
		exit(63);
	}
	int effacer = 1; //Pour savoir si la grille est totalement vide (dans ce cas le score incrémenté est augmenté)
	for (int i = 0; i<LIGNE; i++){
		for (int j = 0; j<COL; j++){
			if (tab_principal[i][j] != 0){
				effacer = 0;
			}
		}
	}
	switch(nb_lignes){//Score différent en fonction du nombre de lignes complétées
			case 1 :
				if (effacer == 1){
					J->score +=800*J->difficulte;
				}
				J->score +=100*J->difficulte;
				break;
			case 2 :
				if (effacer == 1){
					J->score +=1200*J->difficulte;
				}
				J->score +=300*J->difficulte;	
				break;
			case 3 :
				if (effacer == 1){
					J->score +=1800*J->difficulte;
				}
				J->score +=500*J->difficulte;	
				break;
			case 4 :
				if (effacer == 1){
					J->score +=2000*J->difficulte;
				}
				J->score +=800*J->difficulte;	
				break;
			case 5 : //On peut au maximum avoir 5 lignes complétées à la fois
				if (effacer == 1){
					J->score +=2500*J->difficulte;
				}
				J->score +=1000*J->difficulte;	
				break;
	}
}

//Sous-menu Pause pour quitter ou faire une pause dans la partie, renvoie le statut "quitter" pour savoir si le jeu doit se stopper
int pause(){
	int selectionne = 0;
	int entree;
	int t = 1;
	int quitter;
	const char *options4[] = {"Quitter","Continuer"};
	int num_options4 = (sizeof(options4) / sizeof(char*));
	while (t) {
		system("clear");
		printf("\n\n\n");
		afficher_colore("===== Pause =====", 0);
		printf("\n");
		for (int i = 0; i < num_options4; i++) {
		    afficher_colore_tetris(options4[i], i == selectionne);
		}
		
		printf("\n\n\nD (droite), Q (gauche), E (valider)\n");

		entree = saisir_entree();
		
		if (entree == 'd' || entree == 'D') { 
			selectionne = (selectionne + 1)%num_options4;
		} 
		else if (entree == 'q' || entree == 'Q') {
			selectionne = (selectionne - 1 + num_options4)%num_options4;
		}  
		else if (entree == 'e' || entree == 'E') {
			switch (selectionne) {
				case 0:
					t=0;
					quitter = 1;
					break;
		        	case 1:
		            		t=0;
		            		quitter = 0;
		            		break;
		        }
		}
	}
	return quitter;
}

//Sauvegarde de la partie dans le fichier "sauvegarde.txt"
void enregistrement_partie(int tab[LIGNE][COL], Joueur* J){
	if (tab == NULL || J == NULL){
		printf("Erreur : void enregistrement_partie ! \n");
		exit(64);
	}
	char tab_char[LIGNE][COL+1]; 
	for (int i = 0; i <LIGNE;i++){ // Convertir le tableau de int en tableau de char
		for (int j = 0; j<COL+1;j++){
			if(j == COL){
				tab_char[i][j] = '\0';
			}
			else if (tab[i][j] == 0){
				tab_char[i][j] = '0';
			}
			else {
				switch(tab[i][j]%7+1){
		            		case 1:
				        	tab_char[i][j] = '1';
				        	break;
		          		case 2:
		                		tab_char[i][j] = '2';
		                		break;
		            		case 3:
		               			tab_char[i][j] = '3';
		                		break;
		            		case 4:
		                		tab_char[i][j] = '4';
		                		break;
		            		case 5:
		                		tab_char[i][j] = '5';
		                		break;
		            		case 6:
		                		tab_char[i][j] = '6';
		                		break;
		            		case 7:
		                		tab_char[i][j] = '7';
		                		break;
		        	}
			}	
		}
	}
	FILE *f;
	f=fopen("sauvegarde.txt","w+"); //'w+' écrase la dernière sauvegarde
	if (f == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (65);
	}
	for (int i = 0; i<LIGNE;i++){ //Ecriture ligne par ligne du tableau de char correspondant à la grille du Tetris
		fputs(tab_char[i],f);
		fputs("\n",f);
	}
	
	fprintf(f,"@\n"); // Séparateur
	fprintf(f,"#%s\n",J->pseudo); //Données du joueur
	fprintf(f,"&%d\n",J->score);
	fprintf(f,"/%d\n",J->difficulte);
	fclose(f);

}


//Exécution du code principal du jeu
void jeu_tetris(Joueur* J, int tab_principal[LIGNE][COL]){
	if (tab_principal == NULL || J == NULL){
		printf("Erreur : void jeu_tetris ! \n");
		exit(66);
	}
	struct timespec start, end;
    	char grille[LIGNE][COL][UTF]; //Grille qui va être affichée dans le terminal
    	int n; //Sortie de key_input()
    	int tour = rand()%NOMBRE_PIECES; //Valeur permettant de choisir la pièce à jouer
	int prochain_tour; //Indice du prochain tetromino
	int pre_tour; //Indice du tetromino précédent
    	int nb_lignes = 0; //Variable utilisée pour compter les lignes pleines
    	int p_ligne = LIGNE-1; //Première ligne pleine par défaut
    	int temp; //Variable temporaire
    	float speed = 1000; //Vitesse d'exécution du jeu
    	int quitter; //Booleen quitter
	int gv = 0; //Booleen du game over
	int montrer_pro_t = 0; //Booleen pour savoir si on affiche le prochain tetromino
    	Vecteur v; //Vecteur déplacement du joueur
    	Vecteur d; //Vecteur déplacement automatique à chaque période (vers le bas)
    	d.x = 1;
    	d.y = 0;
	
    	//printf("Sah Dimitri\n"); La première ligne de code qui a été écrite pour le projet

	Tetromino *liste_t; //Tableau contenant les tetromino à jouer
    	liste_t = malloc(NOMBRE_PIECES*sizeof(Tetromino));
    	if (liste_t == NULL){
        	exit(67);
    	}
	//Création des Tetrominos
    	creation_tetrominos(liste_t);
	//On choisit le prochain tetromino qui ne doit pas être le même que le précédent
	do{
        	prochain_tour = rand()%NOMBRE_PIECES;
    	}while(prochain_tour==tour);
    	while(1){
		clock_gettime(CLOCK_MONOTONIC, &start); //Pour que start et end n'est pas des valeurs non-déclarer
		clock_gettime(CLOCK_MONOTONIC, &end);
		long seconds = end.tv_sec - start.tv_sec; //On calcule la période en secondes et en nanosecondes
	    	long nanoseconds = end.tv_nsec - start.tv_nsec;
	    	long periode = seconds * 1000 + nanoseconds / 1000000;
		//Fonctionnement du jeu : à chaque niveau de difficulté est associé une période de temps en millisecondes
		//Pendant cette période, le joueur peut faire ce qu'il veut (bouger la pièce, la tourner, etc), mais à la fin de chaque période le tétromino descendra forcément de 1 case
		while(periode<speed/J->difficulte){
			if (!(liste_t[tour].enVie)){ //Quand la pièce actuelle est arrivée en bas, on change de pièce aléatoirement dans la liste_t en veillant à ce qu'elle ne soit pas identique à la précédente
		    		reinitialiser_piece(liste_t+tour,liste_t[tour].nb_blocs);

				pre_tour = tour;

				tour = prochain_tour;
				//On choisit le prochain tetromino qui ne doit pas être le même que le précédent
			    	do{
					prochain_tour = rand()%NOMBRE_PIECES;
			    	}while(prochain_tour==tour || prochain_tour == pre_tour);
		    		
			}
	       
			
	   		n = entree_clavier(); //On appelle key_input() pour savoir si le joueur a appuyé sur une touche	
			if (game_over(tab_principal,liste_t+tour,liste_t[tour].nb_blocs,tour+1)){ //On appelle la fonction qui vérifie si le jeu est toujours valide
				gv = 1;
				break;
			}
		    	if (n==8){ // Pause
		    		quitter = pause();
		    		if (quitter){
		    			break;
		    		}
		    	}
			//Condition changeant la valeur de montrer_pro_t de 0 à 1 ou vice-versa
			else if(n==9){
				montrer_pro_t = !montrer_pro_t;
				n=0;
			}
			else if (n == 10){ //Touche espace appuyé, descente direct
				v.x = 1;
				v.y = 0;
				while (liste_t[tour].enVie){  //Tant que la pièce est vivante
					place_t(liste_t+tour,tab_principal,v,liste_t[tour].nb_blocs, tour+1);
					J->score +=2;
					dessiner(tab_principal,grille);
					actualiser(grille, tab_principal,J,liste_t+prochain_tour, montrer_pro_t, prochain_tour+1);
					nb_lignes = 0;
					enregistrement_partie(tab_principal,J);
				}
				n=0;
			}
			else if (n!=0){ //rotation ou descente de 1
				v = conversion_entree_vecteur(n);
				rotation(n,liste_t+tour,liste_t[tour].nb_blocs,tab_principal);
				place_t(liste_t+tour,tab_principal,v,liste_t[tour].nb_blocs, tour+1);
				if (n==4){
					J->score +=2;
				}
				n=0;
				dessiner(tab_principal,grille);
				actualiser(grille, tab_principal,J,liste_t+prochain_tour, montrer_pro_t, prochain_tour+1);
				nb_lignes = 0;
				enregistrement_partie(tab_principal,J);
			}
			clock_gettime(CLOCK_MONOTONIC, &end);
			seconds = end.tv_sec - start.tv_sec;
		    	nanoseconds = end.tv_nsec - start.tv_nsec;
		    	periode = seconds * 1000 + nanoseconds / 1000000;
			sleep_ms(30);
		}
		
		if (n==8){ // Pause
			quitter = pause();
			if (quitter){
				break;
			}
		}
		J->score ++;
		place_t(liste_t+tour,tab_principal,d,liste_t[tour].nb_blocs, tour+1);
		
	
		for(int i = 0; i<LIGNE; i++){
			temp = scoreGrille(tab_principal[i]); //On vérifie si une ligne est pleine
			if (temp){
				effacer_ligne(tab_principal,i); //Si c'est le cas, on supprime la ligne en question
				p_ligne = i;
				gravitation(tab_principal,1,p_ligne); //On fait descendre toutes les lignes qui n'ont pas été suprimées
			}
			nb_lignes+=temp; //On additionne temp afin de savoir le nombre de lignes supprimées
			
		}
		dessiner(tab_principal,grille);
		actualiser(grille, tab_principal,J,liste_t+prochain_tour,montrer_pro_t,prochain_tour+1);
		score(J,tab_principal,nb_lignes);

		nb_lignes = 0;
		enregistrement_partie(tab_principal,J);
		if (gv || game_over(tab_principal,liste_t+tour,liste_t[tour].nb_blocs,tour+1)){ //On vérifie si le jeu n'est pas terminé (quand les pièces atteignent le haut de la grille)
			dessiner(tab_principal,grille);
			actualiser(grille, tab_principal,J,liste_t+prochain_tour,montrer_pro_t, prochain_tour+1);
			sleep_ms(100);
			enregistrement_score(J);
			FILE *f;
			f=fopen("sauvegarde.txt","w+"); //'w+' écrase la dernière sauvegarde
			if (f == NULL){
				printf("Ouverture du fichier impossible pour la sauvegarde \n");
				printf("Code erreur = %d \n", errno);
				printf("Message erreur = %s \n", strerror(errno));
				exit (68);
			}
			fclose(f);
			system("clear");
			printf("\nGAME OVER\n");
			break;
		}
	}
    
	free(liste_t);
	attendre_pour_entree();
    
}
