#include "fichier.h"
//CONTROLES : A pour tourner vers la gauche la pièce, E pour la tourner vers la droite, S pour la faire descendre de 1, Q et D pour la déplacer respectivement vers la gauche ou vers la droite de 1


//Détecte quand on appuie sur une touche du clavier et renvoie un entier en fonction de la touche sur laquelle on appuie
//Il faut pour l'instant appuyer sur la touche Entrée pour que ça marche
//Cela marche avec les majuscules et les minuscules
int key_input()
{
    char c;
    c = getchar();
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

//Renvoie un vecteur différent en fonction de l'entier pris en argument : 2: vers la gauche (0,-1) 3: vers la droite (0,1)  4: vers le bas (1,0)
//Elle ne sert qu'à traduire ce que renvoie la fonction "key_input" en vecteur on peut le faire en une seule fonction mais ce serait un peu long avec les majuscules
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