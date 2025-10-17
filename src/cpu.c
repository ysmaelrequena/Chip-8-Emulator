#pragma once
#include "cpu.h"



const unsigned int INIT_ADDRESS = START_ADDRESS;
const chip_8 *cpuPtr = &cpu;

void load_ROM(char const *filename, chip_8 *cpu) {

    if (filename == NULL) {
        printf("An error has ocurred %d\n", errno);
        perror("Error message");
    };
    
    fopen(filename, "rb");
    fseek(filename, 0, SEEK_END);
    long size = ftell(filename);
    rewind(filename);
    fread(cpu->memory[0x200], 1, size, filename);
    fclose(filename);
    cpu->program_counter = START_ADDRESS;
};

void load_fontset(chip_8 *cpu) {
    const unsigned int FONTSET_SIZE = 80;

    uint8_t fontset[FONTSET_SIZE] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

    for (unsigned int i = 0; i < FONTSET_SIZE; ++i) {
        cpu->memory[FONTSET_START_ADDRESS + i] = fontset[i];
    };
};

//TODO, Handlers for the opcodes in another document, and then a function pointer table that just
//determines what to do with the code after decoding the first two bytes 