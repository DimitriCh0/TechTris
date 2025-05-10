#include "fichier.h"

void triInsertion(Joueur* tab, int taille) {
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

void lire_scoreboard(FILE *f){
    int variable;
    char ligne[100];
    Joueur J;
    rewind(f);
    while((variable=fgetc(f))!=EOF){
        if(variable=='#'){
            if ((fgets(J.pseudo,sizeof(J.pseudo),f)) != NULL){// Lire la ligne.
            	J.pseudo[strcspn(J.pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n
            	if (strlen(J.pseudo) > 7){
            		for (int i = 5; i <=8;i++){
            			if (i == 8){
            				J.pseudo[i] = '\0';
            			}
            			else{
            				J.pseudo[i] = '.';
            			}
            		}
            	}
            }
        }
        else if (variable=='&'){
            fscanf(f,"%d ",&J.score);
        }
        else if (variable=='/'){
            fscanf(f,"%d ",&J.difficulte);
            snprintf(ligne, sizeof(ligne), "%-10s  |  %6d pts  |       %d", J.pseudo, J.score, J.difficulte);
            printf("%s\n", ligne);
        }
	
        
    }
}


Joueur constru(){
    Joueur J;
    do{
	    system("clear");
	    printf("Entrez votre pseudo :\n");
	    scanf(" %s",J.pseudo);
	    if (strlen(J.pseudo) > 48){
	    	printf("Pseudo trop long ! \n");
	    	sleep(1);
	    }
	    while (getchar() != '\n');
    } while (strlen(J.pseudo) > 48);
    J.score=0;
    int retour;
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
   
void enregistrement_score(Joueur* J){
    if (J == NULL){
		printf("Pointeur NULL\n");
		exit (1);
    }
    FILE *f;
    int nbr_joueurs,variable;
    int k = 0;
    f=fopen("scoreboard.txt","a+");
    if (f == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (93);
    }
    if ((variable = fgetc(f))==EOF){
    	rewind(f);
	fprintf(f,"%d\n",1);
	fprintf(f,"Pseudo :#%s\n",J->pseudo);
	fprintf(f,"Score :&%d\n",J->score);
	fprintf(f,"Difficulte :/%d\n",J->difficulte);
    }
    else {
    	rewind(f);
	if (fscanf(f, "%d", &nbr_joueurs) != 1 || nbr_joueurs < 0) {
    		printf("Format invalide : nombre de joueurs incorrect.\n");
    		fclose(f);
    		exit(1);
	}	
	Joueur* tab = NULL;
	tab = malloc(sizeof(Joueur)*(nbr_joueurs+1));
	if (tab == NULL){
		printf("Allocation échoué !\n");
		exit (1);
	}
    	while((variable=fgetc(f))!=EOF){
		if(variable=='#'){
			if ((fgets((tab+k)->pseudo,sizeof((tab+k)->pseudo),f)) != NULL){// Lire la ligne.
			    (tab+k)->pseudo[strcspn((tab+k)->pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n
			}
		}
		else if (variable=='&'){
			fscanf(f,"%d ",&(tab+k)->score);
		}
		else if (variable=='/'){
			fscanf(f,"%d ",&(tab+k)->difficulte);
			k++;
		}
	}
   	*(tab+nbr_joueurs) = *J;
   	nbr_joueurs ++;
    	triInsertion(tab, nbr_joueurs);
    	f = freopen("scoreboard.txt", "w+", f);
	if (f == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (90);
	}
	fprintf(f,"%d\n",nbr_joueurs);
	for (int i = 0; i<nbr_joueurs;i++){
		fprintf(f,"Pseudo :#%s\n",(tab+i)->pseudo);
	    	fprintf(f,"Score :&%d\n",(tab+i)->score);
	    	fprintf(f,"Difficulte :/%d\n",(tab+i)->difficulte);
	}
	free(tab);
    }
    fclose(f);
    system("clear");

}



