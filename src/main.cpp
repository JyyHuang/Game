// headers
#include <SDL.h>
#include <iostream>
using namespace std;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool load();
void close();
SDL_Surface* loadSurface(std::string path);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// rendering window, surface, and image
SDL_Window* pWindow = NULL;
SDL_Surface* pScreenSurface = NULL;

//pointer to array keySurfaces with length KEY_PRESS_SURFACE_TOTAL
SDL_Surface* pKeySurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* pCurrentSurface = NULL;



int main(int argc, char* argv[]){
    cout << "HELLO WORLD" << endl;
    if(!init()) {
        cout << "Failed to init!" << endl;
    } else {
        if (!load()) {
            cout << "Failed to load!" << endl;
        }
        else {
            // quit flag
            bool quit = false;
            // Event handler
            SDL_Event e;

            pCurrentSurface = pKeySurfaces[KEY_PRESS_SURFACE_DEFAULT];
            // main loop
            while (!quit){
                // Event loop in queue
                // When queue is empty, SDL_PollEvent returns 0
                while (SDL_PollEvent(&e) != 0){
                    if (e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN){
                        switch (e.key.keysym.sym) 
                        {
                            case SDLK_UP:
                            pCurrentSurface = pKeySurfaces[KEY_PRESS_SURFACE_UP];
                            break;

                            case SDLK_DOWN:
                            pCurrentSurface = pKeySurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                            case SDLK_LEFT:
                            pCurrentSurface = pKeySurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                            case SDLK_RIGHT:
                            pCurrentSurface = pKeySurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                            default:
                            pCurrentSurface = pKeySurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                SDL_BlitSurface(pCurrentSurface, NULL, pScreenSurface, NULL);
                SDL_UpdateWindowSurface(pWindow);
            }
        }
    }

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
        pWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (pWindow == NULL){
            cout << "Unable to create window. SDL_ERROR: " << SDL_GetError() << endl;
            success = false;
        }
        else {
            pScreenSurface = SDL_GetWindowSurface(pWindow);
        }
    }
    return success;
}

bool load(){
    bool success = true;
    
    // load default surface
    pKeySurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
    if (pKeySurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
        cout << "Failed to load default image." << endl;
        success = false;
    }

    // "up" surface
    pKeySurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_presses/up.bmp");
    if (pKeySurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        cout << "Failed to load yp image." << endl;
        success = false;
    }

    //Load down surface
    pKeySurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_presses/down.bmp");
    if( pKeySurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    //Load left surface
    pKeySurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_presses/left.bmp");
    if( pKeySurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    //Load right surface
    pKeySurfaces[KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
    if( pKeySurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void close(){
    SDL_FreeSurface(pCurrentSurface);

    SDL_DestroyWindow(pWindow);
    pWindow = NULL;

    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path){
    SDL_Surface* returnedSurface = NULL;
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());

    if (surface == NULL){
        cout << "Unable to load image " << path.c_str() << " SDL Error: "<< SDL_GetError() << endl;
    }
    else{
        returnedSurface = SDL_ConvertSurface(surface, pScreenSurface -> format, 0);
        if (returnedSurface == NULL){
            cout << "Unable to optimize image " << path.c_str() << " SDL Error: "<< SDL_GetError() << endl;
        }
        SDL_FreeSurface(surface);
    }
    return returnedSurface;
}