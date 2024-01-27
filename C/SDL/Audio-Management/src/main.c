#include "./contants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

//The music that will be played
Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initialize_window(void){
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
        fprintf(stderr, "Error initialiing SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(
        "SDL Audio Management",
        SDL_WINDOWPOS_CENTERED,   
        SDL_WINDOWPOS_CENTERED,    
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(!window){
        fprintf(stderr, "Error creating SDL window.\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        fprintf(stderr, "Error on renderer SDL renderer.\n");
        return FALSE;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return FALSE;
    }

    gMusic = Mix_LoadMUS("./src/audio/Schubert-ave-maria.wav");
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return FALSE;
    }

    //Load sound effects
    gScratch = Mix_LoadWAV_RW(SDL_RWFromFile("./src/audio/oh-my-god-1.wav", "rb"), 1);
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return FALSE;
    }

    return TRUE;
}

void setup(){

}

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            game_is_running = FALSE;
        break;
        
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                game_is_running = FALSE;
            }
            if(event.key.keysym.sym == SDLK_1){
                if( Mix_PlayingMusic() == 0 )
                {
                    Mix_PlayMusic( gMusic, -1 );
                }
                else
                {
                    if( Mix_PausedMusic() == 1 )
                    {
                        Mix_ResumeMusic();
                    }
                    else
                    {
                        Mix_PauseMusic();
                    }
                }
            }
            if(event.key.keysym.sym == SDLK_2){
               Mix_PlayChannel( -1, gScratch, 0 );
            }
        break;

        default:
        break;
    }
}

void update(){

}

void render(){

}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]){
    game_is_running = initialize_window();

    setup();

    while (game_is_running)
    {
        process_input();
        update();
        render();
    }
    
    return 0;
}