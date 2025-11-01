#pragma once
#include <stdio.h>
#include "cpu.h"

//Handler funtions for opcodes:
void OP_00E0(chip_8 *cpu); 

void OP_00EE(chip_8 *cpu); 

void OP_1nnn(chip_8 *cpu);

void OP_2nnn(chip_8 *cpu);

void OP_3xkk(chip_8 *cpu);

void OP_4xkk(chip_8 *cpu);

void OP_5xy0(chip_8 *cpu);

void OP_6xkk(chip_8 *cpu);

void OP_7xkk(chip_8 *cpu);

void OP_8xy0(chip_8 *cpu);

void OP_8xy1(chip_8 *cpu);

void OP_8xy2(chip_8 *cpu);

void OP_8xy3(chip_8 *cpu);

void OP_8xy4(chip_8 *cpu);

void OP_8xy5(chip_8 *cpu);

void OP_8xy6(chip_8 *cpu);

void OP_8xy7(chip_8 *cpu);

void OP_8xyE(chip_8 *cpu);

void OP_9xy0(chip_8 *cpu);

void OP_Annn(chip_8 *cpu);

void OP_Bnnn(chip_8 *cpu);

void OP_cxkk(chip_8 *cpu);

void OP_Dxyn(chip_8 *cpu);

void OP_Ex9E(chip_8 *cpu);

void OP_ExA1(chip_8 *cpu);

void OP_Fx07(chip_8 *cpu);

void OP_Fx0A(chip_8 *cpu);

void OP_Fx15(chip_8 *cpu);

void OP_Fx18(chip_8 *cpu);

void OP_Fx1E(chip_8 *cpu);

void OP_Fx29(chip_8 *cpu);

void OP_Fx33(chip_8 *cpu);

void OP_Fx55(chip_8 *cpu);

void OP_Fx65(chip_8 *cpu);

//Table of function pointers:
void (*mainFuncTable[16])(chip_8 *cpu);
void (*funcTable0[2])(chip_8 *cpu);
void (*funcTable8[16])(chip_8 *cpu);
void (*funcTableE[2])(chip_8 *cpu);
void (*funcTableF[16])(chip_8 *cpu);

//Handler functions for the tables that contain the function pointers:
void handleFuncTable0(chip_8 *cpu);
void handleFuncTable8(chip_8 *cpu);
void handleFuncTableE(chip_8 *cpu);
void handleFuncTableF(chip_8 *cpu);
void handleMainFuncTable(chip_8 *cpu);