#include <stdio.h>
#include <SDL2/SDL.h>
#include "./contants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct  ball {
    float x;
    float y;
    float width;
    float height;
} ball;

struct racket
{
    float x;
    float y;
    float width;
    float height;
};

struct racket racket_p1;
struct racket racket_p2;

int direction_x = 1;
int direction_y = 1;

int initialize_window(void){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initialiing SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,   
        SDL_WINDOWPOS_CENTERED,    
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
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

    return TRUE;
}

void setup(){
    ball.x = 10;
    ball.y = 10;
    ball.width = 15;
    ball.height = 15;

    //Player 1
    racket_p1.x = 0;
    racket_p1.y = 275;
    racket_p1.width = 10;
    racket_p1.height = 50;

    //Player 2
    racket_p2.x = WINDOW_WIDTH -10;
    racket_p2.y = 275;
    racket_p2.width = 10;
    racket_p2.height = 50;
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
        break;

        default:
        break;
    }
}

void update(){

    //Fixed timestep
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
        SDL_Delay(time_to_wait);
    }
    
    //Get a delta time factor converted to second to be used to update objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

    ball.x += 80 * direction_x * delta_time;
    ball.y += 100 * direction_y * delta_time;

    // Change direction

    if(ball.x >= (WINDOW_WIDTH - ball.width) || ball.x <= 0) {
        direction_x *= -1;
    }
    if(ball.y >= (WINDOW_HEIGHT - ball.height) || ball.y <= 0) {
        direction_y *= -1;
    }
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Here is where we can star drawing our game objects

    //Draw rectangle

    SDL_Rect ball_rect = {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };

    SDL_Rect racket_p1_rect = {
        (int)racket_p1.x,
        (int)racket_p1.y,
        (int)racket_p1.width,
        (int)racket_p1.height
    };

    SDL_Rect racket_p2_rect = {
        (int)racket_p2.x,
        (int)racket_p2.y,
        (int)racket_p2.width,
        (int)racket_p2.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);
    SDL_RenderFillRect(renderer, &racket_p1_rect);
    SDL_RenderFillRect(renderer, &racket_p2_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(){
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