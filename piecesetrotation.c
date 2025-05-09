#include "fichier.h"

//une pièce est définie comme : '1' = bloc et '0' = vide

char*** pieces(){ //procedure qui crée un tableau utilisé pour la lecture des pieces dans le jeu
	char*** liste_pieces = NULL;
	liste_pieces = malloc(NOMBRE_PIECES*sizeof(char**)); 		//Créer le tableau qui contiendra chaque pièce (une pièce étant un tableau a 2 dimensions)
	if (liste_pieces == NULL){
		exit(10);
	}
	for (int i = 0;i<NOMBRE_PIECES;i++){
		*(liste_pieces+i) = malloc(DIM*sizeof(char*)); 		//Créer les tableaux qui contiendront les chaines de caractères correspondant à chaque ligne qui forme une pièce (5 lignes)
		if (*(liste_pieces+i) == NULL){
			exit(10);
		}
		for (int j = 0; j<DIM;j++){
			*(*(liste_pieces+i)+j) = malloc((DIM+1)*sizeof(char)); 		//Créer les chaines de caractères qui contiendront les pièces ligne par ligne + (DIM+1) pour contenir '\0'
			if (*(*(liste_pieces+i)+j) == NULL){
				exit(10);
			}
		}
	}
	return liste_pieces;
}

void lecture(char*** liste_pieces,int var){
	FILE* fichier = NULL;
	if (var){
		fichier = fopen("piecesedited.txt","r+");
	}
	else{
		fichier = fopen("piecesdefault.txt","r+");
	}
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		printf("Code erreur = %d \n", errno);
		printf("Message erreur = %s \n", strerror(errno));
		exit (1);
	}
	
	//Cette partie du code nécessite que le fichier texte contenant les pièces est une forme bien spécifique !!!
	for (int i = 0;i<NOMBRE_PIECES;i++){ 		//récupère pièce par pièce
		for (int j = 0; j<DIM;j++){ 			//récupère ligne par ligne les pièces qui se trouvent dans le fichier texte dans le tableau liste_pieces
			if (fgets(liste_pieces[i][j],DIM+1,fichier) == NULL){
				printf("Erreur dans le fichier texte, la lecture d'une ligne de la piece n'a pas abouti. \n");
				exit(1);
			}
			fgetc(fichier); 					//passer le '\n' aprés chaque ligne 
		}
		if (fgetc(fichier) != '#'){
			printf("Erreur dans le fichier texte, le separateur n'est pas correcte. \n");
			exit(1);
		}  										//passer le '#' qui est le séparateur de pièce
		fgetc(fichier);  						//passer le '\n' après le '#'
	}
	for (int i = 0; i <NOMBRE_PIECES;i++){
		for (int j = 0; j<DIM;j++){ 
			for (int k = 0; k<DIM;k++){ 
				if (liste_pieces[i][j][k] != '1' && liste_pieces[i][j][k] != '0'){
					printf("Erreur dans le fichier texte, le format n'est pas respecté \n");
					exit(1);
				}
			}
		}
	}
	fclose(fichier);
	
}

void liberer_pieces(char*** liste_pieces){
	if (liste_pieces == NULL){
		return;
	}
	for (int i = 0; i < NOMBRE_PIECES; i++) {
        if (liste_pieces[i] != NULL) {
            for (int j = 0; j < DIM; j++) {
                if (liste_pieces[i][j] != NULL) {
                    free(liste_pieces[i][j]); // Libérer chaque ligne
                }
            }
            free(liste_pieces[i]); // Libérer le tableau de lignes
        }
    }
    free(liste_pieces); // Libérer le tableau des pièces
}

void afficheliste(char ***liste_pieces){
	for (int i = 0;i<DIM;i++){
		for (int j = 0; j<NOMBRE_PIECES;j++){
			printf("%s",liste_pieces[j][i]);
			printf("    ");
			
		}
		printf("\n");
	}
}


void affichepiece(char **piece){
	for (int j = 0; j<DIM;j++){
		printf("%s",piece[j]);
		printf("\n");		
	}
}


