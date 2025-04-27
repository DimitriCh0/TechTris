#include "fichier.h"

void lire_scoreboard(FILE *f){
    int variable;
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
           	printf("\n %s  ",J.pseudo);
            }
        }
        else if (variable=='&'){
            fscanf(f,"%d ",&J.score);
            printf("%d  ",J.score);
        }
        else if (variable=='/'){
            fscanf(f,"%d ",&J.difficulte);
            printf("  %d\n",J.difficulte);
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
    FILE *f;
    f=fopen("scoreboard.txt","a+");
    if (f == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (1);
    }
    fprintf(f,"Pseudo :#%s\n",J.pseudo);
    fprintf(f,"Score :&%d\n",J.score);
    fprintf(f,"Difficulte :/%d\n",J.difficulte);
    fclose(f);
    system("clear");
    return J;

}




/*void incrementer(char tab[],Joueur J){
    int c;
    int Val=scoreGrille(tab);
    if(Val==1){  // Verifie qu'on a bien une ligne de 2.
        FILE *f;
        f=fopen("scoreboard.txt","r+");
        if(f==NULL){
            perror("Erreur d'ouverture  du fichier");
            exit(10);
        }
        while((c=fgetc(f))!=EOF){
            if(c=='&'){
                J.score++;
                fprintf(f,"%d",J.score);
            }
        }
        fclose(f);
    }
}
*/    



