#include "fichier.h"




 
int main(){
    //Partie du programme qui change le mode du terminal (en non-canonical) afin qu'on n'ait pas besoin d'appuyer sur Entrée pour contrôler la pièce
    struct termios info;
    tcgetattr(0, &info);          // get current terminal attirbutes; 0 is the file descriptor for stdin 
    info.c_lflag &= ~ICANON;      // disable canonical mode 
    info.c_cc[VMIN] = 1;          // wait until at least one keystroke available 
    info.c_cc[VTIME] = 0;         // no timeout 
    tcsetattr(0, TCSANOW, &info);
	printf("Sah Dimitri\n");
	int tab_principal[LINE][COL] = {0};
    char grille[LINE][COL];
    int n;
    Vecteur v;
    Vecteur d;
    d.x = 1;
    d.y = 0;
    char truc[DIM][DIM] = 
   {"00000",
    "00100",
    "01110",
    "00100",
    "00000"};

    Tetromino test = tetrominoConstructor(truc);

    while(1){
        

    	n = key_input(); //On appelle key_input()
        
        if (n!=0){
            v = keyToVect(n);
            rotation(n,&test);
            place_t(&test,tab_principal,v);
            n=0;
        }else{
            place_t(&test,tab_principal,d);
           
        }
        draw(tab_principal,grille);
        refresh(grille, tab_principal);
        sleep(1);
    }
    //Remet le terminal dans son mode de base (canonical)
    tcgetattr(0, &info);
    info.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &info); 
	return 0;
}
