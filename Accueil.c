#include <stdio.h>
#include <string.h>

typedef struct{
    char Pseudo[50];
    int score;
}Joueur;

void Read(FILE *f){
    int variable;
    Joueur J;
    rewind(f);
    while((variable=fgetc(f))!=EOF){
        if(variable=='#'){
            fgets(J.Pseudo,sizeof(J.Pseudo),f); // Lire la ligne.
            J.Pseudo[strcspn(J.Pseudo,"\n")]='\0'; // Remplace le \n en \0 donc il retire \n
            printf("Votre pseudo : %s\n",J.Pseudo);
        }
        if (variable=='&'){
            fscanf(f,"%d",&J.score);
            printf("Votre score est de : %d\n",J.score);
        }
    }
}


Joueur constru(){
    Joueur J;
    printf("Entrer votre pseudo :\n");
    scanf(" %s",J.Pseudo);
    J.score=0;
    FILE *f;
    f=fopen("Nom.txt","w+");
    fprintf(f,"Pseudo :#");
    fprintf(f,"%s\n",J.Pseudo);
    fprintf(f,"Score :&");
    fprintf(f,"%d",J.score);
    Read(f);
    fclose(f);
    return J;

}

int  main(){
    Joueur J;
    J=constru();
    return 0;
}