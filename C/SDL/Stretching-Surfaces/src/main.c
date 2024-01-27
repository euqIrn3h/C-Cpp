#include "./contants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

// Declaring functions
int init(void);
int loadMedia(void);
void close_window(void);
SDL_Surface* loadSurface(char* path);

//Globals

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_TOTAL
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

int main(int argc, char* args[]){

    //Main loop flag
    int quit = FALSE;

    //Event handler
    SDL_Event e;

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Apply the image
            SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
        }
    }

    //While application is running
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = TRUE;
            }
            if(e.type == SDL_KEYDOWN)
            {
                SDL_Rect stretchRect;

                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        quit = TRUE;
                    break;

                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];

                        stretchRect.x = 0 + 5;
                        stretchRect.y = 0 + 5;
                        stretchRect.w = WINDOW_WIDTH/2 - 10;
                        stretchRect.h = WINDOW_HEIGHT/2 - 10;
                        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
                        break;

                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                        
                        stretchRect.x = WINDOW_WIDTH/2 + 5;
                        stretchRect.y = 0 + 5;
                        stretchRect.w = WINDOW_WIDTH/2 - 10;
                        stretchRect.h = WINDOW_HEIGHT/2 - 10;
                        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
                        break;

                    default:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

                        stretchRect.x = 0 + 5;
                        stretchRect.y = WINDOW_HEIGHT/2;
                        stretchRect.w = WINDOW_WIDTH/2 - 10;
                        stretchRect.h = WINDOW_HEIGHT/2 - 10;
                        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
                        break;
                }
            }
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    quit = TRUE;
                }
            }
        }

        SDL_UpdateWindowSurface( gWindow );
    }

    //Free resources and close SDL
    close_window();

    return 0;  
}
    
int init(void){
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return FALSE;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL - Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return FALSE;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return TRUE;
}

int loadMedia()
{

    int success = TRUE;

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "./src/assets/mario_0.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = FALSE;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "./src/assets/mario_1.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = FALSE;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "./src/assets/yoshi_0.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = FALSE;
    }

    return success;
}

void close_window()
{
    //Deallocate surface
    SDL_FreeSurface( gScreenSurface );
    gScreenSurface = NULL;

    SDL_FreeSurface( gCurrentSurface );
    gCurrentSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface(char* path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}