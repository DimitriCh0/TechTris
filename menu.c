#include "fichier.h"



const char *options[] = {"Jouer","Scoreboard","Atelier","Quitter"};
#define NUM_OPTIONS (sizeof(options) / sizeof(char*))

// Lecture d'une touche sans attendre Enter
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

//surlignage
void print_colored(const char *text, int highlight) {
	if (highlight) {
        	printf("> \033[1;32m%s\033[0m <\n", text); // Texte vert si sélectionné
	} 
	else {
        	printf("  %s\n", text);
	}
}


void wait_for_enter() {
	printf("\nAppuie sur Entrée pour continuer...");
	getchar();
}

void tetris() {
	system("clear");
	printf("Tetris");
	wait_for_enter();
}

void scoreboard() {
	system("clear");
	printf("Scoreboard");
	wait_for_enter();
}

void dessin() {
	atelier();
}

void avantdessin() {
	system("clear");
	printf("Bienvenue dans le menu pour dessiner tes pieces ! \n");
	printf("Quelques regles avant de commencer : \n");
	wait_for_enter();
	dessin();
}



int main() {
	int selected = 0;
	int input;

	while (1) {
		system("clear");
		printf("\n\n\n");
		print_colored("===== MENU =====", 0);
		printf("\n");

		for (int i = 0; i < NUM_OPTIONS; i++) {
		    print_colored(options[i], i == selected);
		}

		printf("\nUtilise Z (haut), S (bas), E (valider)\n");

		input = get_input();

		if (input == 'z' || input == 'Z') {
			selected = (selected - 1 + NUM_OPTIONS) % NUM_OPTIONS;
		} 
		else if (input == 's' || input == 'S') {
			selected = (selected + 1) % NUM_OPTIONS;
		} 
		else if (input == 'e' || input == 'E') {
			switch (selected) {
		        	case 0:
		            		tetris();
		            		break;
		        	case 1:
		            		scoreboard();
		            		break;
		        	case 2:
		            		avantdessin();
		            		break;
				case 3:
					system("clear");;
					print_colored("À bientôt !", 0);
					return 0;
		    }
		}
	}

    return 0;
}

