#include <iostream>
#include <chrono>
#include "SDL.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;


//The gWindow we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the gWindow
// SDL_Surface* gScreenSurface = nullptr;

//The image we will load and show on the screen
SDL_Renderer* renderer = nullptr;

SDL_Texture* texture = nullptr;

bool init(bool accelerated) {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }


    //Create gWindow
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == nullptr )
    {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    //Get gWindow surface
    // gScreenSurface = SDL_GetWindowSurface( gWindow );

    renderer = SDL_CreateRenderer(gWindow, -1, accelerated ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC : SDL_RENDERER_SOFTWARE);
    if( renderer == nullptr )
    {
        cout << "SDL_CreateRenderer error! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    // Main texture
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (texture == nullptr) {
        cout << "SDL_CreateTexture error! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void destroy() {
    // Destroy Texture
    SDL_DestroyTexture(texture);

    // Destroy Renderer
    SDL_DestroyRenderer(renderer);

    //Destroy gWindow
    SDL_DestroyWindow( gWindow );

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *argv[]) {

    if (!init(argc > 1)) {
        return EXIT_FAILURE;
    }

    // Main loop flag
    bool ready = false;

    //Event handler
    SDL_Event e;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    unsigned i = 0, fpsCount = 0;

    // Rect
    SDL_Rect rect, textureRect;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    rect.x = rect.y = 0;
    textureRect = rect;
    textureRect.w /= 2;
    textureRect.h /= 2;

    while (!ready) {

        /*//Fill the surface white
        SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, (i >> 10) & 0xFF, (i >> 8) & 0xFF, (i >> 8) & 0xFF ) );
        ++i;
        SDL_LockSurface(gScreenSurface);
        //cout << gScreenSurface->pixels << endl;
        *((uint32_t *)gScreenSurface->pixels + 11520 - 80) = SDL_MapRGB( gScreenSurface->format, 255,255,255 );
        SDL_UnlockSurface(gScreenSurface);
        //++i;

        //Update the surface
        SDL_UpdateWindowSurface( gWindow );*/

        // SDL2
        //SDL_SetRenderDrawColor(renderer, 144,0,0, 0xFF);
        //SDL_RenderClear(renderer);

        //SDL_SetRenderDrawColor(renderer, (i >> 10) & 0xFF, (i >> 8) & 0xFF, (i >> 0) & 0xFF , 0xFF);
        //SDL_RenderFillRect(renderer, &rect);

        uint8_t * pixels = nullptr; int pitch = 0;
        SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch);
        *(uint32_t*)(pixels + (20 * pitch + 79 * sizeof(uint32_t))) = 0xFF000000 | i;
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
        ++i;


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
