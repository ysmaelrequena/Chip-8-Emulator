#pragma once
#include "cpu.h"
#include "opcodes.h"



const unsigned int INIT_ADDRESS = START_ADDRESS;

void load_ROM(char const *filename, chip_8 *cpu) {

    FILE *ROM = fopen(filename, "rb"); //Look for the ROM and open it in Read Only mode.
    
    if (filename == NULL) {
        printf("An error has ocurred %d\n", errno);
        perror("Error message");
    };
    
    fseek(ROM, 0, SEEK_END);
    long size = ftell(filename);
    rewind(ROM);
    fread(cpu->memory + 0x200, 1, size, ROM);
    fclose(ROM);
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

void initialization(chip_8 *cpu, char filename){
    cpu->program_counter = START_ADDRESS; //we initialize the program counter to the starting position.
    load_fontset(cpu); // we load the fontset from address 0x50
    load_ROM(cpu, filename); //Load the ROM in memory
};

void cycle(chip_8 *cpu) {
    cpu->opcode = (cpu->memory[cpu->program_counter] << 8u) | cpu->memory[cpu->program_counter + 1]; //Decode opcode, first byte gets shifted to the left, then it is combined with the right one

    if(!cpu->opcode) { //Erro handling
        perror("Opcode is not valid");
        return;
    };

    cpu->program_counter += 2; //The PC always gets increased by two, if an instruction gets skipped, the opcode's logic will take care of it.

    handleMainFuncTable(cpu); //Call the index in my table with function pointers.

    if (cpu->delay_timer > 0) {
        --cpu->delay_timer;
    };

    if (cpu->sound_timer > 0) {
        --cpu->sound_timer;
    };
};