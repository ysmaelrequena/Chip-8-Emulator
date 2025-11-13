#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"
#include "cpu.h"
#include "input.h"
#include "opcodes.h"


void init_SDL(void) {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMEPAD);
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMEPAD) == 1) {
        SDL_Log("Could not initialize SDL, better luck next time, chump! %s\n", SDL_GetError());
    } else {
        printf("SDL initialized successfully");
    };
}

int main(int argc, char *argv[]) {

    bool running = true;

    //Boot sequence
    init_SDL();

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int PITCH = 64 * 256;

    chip_8 cpu = { 0 };

    initialization(&cpu, argv[1]);

    //Create window
    display_init(window, renderer, texture);

    while (running == true) { //main loop
        handle_input(&cpu, &running);
        cycle(&cpu);
        update(&cpu, window, renderer, texture, &PITCH);
        
        if (running != true) {
            exit_cleanup(window, renderer, texture);
        };
    }; 
    return 0;
}