#include "fichier.h"

//Procédure qui crée les tétrominos à partir du fichier pieces.txt
void creation_tetrominos(Tetromino *t){
    printf("Construction des Tétrominos...\n");
    if (t == NULL){
        exit(16);
    }
    char ***liste = pieces();
    for (int i = 0; i<NOMBRE_PIECES; i++){
        tetrominoConstructor(*(liste+i),t+i);
    }
    free(liste);
   
}
//Fonction qui a le rôle de vérifier si une ligne est pleine
int scoreGrille(int *tab){
    int cpt=0;
    for(int i=0;i<COL;i++){
        if(tab[i]==2){ 
            cpt++;
        }
            if(cpt==COL){
                return 1;
            }
        }
    return 0;
}

//Exécution du code principal du jeu
void jeu_tetris(){
    int tab_principal[LINE][COL] = {0};
    char grille[LINE][COL];
    int n;
    int tour = rand()%NOMBRE_PIECES;
    int tour_pre = tour;
    int nombre_lignes = 0;
    int p_ligne = LINE-1;
    int temp;
    Vecteur v;
    Vecteur d;
    d.x = 1;
    d.y = 0;

    printf("Sah Dimitri\n");

	Tetromino *liste_t;
    liste_t = malloc(NOMBRE_PIECES*sizeof(Tetromino));
    if (liste_t == NULL){
        exit(15);
    }
    creation_tetrominos(liste_t);
    while(1){
        
        
        if (!(liste_t[tour].isalive)){
            reset_piece(liste_t+tour);
            do{
                tour = rand()%NOMBRE_PIECES;
            }while(tour==tour_pre);
            tour_pre = tour;
        }
        if (game_over(tab_principal,liste_t+tour)){
            
            break;
        }
        
    	n = key_input(); //On appelle key_input()
        
        if (n!=0){
            v = keyToVect(n);
            rotation(n,liste_t+tour);
            place_t(liste_t+tour,tab_principal,v);
            n=0;
        }else{
            place_t(liste_t+tour,tab_principal,d);
        }
        
        draw(tab_principal,grille);
        for(int i = 0; i<LINE; i++){
            temp = scoreGrille(tab_principal+i);
            
            if (temp){
                clear_line(tab_principal,i);
                p_ligne = i;
            }
            nombre_lignes+=temp;
            
        }
        gravitation(tab_principal,nombre_lignes,p_ligne);
        nombre_lignes = 0;
        refresh(grille, tab_principal);
        
        sleep(1);
    }
    
    system("clear");
    printf("\nGAME OVER\n");
    wait_for_enter();
    free(liste_t);
	
}