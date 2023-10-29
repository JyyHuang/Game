// headers
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]){
    // rendering window and show 2d image 
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    // returns -1 if theres an error
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not be initialized! SDL_Error: %s\n",SDL_GetError());
    }
    else{
        window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            printf("Unable to create window. SDL_ERROR: %s\n", SDL_GetError());
        }
    }


}