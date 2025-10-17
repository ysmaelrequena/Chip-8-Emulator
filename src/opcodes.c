#pragma once
#include "cpu.h"


//OPCODES

//00E0 CLS - Clear the screen
void OP_00E0(chip_8 *cpu) {
    memset(0, cpu->gfx, sizeof(cpu->gfx));
};

//00EE RET - The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
void OP_00EE(chip_8 *cpu) {
    --cpu->stack_pointer;
    cpu->program_counter = cpu->stack[cpu->stack_pointer];
};

//1nnn JMP - Jump to location nnn
void OP_1nnn(chip_8 *cpu) {
    uint16_t address = cpu->opcode & 0x0FFFu;
    cpu->program_counter = address;
};

//2nnn CALL - The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
void OP_2nnn(chip_8 *cpu) {
    uint16_t address = cpu->opcode & 0x0FFFu;
    ++cpu->stack_pointer;
    cpu->stack[cpu->stack_pointer] = cpu->program_counter;
    cpu->program_counter = address;  
};

//3xkk Skip next instruction if Vx = kk.
void OP_3xkk(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8;
    uint8_t kk = cpu->opcode & 0x00FFu;

    if (cpu->registers[vx] == kk) {
        cpu->program_counter += 4;
    } else {
        cpu->program_counter += 2;
    };
};

//4xkk - Skip next instruction if Vx != kk.
void OP_4xkk(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t kk = cpu->opcode & 0x00FFu;

    if (cpu->registers[vx] != kk) {
        cpu->program_counter += 4;
    } else {
        cpu->program_counter += 2;
    };
};

//5xy0 - Skip next instruction if Vx = Vy.
void OP_5xy0(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->registers[vx] == cpu->registers[vy]) {
        cpu->program_counter += 4;
    } else {
        cpu->program_counter += 2;
    };
};

//6xkk - Set Vx = kk.
void OP_6xkk(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t kk = cpu->opcode & 0x00FFu;

    cpu->registers[vx] = kk;
};

//7xkk - Set Vx = Vx + kk.
void OP_7xkk(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t kk = cpu->opcode & 0x00FFu;


    cpu->registers[vx] += kk;
};

//8xy0 - Set Vx = Vy.
void OP_8xy0(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] = cpu->registers[vy];
};

//8xy1 - Set Vx = Vx OR Vy
void OP_8xy1(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] |= cpu->registers[vy];
};

//8xy2 - Set Vx = Vx AND Vy.
void OP_8xy2(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] &= cpu->registers[vy];
};

//8xy3 - Set Vx = Vx XOR Vy.
void OP_8xy3(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] ^= cpu->registers[vy];
};

//8xy4 - ADD Vx, Vy
void OP_8xy4(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    uint16_t sum = cpu->registers[vx] + cpu->registers[vy];

    if (sum > 255u) {
        cpu->registers[15] = 1;
    } else {
        cpu->registers[15] = 0;
    };

    cpu->registers[vx] = sum & 0xFFu;
};

//8xy5 - Set Vx = Vx - Vy, set VF = NOT borrow
void OP_8xy5(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;
    
    if (cpu->registers[vx] > cpu->registers[vy]) {
        cpu->registers[15] = 1;
    } else {
        cpu->registers[15] = 0;
    };

    uint16_t subtraction = cpu->registers[vx] - cpu->registers[vy];
    cpu->registers[vx] = subtraction;
};

//8xy6 - If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
void OP_8xy6(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->registers[15] = cpu->registers[vx] & 0x01u;

    cpu->registers[vx] >>= 1; //Every bit shift by one, is a division of the original value by 2; 
};

//8xy7 - If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
void OP_8xy7(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->registers[vy] > cpu->registers[vx]) {
        cpu->registers[15] = 1;
    } else {
        cpu->registers[15] = 0;
    };

    cpu->registers[vx] -= cpu->registers[vy];
};

//8xyE - If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
void OP_8xyE(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
   
    cpu->registers[15] = cpu->registers[vx] & 0x80u;8;

    cpu->registers[vx] <<= 1; //The opposite of 8xy6
};

//9xy0 - The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
void OP_9xy0(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->registers[vx] != cpu->registers[vy]) {
        cpu->program_counter +=2;
    };
};

//Annn - The value of register I is set to nnn.
void OP_Annn(chip_8 *cpu) {
    uint16_t address = cpu->opcode & 0x0FFFu;

    cpu->index = address;
};

