#include "fichier.h"
//CONTROLES : A pour tourner vers la gauche la pièce, E pour la tourner vers la droite, S pour la faire descendre de 1, Q et D pour la déplacer respectivement vers la gauche ou vers la droite de 1


//Détecte quand on appuie sur une touche du clavier et renvoie un entier en fonction de la touche sur laquelle on appuie

int get_input() {
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);           // Sauvegarder config actuelle
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);         // Mode non canonique + pas d'écho
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Appliquer

	ch = getchar();                           // Lire une touche
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restaurer config
	return ch;
}

//Cela marche avec les majuscules et les minuscules
int key_input()
{
    //Programme qui permet de faire en sorte que le programme continue de s'exécuter si le joueur n'utilise pas le clavier
    //pour passer stdin en non-blocking mode.
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); //O_NONBLOCK dit à getchar() de ne pas attendre si rien n'est dispo.

    char c;
    c = get_input();
    fcntl(STDIN_FILENO, F_SETFL, flags); // On remet stdin en mode bloquant (stdin étant la variable associée au terminal)
    if (c==EOF){
        return 0; //On return 0 si getchar ne détecte rien
    }
   
    
    switch(c){
        case 'a':
            return 5;
            break;
        case 'e':
            return 1;
            break;
        case 'q':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 's':
            return 4;
            break;
        case 'A':
            return 5;
            break;
        case 'E':
            return 1;
            break;
        case 'Q':
            return 2;
            break;
        case 'D':
            return 3;
            break;
        case 'S':
            return 4;
            break;
        default:
            break;
    }
    return 0;
}

//Renvoie un vecteur différent en fonction de l'entier pris en argument : 2: vers la gauche (0,-1), 3: vers la droite (0,1), 4: vers le bas (1,0)
//Elle ne sert qu'à traduire ce que renvoie la fonction "key_input" en vecteur on peut le faire en une seule fonction mais ce serait un peu long avec les majuscules
//A noter que la fonction keyToVect() ne traite que 3 valeurs sur les 5 que peut renvoyer key_input() (à part le 0)
//car les valeurs 5 et 1 sont utilisées par la fonction rotation() (voir les fichiers piecesetrotation et main)
Vecteur keyToVect(int r)
{
    Vecteur v;
    switch(r)
    {
        case 2:
            v.x = 0;
            v.y = -1;
            break;
        case 3:
            v.x = 0;
            v.y = 1;
            break;
        case 4:
            v.x = 1;
            v.y = 0;
            break;
        default:
            v.x = 0;
            v.y = 0;
            break;
    }
    return v;
}
