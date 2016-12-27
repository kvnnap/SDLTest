#include <iostream>
#include <chrono>
#include "SDL.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;


//The gWindow we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the gWindow
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init() {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }


    //Create gWindow
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    } else {
        //Get gWindow surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
        return true;
    }

}

void destroy() {
    //Destroy gWindow
    SDL_DestroyWindow( gWindow );

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *argv[]) {

    if (!init()) {
        return EXIT_FAILURE;
    }

    // Main loop flag
    bool ready = false;

    //Event handler
    SDL_Event e;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    unsigned i = 0, fpsCount = 0;

    while (!ready) {

        //Fill the surface white
        SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, (i >> 10) & 0xFF, (i >> 8) & 0xFF, (i >> 8) & 0xFF ) );
        ++i;
        SDL_LockSurface(gScreenSurface);
        //cout << gScreenSurface->pixels << endl;
        *((uint32_t *)gScreenSurface->pixels + 11520 - 80) = SDL_MapRGB( gScreenSurface->format, 255,255,255 );
        SDL_UnlockSurface(gScreenSurface);
        //++i;

        //Update the surface
        SDL_UpdateWindowSurface( gWindow );

        //Wait two seconds
        //SDL_Delay( 2000 );

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                ready = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        cout << "Up Key Down" << endl;
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        cout << "Up Key Up" << endl;
                        break;
                    default:
                        break;
                }
            }
        }


        // Timer
        ++fpsCount;
        end = chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (elapsed_seconds.count() >= 1.0) {
            start = chrono::system_clock::now();
            cout << "FPS: " << fpsCount << endl;
            fpsCount = 0;
        }
    }

    destroy();

    return EXIT_SUCCESS;
}
