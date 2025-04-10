typedef struct{
    int x;
    int y;
}Vecteur;

typedef struct{
    int blocs[5][2];
    int isalive;

}Tetromino;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;
