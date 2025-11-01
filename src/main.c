#include <SDL3/SDL_main.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"
#include "cpu.h"
#include "opcodes.h"
#pragma once

void init_SDL(void) {
    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_GAMEPAD) != false) {
        SDL_Log("Could not initialize SDL, better luck next time, chump! %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    };
};

int main() {

    //Declare the window, renderer and texture as global variables within my stack, so my initialization, update and cleanup functions can use them

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    bool running = true;
    chip_8 cpu = { 0 };
    
    //Boot sequence
    if(!init_SDL) exit(EXIT_FAILURE);
    SDL_Log("Init failed at main function: %s\n", SDL_GetError());
   
    //Create window
    display_init();
    
    while (running == true) { //main loop
        
        if (running != true) {
            final_cleanup();
        };
    }; 
    return 0;
}