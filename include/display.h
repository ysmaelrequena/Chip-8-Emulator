#pragma once
#include <SDL3/SDL_video.h> 
#include <SDL3/SDL_render.h>
#include <stdbool.h>
#include "cpu.h"
#define SCALE 10
#define WINDOW_TITLE "CHIP-8 Emulator"
#define WINDOW_W 640
#define WINDOW_H 320

//Funtion declarations
void display_init(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);
void exit_cleanup(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);
void update(chip_8 *cpu, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, int *pitch);

//Pitch is the calculation of my pixel row width time the amount of bytes per pixels. Used in the update function 