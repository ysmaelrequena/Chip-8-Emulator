#include "display.h"
#include "cpu.h"

void exit_cleanup(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void update(chip_8 *cpu, SDL_Renderer *renderer, SDL_Texture *texture, int pitch) {

    uint32_t pixel_buffer[ 64 * 32 ];
    
    for (int i = 0; i < 64 * 32; ++i) {
        if (cpu->gfx[i] == 1) {
            pixel_buffer[i] = 0xFFFFFFFFu;     // white
        } else {
            pixel_buffer[i] = 0xFF000000u;     // black
        }
    };

    if(SDL_UpdateTexture(texture, NULL, pixel_buffer, pitch)) {
        printf("success\n");     
    } else {
        printf("Oh shit, problems updating textures: %s\n", SDL_GetError());
    };
    
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}