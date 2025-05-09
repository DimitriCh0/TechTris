#include "fichier.h"


void print_colored3(const char *text, int highlight) { //Naviguer dans les options sous la grille
	if (highlight) {
        	printf("         > \033[1;32m%s\033[0m < ", text); // Texte vert si sélectionné
	} 
	else {
        	printf("         %s ", text);
	}
}

void sleep_ms(float milliseconds)
{
    //Convertit les millisecondes en microsecondes
    usleep(milliseconds * 1000);
}
//Procédure qui crée les tétrominos à partir du fichier pieces.txt ou piecedited
void creation_tetrominos(Tetromino *t){
	printf("Construction des Tétrominos...\n");
	if (t == NULL){
		exit(60);
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

void score(Joueur* J,int tab_principal[LINE][COL],int nb_lines){
	int clear = 1;
	for (int i = 0; i<LINE; i++){
		for (int j = 0; j<COL; j++){
			if (tab_principal[i][j] != 0){
				clear = 0;
			}
		}
	}
	switch(nb_lines){
			case 1 :
				if (clear == 1){
					J->score +=800*J->difficulte;
				}
				J->score +=100*J->difficulte;
				break;
			case 2 :
				if (clear == 1){
					J->score +=1200*J->difficulte;
				}
				J->score +=300*J->difficulte;	
				break;
			case 3 :
				if (clear == 1){
					J->score +=1800*J->difficulte;
				}
				J->score +=500*J->difficulte;	
				break;
			case 4 :
				if (clear == 1){
					J->score +=2000*J->difficulte;
				}
				J->score +=800*J->difficulte;	
				break;
			case 5 :
				if (clear == 1){
					J->score +=2500*J->difficulte;
				}
				J->score +=1000*J->difficulte;	
				break;
	}
}

int pause(){
	int selected = 0;
	int input;
	int t = 1;
	int quit;
	const char *options4[] = {"Quitter","Continuer"};
	int num_options4 = (sizeof(options4) / sizeof(char*));
	while (t) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== Pause =====", 0);
		printf("\n");
		for (int i = 0; i < num_options4; i++) {
		    print_colored3(options4[i], i == selected);
		}
		
		printf("\n\n\nD (droite), Q (gauche), E (valider)\n");

		input = get_input();
		
		if (input == 'd' || input == 'D') { //Probleme : quand fleche gauche appuyé
			selected = (selected + 1)%num_options4;
		} 
		else if (input == 'q' || input == 'Q') {
			selected = (selected - 1 + num_options4)%num_options4;
		}  
		else if (input == 'e' || input == 'E') {
			switch (selected) {
				case 0:
					t=0;
					quit = 1;
					break;
		        	case 1:
		            		t=0;
		            		quit = 0;
		            		break;
		        }
		}
	}
	return quit;
}

void enregistrement_partie(int tab[LINE][COL], Joueur* J){
	if (tab == NULL || J == NULL){
		exit(61);
	}
	char tab_char[LINE][COL+1];
	for (int i = 0; i <LINE;i++){
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
		exit (62);
	}
	for (int i = 0; i<LINE;i++){
		fputs(tab_char[i],f);
		fputs("\n",f);
	}
	
	fprintf(f,"@\n");
	fprintf(f,"#%s\n",J->pseudo);
	fprintf(f,"&%d\n",J->score);
	fprintf(f,"/%d\n",J->difficulte);
	fclose(f);

}


//Exécution du code principal du jeu
void jeu_tetris(Joueur* J, int tab_principal[LINE][COL],int sauvegarde){
	struct timespec start, end;
    	char grille[LINE][COL][UTF];
    	int n; //Sortie de key_input()
    	int tour = rand()%NOMBRE_PIECES; //Valeur permettant de choisir la pièce à jouer
	int next_tour; //Valeur désignant la prochaine pièce à jouer
	int pre_tour;
    	int nb_lines = 0; //Variable utilisée pour compter les lignes pleines
    	int p_ligne = LINE-1; //Première ligne pleine par défaut
    	int temp; //Variable temporaire
    	float speed = 1000; //Vitesse d'exécution du jeu
    	int quit;
	int gv = 0;
	int show_next_t = 0;
    	Vecteur v;
    	Vecteur d;
    	d.x = 1;
    	d.y = 0;
	
    	printf("Sah Dimitri\n");

	Tetromino *liste_t;
    	liste_t = malloc(NOMBRE_PIECES*sizeof(Tetromino));
    	if (liste_t == NULL){
        	exit(63);
    	}
	//Création des Tetrominos
    	creation_tetrominos(liste_t);
	//On choisit le prochain tetromino qui ne doit pas être le même que le précédent
	do{
        	next_tour = rand()%NOMBRE_PIECES;
    	}while(next_tour==tour);
    	while(1){
		clock_gettime(CLOCK_MONOTONIC, &start);
		clock_gettime(CLOCK_MONOTONIC, &end);
		long seconds = end.tv_sec - start.tv_sec;
	    	long nanoseconds = end.tv_nsec - start.tv_nsec;
	    	long period = seconds * 1000 + nanoseconds / 1000000;
		//Fonctionnement du jeu : à chaque niveau de difficulté est associé une période de temps en millisecondes
		//Pendant cette période, le joueur peut faire ce qu'il veut (bouger la pièce, la tourner, etc), mais à la fin de chaque période le tétromino descendra forcément de 1 case
		while(period<speed/J->difficulte){
			if (!(liste_t[tour].isalive)){ //Quand la pièce actuelle est arrivée en bas, on change de pièce aléatoirement dans la liste_t en veillant à ce qu'elle ne soit pas identique à la précédente
		    		reset_piece(liste_t+tour,liste_t[tour].nb_blocs);

				pre_tour = tour;

				tour = next_tour;
				//On choisit le prochain tetromino qui ne doit pas être le même que le précédent
			    	do{
					next_tour = rand()%NOMBRE_PIECES;
			    	}while(next_tour==tour || next_tour == pre_tour);
		    		
			}
	       
			
	   		n = key_input(); //On appelle key_input() pour savoir si le joueur a appuyé sur une touche	
			if (game_over(tab_principal,liste_t+tour,liste_t[tour].nb_blocs,tour+1)){ //On appelle la fonction qui vérifie si le jeu est toujours valide
				gv = 1;
				break;
			}
		    	if (n==8){
		    		quit = pause();
		    		if (quit){
		    			break;
		    		}
		    	}
			//Condition changeant la valeur de show_next_t de 0 à 1 ou vice-versa
			else if(n==9){
				show_next_t = !show_next_t;
				n=0;
			}
			else if (n == 10){ //Touche espace appuyé, descente direct
				v.x = 1;
				v.y = 0;
				while (liste_t[tour].isalive){  //Tant que la pièce est vivante
					place_t(liste_t+tour,tab_principal,v,liste_t[tour].nb_blocs, tour+1);
					J->score +=2;
					draw(tab_principal,grille);
					refresh(grille, tab_principal,J,liste_t+next_tour, show_next_t);
					nb_lines = 0;
					enregistrement_partie(tab_principal,J);
				}
				n=0;
			}
			else if (n!=0){ //rotation ou descente de 1
				v = keyToVect(n);
				rotation(n,liste_t+tour,liste_t[tour].nb_blocs,tab_principal);
				place_t(liste_t+tour,tab_principal,v,liste_t[tour].nb_blocs, tour+1);
				if (n==4){
					J->score +=2;
				}
				n=0;
				draw(tab_principal,grille);
				refresh(grille, tab_principal,J,liste_t+next_tour, show_next_t);
				nb_lines = 0;
				enregistrement_partie(tab_principal,J);
			}
			clock_gettime(CLOCK_MONOTONIC, &end);
			seconds = end.tv_sec - start.tv_sec;
		    	nanoseconds = end.tv_nsec - start.tv_nsec;
		    	period = seconds * 1000 + nanoseconds / 1000000;
			sleep_ms(30);
		}
		
		if (n==8){
			if (quit){
				break;
			}
		}
		J->score ++;
		place_t(liste_t+tour,tab_principal,d,liste_t[tour].nb_blocs, tour+1);
		
	
		for(int i = 0; i<LINE; i++){
			temp = scoreGrille(tab_principal[i]); //On vérifie si une ligne est pleine
			if (temp){
				clear_line(tab_principal,i); //Si c'est le cas, on supprime la ligne en question
				p_ligne = i;
				gravitation(tab_principal,1,p_ligne); //On fait descendre toutes les lignes qui n'ont pas été suprimées
			}
			nb_lines+=temp; //On additionne temp afin de savoir le nombre de lignes supprimées
			
		}
		draw(tab_principal,grille);
		refresh(grille, tab_principal,J,liste_t+next_tour,show_next_t);
		score(J,tab_principal,nb_lines);

		nb_lines = 0;
		enregistrement_partie(tab_principal,J);
		if (gv || game_over(tab_principal,liste_t+tour,liste_t[tour].nb_blocs,tour+1)){ //On vérifie si le jeu n'est pas terminé (quand les pièces atteignent le haut de la grille)
			draw(tab_principal,grille);
			refresh(grille, tab_principal,J,liste_t+next_tour,show_next_t);
			sleep_ms(100);
			enregistrement_score(J);
			FILE *f;
			f=fopen("sauvegarde.txt","w+"); //'w+' écrase la dernière sauvegarde
			if (f == NULL){
				printf("Ouverture du fichier impossible pour la sauvegarde \n");
				printf("Code erreur = %d \n", errno);
				printf("Message erreur = %s \n", strerror(errno));
				exit (64);
			}
			fclose(f);
			system("clear");
			printf("\nGAME OVER\n");
			break;
		}
	}
    
    free(liste_t);
    wait_for_enter();
    
}
