#include <errno.h>
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>



//CONSTANTES
//Le nombre de pièces (Tétrominos)
#define NOMBRE_PIECES 7
//Le nombre fixe de blocs composant chaque pièce
#define DIM 5
//Les dimensions de la grille principale
#define COL 10
#define LIGNE 10
#define UTF 8

#define BLOC_MAX 5
#define NUM_CASE 25



//Fonctions et procédures
//Jeu
void jeu_tetris(Joueur* J, int tab_principal[LIGNE][COL]);

//Tétrominos
void creation_tetrominos(Tetromino *t);
void tetrominoConstructor(char **tab, Tetromino *t);
void deplacer_t(Tetromino *t,Vecteur v,int n);
void place_t(Tetromino *t,int tab[LIGNE][COL],Vecteur v, int n, int color);
int a_survecu(Tetromino *t, Vecteur v, int tab[LIGNE][COL], int n);
int NestPasBordureD(Tetromino *t, int n);
int NestPasBordureG(Tetromino *t, int n);
void reinitialiser_piece(Tetromino *t, int n);

//Fonctions du jeu
void sleep_ms(float milliseconds);
void effacer_ligne(int tab[LIGNE][COL], int nb);
void gravitation(int tab[LIGNE][COL], int d, int debut);
int game_over(int tab[LIGNE][COL], Tetromino *t, int n,int color);
void score(Joueur* J,int tab_principal[LIGNE][COL],int nb_lignes);
int scoreGrille(int *tab);

//Inputs
int saisir_entree();
int entree_clavier();
Vecteur conversion_entree_vecteur(int r);

//Draw
void afficher(char grille[LIGNE][COL][UTF], Joueur* J, Tetromino *t, int s, int couleur);
void afficher_int(int tab[LIGNE][COL]);
void effacer(int tab[LIGNE][COL]);
void dessiner(int tab[LIGNE][COL], char grille[LIGNE][COL][UTF]);
void actualiser(char grille[LIGNE][COL][UTF], int tab[LIGNE][COL], Joueur* J, Tetromino *t, int s, int couleur);
void afficher_tetromino(Tetromino *t, int ligne, int couleur);

//Rotation et pièces
void rotation(int rotation, Tetromino *t, int n, int tab[LIGNE][COL]);
int rotation_valide(int n, int test_rotation[NUM_CASE][2], int tab[LIGNE][COL]);
void appliquer_rotation(Tetromino *t, int test_rotation[NUM_CASE][2], int n);

//Création des pièces
char*** pieces(); // Création de tableau
void lecture(char*** liste_pieces, int var); // Remplissage de tableau
void liberer_pieces(char*** liste_pieces); // Libération de mémoire
void afficheliste(char ***liste_pieces); 
void choix_couleur(char ***liste_pieces,int i,int j,int k, const char *Couleur);



//sauvegarde
void enregistrement_partie(int tab[LIGNE][COL], Joueur* J);

//pause
int pause();

//Scoreboard
Joueur constru();
void lire_scoreboard(FILE *f);
void enregistrement_score(Joueur* J);
void triInsertion(Joueur* tab, int taille);

//Atelier
void atelier();
char*** pieces_vide();
void enregistrement(char*** pieces_dessinees);
void menu_enregistrement(char*** pieces_dessinees);
int menu_defaut(char *** pieces_dessinees);


//Conditions de dessin de pièces
int voisin(char*** pieces_dessinees, int piece, int selected);
void lie_centre(char*** pieces_dessinees, int piece, int x, int y, int deja_verif[DIM][DIM]);
int correction(char *** pieces_dessinees, int piece);


//Selection colorée
void print_tab(char valeur, int surligner, int piece); 
void afficher_colore(const char *text, int surligner);
void afficher_colore_atelier(const char *text, int surligner);
void afficher_colore_tetris(const char *text, int surligner);
void choix_couleur2(char valeur, const char *Couleur, int surligner);
int saisir_entree();


void attendre_pour_entree();
//Menu
void afficher_menu();

//Sous-menu
void tetris();
void lecture_sauvegarde(FILE *fichier, char tab_char[LIGNE][COL+1], int tab_int[LIGNE][COL], Joueur* Joueur);
void sauvegarde();
void scoreboard();
void dessin(); //Atelier
void avantdessin();//Atelier
void affichagepieces();





