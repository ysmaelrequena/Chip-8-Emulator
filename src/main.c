#include <SDL3/SDL_main.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"
#pragma once

void init_SDL(void) {
    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_GAMEPAD) != false) {
        SDL_Log("Could not initialize SDL, better luck next time, chump! %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    };
}

void final_cleanup(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {

    bool app_state = true;
    
    //Boot sequence
    if(!init_SDL) exit(EXIT_FAILURE);
    SDL_Log("Init failed at main function: %s\n", SDL_GetError());
   
    //Create window
    display_init();
    
    while (app_state == true) { //main loop
        
        if (app_state != true) {
            final_cleanup();
        };

        

    } 
    return 0;
}