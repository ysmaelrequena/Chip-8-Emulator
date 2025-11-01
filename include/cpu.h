#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define START_ADDRESS ((uint16_t)0x200)
#define FONTSET_START_ADDRESS ((uint16_t)0x50)
#pragma once

typedef struct {

    uint16_t opcode;
    uint16_t program_counter;
    uint16_t stack[16];
    uint16_t index;
    uint8_t registers[16];
    uint8_t memory[4096];
    uint8_t stack_pointer;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keys[16];
    uint8_t gfx[64 * 32];
    
} chip_8;


void load_ROM(char const *filename, chip_8 *cpu);
void load_fontset();
