#include "fichier.h"

/*Détecte quand on appuie sur une touche du clavier et renvoie un entier en fonction de la touche sur laquelle on appuie*/
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
}

/*Renvoie un vecteur différent en fonction de l'entier pris en argument : 2:<-  3:->  4:\/*/
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