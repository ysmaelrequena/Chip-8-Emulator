#include "display.h"

void display_init(void) {
    
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_W, WINDOW_H);

}