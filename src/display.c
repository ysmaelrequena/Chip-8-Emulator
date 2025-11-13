#include "display.h"
#include "cpu.h"

void display_init(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_W, WINDOW_H);
}

void exit_cleanup(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void update(chip_8 *cpu, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, int *pitch) {
    SDL_UpdateTexture(texture, NULL, cpu->gfx, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}