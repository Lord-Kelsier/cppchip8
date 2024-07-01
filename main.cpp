#include "cpu.h"

CPU cpu;

int main(int argc, char** argv) {
    // Set up render system and register input callbacks
    // setupGraphics();
    // setupInput();
    /*Setup the graphics (window size, display mode, etc) and input system (bind callbacks)*/

    // initialize chip8 system and load the game into the memory
    cpu.initialize();
    cpu.loadGame("pong");

    // Emulation loop
    for (;;) {
        // Emulate one cycle
        cpu.emulateCycle();

        // If the draw flag is set, update screen
        if (cpu.drawFlag) {
            // drawGraphics()
        }
        // store key press state (Press and Release)
        cpu.setKeys();
        //wait(1/60 second)
        break;
    }
    return 0;
}