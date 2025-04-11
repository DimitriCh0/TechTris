#include "fichier.h"




 
int main(){
	printf("Sah Dimitri\n");
	/*system ("/bin/stty raw");*/
	int tab_principal[LINE][COL] = {0};
    	char grille[LINE][COL];
    	int n;
        Vecteur v;
    char truc[5][5] = 
   {"     ",
    "  #  ",
    " ### ",
    "  #  ",
    "     "};

    Tetromino test = tetrominoConstructor(truc);
   /* for (int j = 0; j<5; j++){
        printf("x=%d y=%d\n",test.blocs[j][0],test.blocs[j][1]);
    }*/

    printf("*******************\n");
    system("clear");
    while(1){
    	n = key_input();
        v = keyToVect(n);
        place_t(&test,tab_principal,v);
        draw(tab_principal,grille);
        display(grille);
        printf("*******************\n");
        sleep(0.1);
        clear(tab_principal);
        if (n!=0){
        system("clear");
        }
       
    }
    /*system ("/bin/stty cooked");*/

    
	return 0;
}
