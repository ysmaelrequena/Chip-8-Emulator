#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"
#include "cpu.h"
#include "input.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s romfile\n", argv[0]);
        return 1;
    }

    bool running = true;
    
    chip_8 cpu = { 0 };
    chip_8 *ptr_cpu = &cpu;

    int cycle_delay = atoi(argv[2]);

    Uint64 last_cycle_ms = SDL_GetTicks();

    //Boot sequence
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("Success initializing SDL\n");
    };

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_W, WINDOW_H, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    
    if (!window || !renderer || !texture) {
        fprintf(stderr, "Window, Renderer or Texture not initialized: %s\n", SDL_GetError());
    };

    int PITCH = 64 * sizeof(uint32_t);

    initialization(ptr_cpu, argv[1]);

    while (running == true) { //main loop
        handle_input(ptr_cpu, &running);

        Uint64 current_ms = SDL_GetTicks();
        Uint64 delta_time = current_ms - last_cycle_ms;
        
        if (delta_time >= cycle_delay ) {
            last_cycle_ms = SDL_GetTicks();
            cycle(ptr_cpu);
            update(ptr_cpu, renderer, texture, PITCH);  
        };
    }; 

    exit_cleanup(window, renderer, texture);
    return 0;
}
