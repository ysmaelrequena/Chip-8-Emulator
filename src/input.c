#include "input.h"


void handle_input(chip_8 *cpu, bool *running) {
    
    SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_EVENT_QUIT:
                {
                   *running = false;
                }; break;

                case SDL_EVENT_KEY_DOWN:
                    {
                        printf("A key was pressed: %d\n", event.key.key);
                        switch (event.key.key) {

                            case SDLK_ESCAPE:
                            {
                                *running = false;
                            }; break;

                            case SDLK_1:
                            {
                                cpu->keys[0] = 1;
                            }; break;

                            case SDLK_2:
                            {
                                cpu->keys[1] = 1;
                            }; break;

                            case SDLK_3:
                            {
                                cpu->keys[2] = 1;
                            }; break;

                            case SDLK_4:
                            {
                                cpu->keys[3] = 1;
                            }; break;

                            case SDLK_Q:
                            {
                                cpu->keys[4] = 1;
                            }; break;

                            case SDLK_W:
                            {
                                cpu->keys[5] = 1;
                            }; break;

                            case SDLK_E:
                            {
                                cpu->keys[6] = 1;
                            }; break;

                            case SDLK_R:
                            {
                                cpu->keys[7] = 1;
                            }; break;

                            case SDLK_A:
                            {
                                cpu->keys[8] = 1;
                            }; break;

                            case SDLK_S:
                            {
                                cpu->keys[9] = 1;
                            }; break;

                            case SDLK_D:
                            {
                                cpu->keys[0xA] = 1;
                            }; break;

                            case SDLK_F:
                            {
                                cpu->keys[0xB] = 1;
                            }; break;

                            case SDLK_Z:
                            {
                                cpu->keys[0xC] = 1;
                            }; break;

                            case SDLK_X:
                            {
                                cpu->keys[0xD] = 1;
                            }; break;

                            case SDLK_C:
                            {
                                cpu->keys[0xE] = 1;
                            }; break;

                            case SDLK_V:
                            {
                                cpu->keys[0xF] = 1;
                            }; break;                            
                        }; break;
                    };
                
                case SDL_EVENT_KEY_UP:
                {
                    printf("A key was released: %d\n", event.key.key);
                        switch (event.key.key) {
                            
                            case SDLK_1:
                            {
                                cpu->keys[0] = 0;
                            }; break;

                            case SDLK_2:
                            {
                                cpu->keys[1] = 0;
                            }; break;

                            case SDLK_3:
                            {
                                cpu->keys[2] = 0;
                            }; break;

                            case SDLK_4:
                            {
                                cpu->keys[3] = 0;
                            }; break;

                            case SDLK_Q:
                            {
                                cpu->keys[4] = 0;
                            }; break;

                            case SDLK_W:
                            {
                                cpu->keys[5] = 0;
                            }; break;

                            case SDLK_E:
                            {
                                cpu->keys[6] = 0;
                            }; break;

                            case SDLK_R:
                            {
                                cpu->keys[7] = 0;
                            }; break;

                            case SDLK_A:
                            {
                                cpu->keys[8] = 0;
                            }; break;

                            case SDLK_S:
                            {
                                cpu->keys[9] = 0;
                            }; break;

                            case SDLK_D:
                            {
                                cpu->keys[0xA] = 0;
                            }; break;

                            case SDLK_F:
                            {
                                cpu->keys[0xB] = 0;
                            }; break;

                            case SDLK_Z:
                            {
                                cpu->keys[0xC] = 0;
                            }; break;

                            case SDLK_X:
                            {
                                cpu->keys[0xD] = 0;
                            }; break;

                            case SDLK_C:
                            {
                                cpu->keys[0xE] = 0;
                            }; break;

                            case SDLK_V:
                            {
                                cpu->keys[0xF] = 0;
                            }; break;                            
                        }; break;
                    }; break;
                };
            };
    }
