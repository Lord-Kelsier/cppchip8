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

unsigned short int groupThree(unsigned short first, unsigned short second, unsigned short third) {
    return (first << 8) | (second << 4) | third;
}

unsigned short int groupTwo(unsigned short first, unsigned short second) {
    return (first << 4) | second;
}

void CPU::returnSubroutine() {
    sp--;
    unsigned short int pointer = stack[sp];
    pc = pointer;
}

void CPU::gotoDir(unsigned short direction) {
    pc = direction;
}

void CPU::callSubRoutine(unsigned short direction) {
    stack[sp] = pc;
    sp++;
    pc = direction;
}

void CPU::ifJump(unsigned short value1, unsigned short value2, IfCond conditional){
    switch (conditional)
    {
    case equ:
        if (value1 == value2) {
            pc += 4;
        }
        break;
    case neq:
        if (value1 != value2) {
            pc += 4;
        }
        break;
    default:
        break;
    }
}


void CPU::decodeOpcode(unsigned short first, unsigned short second, unsigned short third, unsigned short fourth) {
    if (first == 0x0) {
        unsigned short remainder = groupThree(second, third, fourth);
        if (remainder == 0x0E0) {
            // clearScreen()
        } else if (remainder == 0x0EE) {
            returnSubroutine();
        } else {
            // Calls machine code routine (RCA 1802 for COSMAC VIP) at address NNN. Not necessary for most ROMs.[22]
        }
    } else if (first == 0x1) {
        unsigned short remainder = groupThree(second, third, fourth);
        gotoDir(remainder);
    } else if (first == 0x2) {
        unsigned short remainder = groupThree(second, third, fourth);
        callSubRoutine(remainder);
    } else if (first == 0x3) {
        unsigned short remainder = groupTwo(third, fourth);
        ifJump(V[second], remainder, equ);
    } else if (first == 0x4) {
        unsigned short remainder = groupTwo(third, fourth);
        ifJump(V[second], remainder, neq);
    } else if (first == 0x5) {
        ifJump(V[second], V[third], equ);
    } else if (first == 0x6) {
        V[second] = (third << 4 | fourth) & 0xFF;
    } else if (first == 0x7) {
        V[second] += (third << 4 | fourth) & 0xFF; 
    } else if (first == 0x8) {
        if (fourth == 0x0) {
            V[second] = V[third];
        } else if (fourth == 0x1) {
            V[second] |= V[third];
        } else if (fourth == 0x2) {
            V[second] &= V[third];
        } else if (fourth == 0x3) {
            V[second] ^= V[third];
        } else if (fourth == 0x4) {
            if (V[second] + V[third] > 0xFF) {
                V[0xF] = 1; 
                V[second] = (V[second] + V[third]) & 0xFF;
            } else {
                V[0xF] = 0;
                V[second] += V[third];
            }
        } else if (fourth == 0x5) {
            if (V[second] < V[third]) {
                V[0xF] = 0;
                V[second] = V[third] - V[second];
            } else {
                V[0xF] = 1;
                V[second] -= V[third];
            }
        } else if (fourth == 0x6) {
            V[0xF] = 0b1 & V[second];
            V[second] >>= 1;
        } else if (fourth == 0x7) {
            if (V[second] < V[third]) {
                V[0xF] = 1;
                V[second] = V[third] - V[second];
            } else {
                V[0xF] = 0;
                V[second] = V[second] - V[third];
            }
        } else if (fourth == 0xE) {
            V[0xF] = (0b1 << 7) & V[second];
            V[second] = (V[second] << 1) & 0xFF;
        }
    } else if (first == 0x9) {
        ifJump(V[second], V[third], neq);
    } else if (first == 0xA) {
        unsigned short remainder = groupThree(second, third, fourth);
        I = remainder;
    } else if (first == 0xB) {
        unsigned short remainder = groupThree(second, third, fourth);
        pc = V[0x0] + remainder;
    } else if (first == 0xC) {
        unsigned short remainder = groupTwo(third, fourth);
        V[second] = (rand() & remainder) & 0xFF; 
    } else if (first == 0xD) {
        // Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value does not change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that does not happen.[22]
    } else if (first == 0xE) {
        if (third == 0x9 && fourth == 0xE) {
            // Skips the next instruction if the key stored in VX is pressed (usually the next instruction is a jump to skip a code block).[22]
        } else if (third == 0xA && fourth == 0x1) {
            //Skips the next instruction if the key stored in VX is not pressed (usually the next instruction is a jump to skip a code block).[22]
        }
    } else if (first == 0xF) {
        unsigned short lastTwo = groupTwo(third, fourth);
        if (lastTwo == 0x07) {
            // Sets VX to the value of the delay timer.[
        } else if (lastTwo == 0x0A) {
            // A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event).[22]
        } else if (lastTwo == 0x15) {
            //	Sets the delay timer to VX.[22]
        } else if (lastTwo == 0x18) {
            // 	Sets the sound timer to VX.[22]
        } else if (lastTwo == 0x1E) {
            I += V[second];
        } else if (lastTwo == 0x29) {
            // Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.[22]
        } else if (lastTwo == 0x33) {
            // Stores the binary-coded decimal representation of VX, with the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.[22]
        } else if (lastTwo == 0x55) {
            // Stores from V0 to VX (including VX) in memory, starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.[d][22]
        } else if (lastTwo == 0x65) {
            // Fills from V0 to VX (including VX) with values from memory, starting at address I. The offset from I is increased by 1 for each value read, but I itself is left unmodified.[d][22]
        }
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
