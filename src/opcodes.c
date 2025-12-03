#include "opcodes.h"

//OPCODES

//00E0 CLS - Clear the screen
void OP_00E0(chip_8 *cpu) {
    printf("00E0\n");
    memset(cpu->gfx, 0, sizeof(cpu->gfx));
}

//00EE RET - The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
void OP_00EE(chip_8 *cpu) {
    printf("00EE\n");
    cpu->program_counter = cpu->stack[cpu->stack_pointer];
    --cpu->stack_pointer;
}

//1nnn JMP - Jump to location nnn
void OP_1nnn(chip_8 *cpu) {
    printf("1nnn\n");
    uint16_t address = (cpu->opcode & 0x0FFFu);
    cpu->program_counter = address;
}

//2nnn CALL - The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
void OP_2nnn(chip_8 *cpu) {
    printf("2nnn\n");
    uint16_t address = (cpu->opcode & 0x0FFFu);
    ++cpu->stack_pointer;
    cpu->stack[cpu->stack_pointer] = cpu->program_counter;
    cpu->program_counter = address;  
}

//3xkk Skip next instruction if Vx = kk.
void OP_3xkk(chip_8 *cpu) {
    printf("3xkk\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8;
    uint8_t kk = (cpu->opcode & 0x00FFu);

    if (cpu->registers[vx] == kk) {
        cpu->program_counter += 2;
    };
}

//4xkk - Skip next instruction if Vx != kk.
void OP_4xkk(chip_8 *cpu) {
    printf("4xkk\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t kk = (cpu->opcode & 0x00FFu);

    if (cpu->registers[vx] != kk) {
        cpu->program_counter += 2;
    };
}

//5xy0 - Skip next instruction if Vx = Vy.
void OP_5xy0(chip_8 *cpu) {
    printf("5xy0\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->registers[vx] == cpu->registers[vy]) {
        cpu->program_counter += 2;
    };
}

//6xkk - Set Vx = kk.
void OP_6xkk(chip_8 *cpu) {
    printf("6xkk\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t kk = (cpu->opcode & 0x00FFu);

    cpu->registers[vx] = kk;
}

//7xkk - Set Vx = Vx + kk.
void OP_7xkk(chip_8 *cpu) {
    printf("7xkk\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t kk = (cpu->opcode & 0x00FFu);

    cpu->registers[vx] += kk;
}

//8xy0 - Set Vx = Vy.
void OP_8xy0(chip_8 *cpu) {
    printf("8xy0\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] = cpu->registers[vy];
}

//8xy1 - Set Vx = Vx OR Vy
void OP_8xy1(chip_8 *cpu) {
    printf("8xy1\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] |= cpu->registers[vy];
}

//8xy2 - Set Vx = Vx AND Vy.
void OP_8xy2(chip_8 *cpu) {
    printf("8xy2\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] &= cpu->registers[vy];
}

//8xy3 - Set Vx = Vx XOR Vy.
void OP_8xy3(chip_8 *cpu) {
    printf("8xy3\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    cpu->registers[vx] ^= cpu->registers[vy];
}

//8xy4 - The values of Vx and Vy are added together. 
//If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
void OP_8xy4(chip_8 *cpu) {
    printf("8xy4\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    uint16_t sum = cpu->registers[vx] + cpu->registers[vy];

    if (sum > 255u) {
        cpu->registers[15] = 1;
    } else {
        cpu->registers[15] = 0;
    };

    cpu->registers[vx] = sum & 0xFFu;
}

//8xy5 - If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void OP_8xy5(chip_8 *cpu) {
    printf("8xy5\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;
    
    if (cpu->registers[vx] > cpu->registers[vy]) {
        cpu->registers[15] = 1;
    } else {
        cpu->registers[15] = 0;
    };

    cpu->registers[vx] -= cpu->registers[vy];
}

//8xy6 - If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
void OP_8xy6(chip_8 *cpu) {
    printf("8xy6\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->registers[15] = (cpu->registers[vx] & 0x1u);

    cpu->registers[vx] >>= 1; //Every bit shift by one, is a division of the original value by 2; 
}

//8xy7 - If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
void OP_8xy7(chip_8 *cpu) {
    printf("8xy7\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->registers[vy] > cpu->registers[vx]) {
        cpu->registers[15] = 1;
    } else {
        cpu->registers[15] = 0;
    };

    cpu->registers[vx] -= cpu->registers[vy];
}

//8xyE - If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
void OP_8xyE(chip_8 *cpu) {
    printf("8xyE\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
   
    cpu->registers[0xF] = (cpu->registers[vx] & 0x80u) >> 7u;

    cpu->registers[vx] <<= 1; //The opposite of 8xy6
}

//9xy0 - The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
void OP_9xy0(chip_8 *cpu) {
    printf("9xy0\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u;

    if (cpu->registers[vx] != cpu->registers[vy]) {
        cpu->program_counter +=2;
    };
}

//Annn - The value of register I is set to nnn.
void OP_Annn(chip_8 *cpu) {
    printf("Annn\n");
    uint16_t address = (cpu->opcode & 0x0FFFu);

    cpu->index = address;
}

//Bnnn - The program counter is set to nnn plus the value of V0.
void OP_Bnnn(chip_8 *cpu) {
    printf("Bnnn\n");
    uint16_t address = (cpu->opcode & 0x0FFFu);

    cpu->program_counter = address + cpu->registers[0];
}

//cxkk - The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. 
void OP_Cxkk(chip_8 *cpu) {
    printf("Cxkk\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8;
    uint8_t kk = (cpu->opcode & 0x00FFu);
    int random_number = rand() % 256;

    cpu->registers[vx] = kk & random_number;
}

//Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void OP_Dxyn(chip_8 *cpu) {
    printf("Dxyn\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t vy = (cpu->opcode & 0x00F0u) >> 4u; 
    uint8_t height = (cpu->opcode & 0x000Fu);

    uint8_t x_pos = cpu->registers[vx] % 64;
    uint8_t y_pos = cpu->registers[vy] % 32;

    uint8_t sprite_byte;
    cpu->registers[0xF] = 0;

    for (uint16_t row = 0; row < height; ++row) {
        
        sprite_byte = cpu->memory[cpu->index + row];

        for (uint16_t col = 0; col < 8; ++col) {
        
            uint8_t sprite_pixel = sprite_byte & (0x80u >> col); 
            printf("Sprite pixel value: %x\n", sprite_pixel);
            uint32_t draw_index = (y_pos + row) * 64 + (x_pos + col);
            uint32_t screen_pixel = cpu->gfx[draw_index];
            

            if (sprite_pixel) {
                
                if (screen_pixel == 1) {
                    cpu->registers[15] = 1;
                }

                screen_pixel ^= 1;
                cpu->gfx[draw_index] = screen_pixel;
                printf("Value of screen pixel: %x\n", cpu->gfx[draw_index]);
            }
        };
    }; 
}

// Ex9E - Skip next instruction if key with the value of Vx is pressed.
void OP_Ex9E(chip_8 *cpu) {
    printf("Ex9E\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    if (cpu->keys[cpu->registers[vx]]) {
        printf("value of the key: %d", cpu->keys[cpu->registers[vx]]);
        cpu->program_counter += 2;
    };
}

//ExA1 - Skip next instruction if key with the value of Vx is not pressed.
void OP_ExA1(chip_8 *cpu) {
    printf("ExA1\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    if (!cpu->keys[cpu->registers[vx]]) {
        printf("value of the key: %d", cpu->keys[cpu->registers[vx]]);
        cpu->program_counter += 2;
    };
}

//Fx07 - Set Vx = delay timer value.
void OP_Fx07(chip_8 *cpu) {
    printf("Fx07\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

     cpu->registers[vx] = cpu->delay_timer;
}

//Fx0A Wait for a key press, store the value of the key in Vx. All execution stops until a key is pressed, then the value of that key is stored in Vx.
void OP_Fx0A(chip_8 *cpu) {
    printf("Fx0A\n");
    uint8_t vx = (cpu->opcode & 0x0F00) >> 8u;
       
        for (int i = 0; i <= 15; i++) { //Loop over the keyboard and check if any of the keys are being pressed.
        
            if (cpu->keys[i] == 1) {
                printf("A key was pressed, execution resumed\n");
                cpu->registers[vx] = i;
                return;
        }; 
    }; 

    cpu->program_counter -= 2;
}

//Fx15 - Set delay timer = Vx
void OP_Fx15(chip_8 *cpu) {
    printf("Fx15\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->delay_timer = cpu->registers[vx]; 
}

//Fx18 - Set sound timer = Vx
void OP_Fx18(chip_8 *cpu) {
    printf("Fx18\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->sound_timer = cpu->registers[vx];
}

//Fx1E - Set I = I + vx
void OP_Fx1E(chip_8 *cpu) {
    printf("Fx1E\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->index += cpu->registers[vx];
}

//Fx29 - Set I = location of sprite for digit Vx.
void OP_Fx29(chip_8 *cpu) {
    printf("Fx29\n"); 
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    cpu->index = FONTSET_START_ADDRESS + (cpu->registers[vx] * 5);
   
}

//Fx33 - The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
void OP_Fx33(chip_8 *cpu) {
    printf("Fx33\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint8_t value = cpu->registers[vx];

   //Ones-place
   cpu->memory[cpu->index + 2] = value % 10;
   value /= 10;

   //Tens-place
   cpu->memory[cpu->index + 1] = value % 10;
   value /= 10;

   //Hundreds-place
   cpu->memory[cpu->index] = value % 10; 
}

//Fx55 - Store registers V0 through Vx in memory starting at location I.
void OP_Fx55(chip_8 *cpu) {
    printf("Fx55\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;
    uint16_t index = cpu->index;

    for (uint8_t i = 0; i <= vx; i++) {
        cpu->memory[index + i] = cpu->registers[i];
    };
}

//Fx65 - Read registers V0 through Vx from memory starting at location I.
void OP_Fx65(chip_8 *cpu) {
    printf("Fx65\n");
    uint8_t vx = (cpu->opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= vx; i++) {
        cpu->registers[i] = cpu->memory[cpu->index + i];
    };
}

//Table of function pointers:

void (*funcTable0[0xF])(chip_8 *cpu) = { //They all start with 00E but the last digit is different.
        [0x00] = OP_00E0,
        [0xE] = OP_00EE,
};

void (*funcTable8[0xF + 1])(chip_8 *cpu) = { //The last digit is different
    [0x00] = OP_8xy0,
    [0x01] = OP_8xy1, 
    [0x02] = OP_8xy2,
    [0x03] = OP_8xy3,
    [0x04] = OP_8xy4, 
    [0x05] = OP_8xy5, 
    [0x06] = OP_8xy6,
    [0x07] = OP_8xy7, 
    [0x0E] = OP_8xyE,
};

void (*funcTableE[0xE + 1])(chip_8 *cpu) = { //First digit repeats but the last two are different
    [0x01] = OP_ExA1, 
    [0x0E] = OP_Ex9E,
};

void (*funcTableF[0x66])(chip_8 *cpu) = { //Same as above, but the notation starts with F.
    [0x07] = OP_Fx07, 
    [0x0A] = OP_Fx0A,
    [0x15] = OP_Fx15, 
    [0x18] = OP_Fx18,
    [0x1E] = OP_Fx1E, 
    [0x29] = OP_Fx29,
    [0x33] = OP_Fx33,
    [0x55] = OP_Fx55,
    [0x65] = OP_Fx65,
};

void (*mainFuncTable[16])(chip_8 *cpu) = {
   [0x00] = handleFuncTable0, 
   [0x01] = OP_1nnn,
   [0x02] = OP_2nnn,
   [0x03] = OP_3xkk,
   [0x04] = OP_4xkk, 
   [0x05] = OP_5xy0,
   [0x06] = OP_6xkk, 
   [0x07] = OP_7xkk,
   [0x08] = handleFuncTable8,
   [0x09] = OP_9xy0, 
   [0x0A] = OP_Annn, 
   [0x0B] = OP_Bnnn,
   [0x0C] = OP_Cxkk, 
   [0x0D] = OP_Dxyn, 
   [0x0E] = handleFuncTableE, 
   [0x0F] = handleFuncTableF, 
};

//Handler functions for sub tables
void handleFuncTable0(chip_8 *cpu) {
    uint8_t index = cpu->opcode & 0x000Fu;
    
    funcTable0[index](cpu);
}

void handleFuncTable8(chip_8 *cpu) {
    uint8_t index = cpu->opcode & 0x000Fu;

    funcTable8[index](cpu);
}

void handleFuncTableE(chip_8 *cpu) {
    uint8_t index = cpu->opcode & 0x000Fu;

    funcTableE[index](cpu);
}

void handleFuncTableF(chip_8 *cpu) {
    uint8_t index = cpu->opcode & 0x00FFu;

    funcTableF[index](cpu);
}

void handleMainFuncTable(chip_8 *cpu) { //Now we just determine the index of where the opcode is located and execute it.
    uint8_t index = (cpu->opcode & 0xF000u) >> 12u;
        //printf("Executing opcode: %x\n", cpu->opcode);
        printf("Index is %u\n", index);


    mainFuncTable[index](cpu);

}