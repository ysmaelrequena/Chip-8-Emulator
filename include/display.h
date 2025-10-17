#include <SDL3/SDL_video.h> 
#include <SDL3/SDL_render.h>
#include <stdbool.h>
#pragma once
#define SCALE 10
#define WINDOW_TITLE "CHIP-8 Emulator"
#define WINDOW_W 640
#define WINDOW_H 320


void display_init(void);

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;