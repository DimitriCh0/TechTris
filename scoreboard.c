#include "fichier.h"

//Tri par insertion pour trier le scoreboard (chaque appel, le tableau est trié excepté le dernier Joueur, il suffit de l'insérer au bonne endroit pour que le tableau soit trier)
void triInsertion(Joueur* tab, int taille) {
	if (tab==NULL || taille<0){
        	printf("Erreur : void triInsertion \n");
        	exit(40);
    	}
	int i, j;
	Joueur temp;
	for (i = 1; i < taille; i++) {
        	temp = tab[i];
        	j = i - 1;
        	while (j >= 0 && tab[j].score < temp.score) { 
            		tab[j + 1] = tab[j];
            		j--;
        	}
        	tab[j + 1] = temp;
    	}
}

//Lire le fichier "scoreboard.txt" et afficher les scores dans le sous-menu "Scoreboard"
void lire_scoreboard(FILE *f){
	if (f==NULL){
        	printf("Erreur : void lire_scoreboard \n");
        	exit(41);
    	}
	int c;
    	char ligne[100];
    	char pseudo_short[10];
    	int nbr_joueurs;
    	int compteur_p = 0;
    	int compteur_s = 0;
    	int compteur_d = 0;
    	Joueur J;
    	rewind(f);
    	if (fscanf(f, "%d", &nbr_joueurs) != 1 || nbr_joueurs < 0) {
	    		printf("Format invalide : nombre de joueurs incorrect.\n");
	    		fclose(f);
	    		exit(42);
	}	
	while((c=fgetc(f))!=EOF){
	        if(c=='#'){//Vérification du pseudo
	        	if ((fgets(J.pseudo,sizeof(J.pseudo),f)) != NULL && J.pseudo[0] != '\n'){// Lire la ligne.
	            		J.pseudo[strcspn(J.pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n
	            		if (strlen(J.pseudo) > 10){ //Si le pseudo est légèrement long, il est tronqué pour assurer un bon affichage
	            			strncpy(pseudo_short,J.pseudo,5); //Copie les 5 premiers caractères
	            			strcpy(pseudo_short+5,"..."); //Ajoute les 3 petits points
	            			pseudo_short[9] = '\0'; 
	            			strcpy(J.pseudo,pseudo_short); //Remplace le pseudo entier par celui tronqué
	            		}
	            		compteur_p ++;
	            	}
	            	else {
	            		printf("Erreur dans la lecture du pseudo \n");
	            		exit(43);
	            	}
	        }
	        else if (c=='&'){//Vérification du score
	        	if (fscanf(f,"%d ",&J.score)!=1 || J.score >999999){
	        		printf("Erreur dans la lecture du score \n");
	            		exit(44);
	        	}
	        	compteur_s ++;
	        }
	        else if (c=='/'){//Vérification de la difficulté
	        	if (fscanf(f,"%d ",&J.difficulte) != 1 || J.difficulte < 0 || J.difficulte > 4){
	        		printf("Erreur dans la lecture de la difficulté \n");
	            		exit(45);
	        	}
	        	snprintf(ligne, sizeof(ligne), "%-10s  |  %6d pts  |       %d", J.pseudo, J.score, J.difficulte); //Ecrit une chaine de caractère avec un nombre défini de caractère, affichant le score avec un pseudo ne dépassant pas 10 caractères (si inférieur à 10, rajoute des espaces à droite), un score de 6 chiffres maximum
	        	printf("%s\n", ligne);
	        	compteur_d ++;
	        }
	        
	}
	if (nbr_joueurs != compteur_d || nbr_joueurs != compteur_p || nbr_joueurs != compteur_s){//Vérifie si les compteurs de pseudo, de score et de difficulté sont égaux au nombre de joueur indiqué au début du fichier scoreboard.txt
		printf("Erreur dans la lecture des joueurs : voir fichier texte \n");
	        exit(46);
	}
}

//Création du joueur, son pseudo et sa difficulté
Joueur constru(){
	int retour;
    	Joueur J;
    	do{
		system("clear");
		printf("Entrez votre pseudo (max 50 caractères):\n");
		if (scanf(" %50s",J.pseudo)!=1|| strlen(J.pseudo) == 0||J.pseudo[0] == 27||(J.pseudo[0] == 27 && J.pseudo[1] == '[')){            //Le pseudo sera automatiquement tronqué s'il dépasse 50 caractères et les séquences comme Echap ou les flèches ne sont pas valides
	    		printf("Pseudo invalide \n");
	    		J.pseudo[0] ='\0';
	    		sleep(1);
	    	}
	    	while (getchar() != '\n' );
	} while (strlen(J.pseudo)==0);
    	J.score=0;
    	do {
		system("clear");
		printf("Entrez la difficulte (1, 2, 3 ou 4) :\n");
		retour = scanf(" %d", &J.difficulte);
		if (retour != 1 || J.difficulte < 1 || J.difficulte > 4) {
			printf("La valeur saisie est incorrecte.\n");
			sleep(1);
			while (getchar() != '\n'); //vider le scanf qui pourrait provoquer une boucle infinie si on saisit n'importe quoi
	   	}
	} while (retour != 1 || J.difficulte < 1 || J.difficulte > 4);
	while (getchar() != '\n');
	return J;
}

//Enregistrement du score du Joueur dans le fichier "scoreboard.txt" 
void enregistrement_score(Joueur* J){
	if (J == NULL){
		printf("Erreur : void enregistrement\n");
		exit (47);
	}
	FILE *f;
	int nbr_joueurs,c;
	int k = 0;
	int compteur_p = 0;
    	int compteur_s = 0;
    	int compteur_d = 0;
	f=fopen("scoreboard.txt","a+");
	if (f == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (48);
    	}
	if ((c = fgetc(f))==EOF){ //Si le fichier "scoreboard.txt" est vide de données
	    	rewind(f);
		fprintf(f,"%d\n",1);
		fprintf(f,"Pseudo :#%s\n",J->pseudo);
		fprintf(f,"Score :&%d\n",J->score);
		fprintf(f,"Difficulte :/%d\n",J->difficulte);
    	}
    	else { //Créer un tableau contenant les joueurs, formate le fichier, trie les joueurs dans le tableau selon leur score, réinscrit les joueurs dans le fichier "scoreboard.txt"
	    	rewind(f);
		if (fscanf(f, "%d", &nbr_joueurs) != 1 || nbr_joueurs < 0) {
	    		printf("Format invalide : nombre de joueurs incorrect.\n");
	    		fclose(f);
	    		exit(49);
		}	
		Joueur* tab = NULL;
		tab = malloc(sizeof(Joueur)*(nbr_joueurs+1));
		if (tab == NULL){
			printf("Allocation échoué !\n");
			exit (40);
		}
	    	while((c=fgetc(f))!=EOF){ //Lit les joueurs du scoreboard et les stocke dans le tableau de Joueur
			if(c=='#'){
				if ((fgets((tab+k)->pseudo,sizeof((tab+k)->pseudo),f)) != NULL && (tab+k)->pseudo[0] != '\n'){// Lire la ligne.
					(tab+k)->pseudo[strcspn((tab+k)->pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n
				}
				else {
	            			printf("Erreur dans la lecture du pseudo \n");
	            			exit(41);
	            		}
	            		compteur_p ++;
			}
			else if (c=='&'){
				if (fscanf(f,"%d ",&(tab+k)->score)!=1 || J->score >999999){
	        			printf("Erreur dans la lecture du score \n");
	            			exit(42);
	        		}
	        		compteur_s ++;
			}
			else if (c=='/'){
				if (fscanf(f,"%d ",&(tab+k)->difficulte) != 1 || J->difficulte < 0 || J->difficulte > 4){
	        			printf("Erreur dans la lecture de la difficulté \n");
	            			exit(43);
	        		}
	        		compteur_d ++;
				k++;
			}
		}
		if (nbr_joueurs != compteur_d || nbr_joueurs != compteur_p || nbr_joueurs != compteur_s){//Voir plus haut la vérification
			printf("Erreur dans la lecture des joueurs : voir fichier texte \n");
	        	exit(44);
		}
	   	*(tab+nbr_joueurs) = *J;
	   	nbr_joueurs ++;
	    	triInsertion(tab, nbr_joueurs); //Trie les joueurs dans l'ordre décroissant des scores 
	    	f = freopen("scoreboard.txt", "w+", f); //Réouvre le fichier selon "w+" et non "a+"
		if (f == NULL){
			printf("Ouverture du fichier impossible \n");
			printf("Code erreur = %d \n", errno);
			printf("Message erreur = %s \n", strerror(errno));
			exit (45);
		}
		fprintf(f,"%d\n",nbr_joueurs); //On écrit le nouveau nombre de joueurs au début du fichier
		for (int i = 0; i<nbr_joueurs;i++){ //Ecriture des joueurs dans le fichier "scoreboard.txt"
			fprintf(f,"Pseudo :#%s\n",(tab+i)->pseudo);
		    	fprintf(f,"Score :&%d\n",(tab+i)->score);
		    	fprintf(f,"Difficulte :/%d\n",(tab+i)->difficulte);
		}
		free(tab);
	}
    	fclose(f);
    	system("clear");
}
