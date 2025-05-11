//Structures
//Vecteur permettant le déplacement des tétrominos
typedef struct{
    int x;
    int y;
}Vecteur;

//Structure du tétromino comprenant un double tableau contenant les coordonnées de chaque bloc du tétromino
//et un boolean vérifiant si le tétromino a touché le sol ou non, il vaut 1 jusqu'à ce que le tétromino a atteint le sol
typedef struct{
    int blocs[5][2];
    int enVie;
    int nb_blocs;

}Tetromino;

//Structure d'un joueur
typedef struct{
    char pseudo[51];
    int score;
    int difficulte;
}Joueur;

