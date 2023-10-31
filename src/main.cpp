// headers
#include <SDL.h>
#include <iostream>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// rendering window, surface, and image
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* HelloWorld = NULL;

bool init();
bool load();
void close();

int main(int argc, char* argv[]){

    if(!init()) {
        cout << "Failed to init!" << endl;
    } else {
        if (!load()) {
            cout << "Failed to load!" << endl;
        }
        else {
            // apply image
            SDL_BlitSurface(HelloWorld, NULL,screenSurface, NULL);
        }
    }
    SDL_UpdateWindowSurface(window);

    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    // quit flag
    bool quit = false;
    // Event handler
    SDL_Event e;
    
    close();
    return 0;

}

bool init(){
    bool success = true;

    // Initialize SDL
    // returns -1 if theres an error
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << endl;
        success = false;
    }
    else{
        window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            cout << "Unable to create window. SDL_ERROR: " << SDL_GetError() << endl;
            success = false;
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool load(){
    bool success = true;

    // load image
    HelloWorld = SDL_LoadBMP("hello_world.bmp");

    if (HelloWorld == NULL){
        cout << "Unable to load image. SDL_ERROR: " << SDL_GetError() << endl;
        success = false;
    }

    return success;
}

void close(){
    SDL_FreeSurface( HelloWorld );
    HelloWorld = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}