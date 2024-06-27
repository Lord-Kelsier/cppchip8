#include "cpu.h"
#include <iostream>
#include <string>

void CPU::drawSprite() {
    /*The graphics system: 
    The chip 8 has one instruction that draws sprite to 
    the screen. Drawing is done in XOR mode and if a pixel 
    is turned off as a result of drawing, the VF register is 
    set. This is used for collision detection*/
    return;
    
}

void CPU::initialize() {
    // initialize register and memory once
    return;

}

int groupThree(unsigned short first, unsigned short second, unsigned short third) {
    return (first << 8) + (second << 4) + third;
}

unsigned short int groupTwo(unsigned short first, unsigned short second) {
    return (first << 4) + second;
}

void CPU::decodeOpcode(unsigned short first, unsigned short second, unsigned short third, unsigned short fourth) {
    if (first == 0x0) {
        int remainder = groupThree(second, third, fourth);
        if (remainder == 0x0E0) {
            // clearScreen()
        } else if (remainder == 0x0EE) {
            // return from subrutine
        } else {
            // Calls machine code routine (RCA 1802 for COSMAC VIP) at address NNN. Not necessary for most ROMs.[22]
        }
    } else if (first == 0x1) {
        int remainder = groupThree(second, third, fourth);
        // goto remainder
    } else if (first == 0x2) {
        int remainder = groupThree(second, third, fourth);
        // call subroutine at remainder (0xNNN)()
    } else if (first == 0x3) {
        unsigned short remainder = groupTwo(third, fourth);
        // Skips the next instruction if VX equals NN (usually the next instruction is a jump to skip a code block).[22]
    } else if (first == 0x4) {
        unsigned short remainder = groupTwo(third, fourth);
        // Skips the next instruction if VX does not equal NN (usually the next instruction is a jump to skip a code block).[22]
    } else if (first == 0x5) {
        // Skips the next instruction if VX equals VY (usually the next instruction is a jump to skip a code block).[22]
    } else if (first == 0x6) {
        
    }
    return;
}

void CPU::setKeys() {
    return;
}

void CPU::loadGame(std::string game) {
    return;
}

void CPU::emulateCycle() {
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];
    opcode = 0x1AF0;
    unsigned short int 
        firstHalfByte,
        secodnHalfByte,
        thirdHalfByte,
        fourthHalfByte;
    firstHalfByte = opcode >> 12;
    secodnHalfByte = (opcode & 0x0F00) >> 8 ;
    thirdHalfByte = (opcode & 0x00F0) >> 4 ;
    fourthHalfByte = opcode & 0x000F;
    decodeOpcode(firstHalfByte, secodnHalfByte, thirdHalfByte, fourthHalfByte);

    // Decode Opcode
    // Execute Opcode

    // Update timers
    return;
}