//Wall kicks à tester si la rotation échoue : gauche, droite, haut
//On utilise ici des tuples et non des Vecteurs car c'est plus facile à implémenter (les valeurs des vecteurs devant être changées après leur déclaration)
const int wall_kicks[6][2] = {
    {0, -1}, //Déplacement à gauche
    {0, 1},  //Déplacement à droite
    {-1, 0}, //Déplacement à haut
	{0, -2}, 
	{0, 2},
	{-2, 0}
};
//Fontion qui teste la rotation en vérifiant si la pièce est bien dans la grille et pas en collision avec des pièces "mortes"
int rotation_valide(int n, int test_rotation[BLOC_MAX][2], int tab[LINE][COL]) {
	if (test_rotation == NULL){
		printf("Erreur de pointeur dans rotation !\n");
		exit(22);
	}
    for (int i = 0; i < n; i++) {
        if (test_rotation[i][0] < 0 || test_rotation[i][0] >= LINE || test_rotation[i][1] < 0 || test_rotation[i][1] >= COL || tab[test_rotation[i][0]][test_rotation[i][1]] >= 8)
            return 0;
    }
    return 1;
}

//Procédure qui applique simplement la rotation en copiant les coordonnées du tableau test dans le tetromino
void appliquer_rotation(Tetromino *t, int test_rotation[BLOC_MAX][2], int n) {
	if (test_rotation == NULL || t == NULL){
		printf("Erreur de pointeur dans rotation !\n");
		exit(23);
	}
    for (int i = 0; i < n; i++) {
		
        t->blocs[i][0] = test_rotation[i][0];
        t->blocs[i][1] = test_rotation[i][1];
    }
}
//Cette fonction utilise un algorithme simple de rotation dans un tableau de 5*5, pour ce faire on commence par "déplacer" le tetromino jusqu'en haut à gauche de la grille
//Ainsi les changements de coordonnées peuvent être appliqués comme si on était dans un tableau de 5*5, on redéplace en suite le tetromino à sa position initiale,
//les coordonnées du centre n'ayant pas changé (car on tourn la pièce autour du centre)
void rotation(int rotation, Tetromino *t, int n, int tab[LINE][COL]) {
    if (t == NULL) {
        printf("Erreur : pointeur Tetromino invalide dans rotation !\n");
        exit(24);
    }

    int dx = 2 - t->blocs[0][0]; //Distance x entre le centre du tetromino et la case (2,2), qui est le centre d'un tableau 5*5
    int dy = 2 - t->blocs[0][1]; //Distance y...
    int temp, posx, posy;
    int test_rotation[BLOC_MAX][2]; //Tableau test très important car tous les changements et toutes les vérifications se font avec lui, afin de ne pas modifier le tetromino
							  //tant que l'on est pas sûr que la rotation est valide
	if( rotation == 5 || rotation == 1){
    for (int i = 0; i < n; i++) {
        posx = t->blocs[i][0] + dx; //On déplace chaque bloc du tetromino en haut à gauche de la grille
        posy = t->blocs[i][1] + dy;

        if (rotation == 5) { //Pour tourner à gauche
            temp = posy;
            posy = posx;
            posx = DIM - temp - 1;
        } else if (rotation == 1) { //Pour tourner à droite
            temp = posx;
            posx = posy;
            posy = DIM - temp - 1;
        }

        posx -= dx;
        posy -= dy;

        test_rotation[i][0] = posx;
        test_rotation[i][1] = posy;
    }
	
    //On teste si la rotation est valide : si c'est le cas la procédure s'arrête avec le return après avoir appliqué la rotation
    if (rotation_valide(n, test_rotation, tab)) {
        appliquer_rotation(t, test_rotation, n);
        return;
    }
	
    //Tentatives de wall kicks : on déplace le tetromino avec chaque wall_kicks, séparemment et on vérifie si la position de la pièce est valide
    for (int k = 0; k < 6; k++) {
        int kick_x = wall_kicks[k][0];
        int kick_y = wall_kicks[k][1];
        int test_kick[BLOC_MAX][2]; 
		
        for (int i = 0; i < n; i++) {
            test_kick[i][0] = test_rotation[i][0] + kick_x;
            test_kick[i][1] = test_rotation[i][1] + kick_y;
        }

        if (rotation_valide(n, test_kick, tab)) {
            appliquer_rotation(t, test_kick, n);
            return;
        }
    }
	}
    //Si aucun wall kick ne fonctionne : le tetromino reste inchangé
}


