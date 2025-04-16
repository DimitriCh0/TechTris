#include "inclu.h"

int scoreGrille(char tab[]){
    int cpt=0;
    for(int i=0;i<Taille;i++){
        if(tab[i]=='2'){ 
            cpt++;
        }
            if(cpt==Taille){
                return 1;
            }
        }
    return 0;
}

void incrementer(char tab[],Joueur J){
    int c=0;
    int Val=scoreGrille(tab);
    printf("%d\n",Val);
    if(Val==1){  // Verifie qu'on a bien une ligne de 2.
        FILE *f;
        f=fopen("Nom.txt","w+");
        if(f==NULL){
            perror("Erreur d'ouverture  du fihcier");
            exit(10);
        }
        while(c=fgetc(f)!=EOF){
            if(c=='&'){
                J.score++;
                fprintf(f,"%d",J.score);
            }
        }
    }
}

Joueur construBase(){
    Joueur J;
    J.score=0;
    strcpy(J.Pseudo, "Wenox");
    J.difficulte=2;
    return J;
}
int main(){
    char tab[Taille]={'2','2','2','2','2','2','2','2','2','2'};
    Joueur J;
    J=construBase();
    incrementer(tab,J);
    return 1;
}