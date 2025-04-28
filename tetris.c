#include "fichier.h"

//Procédure qui crée les tétrominos à partir du fichier pieces.txt
void creation_tetrominos(Tetromino *t){
    printf("Construction des Tétrominos...\n");
    if (t == NULL){
        exit(16);
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
void jeu_tetris(Joueur* J){
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
            reset_piece(liste_t+tour,liste_t[tour].nb_blocs);
            do{
                tour = rand()%NOMBRE_PIECES;
            }while(tour==tour_pre);
            tour_pre = tour;
        }
        if (game_over(tab_principal,liste_t+tour,liste_t[tour].nb_blocs)){
            
            break;
        }
        
    	n = key_input(); //On appelle key_input()
        //while(getchar()!='\n');
        if (n!=0){
            v = keyToVect(n);
            rotation(n,liste_t+tour,liste_t[tour].nb_blocs);
            place_t(liste_t+tour,tab_principal,v,liste_t[tour].nb_blocs);
            n=0;
        }else{
            place_t(liste_t+tour,tab_principal,d,liste_t[tour].nb_blocs);
        }
        
        draw(tab_principal,grille);
        for(int i = 0; i<LINE; i++){
            temp = scoreGrille(tab_principal[i]);
            
            if (temp){
                clear_line(tab_principal,i);
                p_ligne = i;
                J->score ++;
            }
            nombre_lignes+=temp;
            
        }
        gravitation(tab_principal,nombre_lignes,p_ligne);
        nombre_lignes = 0;
        refresh(grille, tab_principal);
        printf("\n\n Pseudo : %s   |   Score : %d \n",J->pseudo, J->score);
        sleep(1);
    }
    
    system("clear");
    printf("\nGAME OVER\n");
    wait_for_enter();
   
	
}