//Bnnn - The program counter is set to nnn plus the value of V0.
void OP_Bnnn(chip_8 *cpu) {
    uint16_t address = cpu->opcode & 0x0FFFu;

    cpu->program_counter = address + cpu->registers[0];
};

//cxkk - The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
void OP_cxkk(chip_8 *cpu) {
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8;
    uint8_t kk = cpu->opcode & 0x00FFu;
    int random_number = rand() % 256;

    cpu->registers[vx] = kk & random_number;
};

//Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void OP_Dxyn(chip_8 *cpu) {
   uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
   uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u; 
   uint8_t height = (cpu->opcode & 0x000Fu);

   uint8_t sprite_byte;
   cpu->registers[0xF] = 0;

   for (uint16_t y_row = 0; y_row < height; y_row++) {
    sprite_byte = cpu->memory[cpu->index + y_row];

    for (uint8_t x_pixel = 0; x_pixel < 8; x_pixel++) {
        uint8_t mask = 0x80 >> x_pixel;
        if ((sprite_byte & mask) != 0) {
            uint16_t x = (x_pixel + vx) % 64; //offset + actual value and then we prevent overflow
            uint16_t y = (y_row + vy) % 32; //offset + actual value and then we prevent overflow
            uint16_t draw_index = (y * 64) + x; //Jump to the next line in the flat array and add the horizontal offset

            if (cpu->gfx[draw_index] == 1 && (sprite_byte & mask)) { //Detect collision, if both are 1, we have a collision, then we store at VF.
                cpu->registers[0x0F] = 1;
            };

            cpu->gfx[draw_index] ^= (sprite_byte & mask) ? 1 : 0; //XOR to turn on/off the pixel in question.
            };
        }; 
    };
};

// Ex9E - Skip next instruction if key with the value of Vx is pressed.
void OP_Ex9E(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    if (cpu->keys[cpu->registers[vx]]) {
        cpu->program_counter += 4;
    } else {
        cpu->program_counter += 2;
    };
};

//ExA1 - Skip next instruction if key with the value of Vx is not pressed.
void OP_ExA1(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    if (cpu->keys[cpu->registers[vx]] == 0) {
        cpu->program_counter += 4;
    } else {
        cpu->program_counter += 2;
    };
};

//Fx07 - Set Vx = delay timer value.
void OP_Fx07(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    cpu->delay_timer = cpu->registers[vx];

    cpu->program_counter += 2;
};

//Fx0A Wait for a key press, store the value of the key in Vx. All execution stops until a key is pressed, then the value of that key is stored in Vx.
void OP_Fx0A(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00 >> 8u;
    
    for (int i = 0; i < 16; i++) { //Loop over the keyboard and check if any of the keys are being pressed.
        
        if (cpu->keys[i] == 1) {
            cpu->registers[vx] = i;
            cpu->program_counter += 2;
            return;
        } else if (cpu->keys[i] == 0){
            continue;
        } else if (i == 15 && cpu->keys[15] == 0){
            return;
        } 

    }; 
};

//Fx15 - Set delay timer = Vx
void OP_Fx15(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    cpu->delay_timer = cpu->registers[vx]; 
};

//Fx18 - Set sound timer = Vx
void OP_Fx18(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    cpu->sound_timer = cpu->registers[vx];
};

//Fx1E - Set I = I + vx
void OP_Fx1E(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    cpu->index += cpu->registers[vx];
};

//Fx29 - Set I = location of sprite for digit Vx.
void OP_Fx29(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u;

    cpu->index = FONTSET_START_ADDRESS + (cpu->registers[vx] * 5);
   
};

//Fx33 - The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
void OP_Fx33(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;
    uint8_t value = cpu->registers[vx];

   //Ones-place
   cpu->memory[cpu->index + 2] = value % 10;
   value /= 10;

   //Tens-place
   cpu->memory[cpu->index + 1] = value % 10;
   value /= 10;

   //Hundreds-place
   cpu->memory[cpu->index] = value % 10; 
};

//Fx55 - Store registers V0 through Vx in memory starting at location I.
void OP_Fx55(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;
    uint16_t index = cpu->index;

    for (uint8_t i = 0; i <= vx; i++) {
        cpu->memory[index + i] = cpu->registers[i];
    };
};

//Fx65 - Read registers V0 through Vx from memory starting at location I.
void OP_Fx65(chip_8 *cpu) {
    uint8_t vx = cpu->opcode & 0x0F00u >> 8u;

    for (uint8_t i = 0; i <= vx; i++) {
        cpu->registers[i] = cpu->memory[cpu->index];
    };
};