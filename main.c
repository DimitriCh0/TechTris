#include "fichier.h"




 
int main(){
	printf("Sah Dimitri\n");
	/*system ("/bin/stty raw");*/
	int tab_principal[LINE][COL] = {0};
    	char grille[LINE][COL];
    	int n;
        Vecteur v;
    char truc[DIM][DIM] = 
   {"00000",
    "00100",
    "01110",
    "00100",
    "00000"};

    Tetromino test = tetrominoConstructor(truc);

    printf("*******************\n");
    system("clear");
    while(1){
    	n = key_input();
        v = keyToVect(n);
        rotation(n,&test);
        place_t(&test,tab_principal,v);
        draw(tab_principal,grille);
        display(grille);
        printf("*******************\n");
        sleep(0.1);
        clear(tab_principal);
       
       
    }
    /*system ("/bin/stty cooked");*/

    
	return 0;
}
