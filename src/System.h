#include <cstdint>
#include <fstream>
#include "Instruction.h"

using namespace std;

#ifndef SYSTEM_H
#define SYSTEM_H

#define MEMORY_SIZE_BYTES 4294967296
#define REGISTERS_SIZE 32

#define ADDR_INSTR 0x10000000
#define ADDR_DATA 0x20000000
#define ADDR_GETC 0x30000000
#define ADDR_PUTC 0x30000004

class System {
private:
    uint32_t pc = ADDR_INSTR;
    uint32_t hi = 0;
    uint32_t lo = 0;
    uint32_t registers[REGISTERS_SIZE] = {0};
    uint8_t memory[MEMORY_SIZE_BYTES] = {0};

public:
    System(){};
    void start();
    void setMemoryFromStream(ifstream *stream);
    void executeInstruction(Instruction *instruction);

    // Memory
    uint32_t readMemoryWord(uint32_t address);
    uint8_t readMemoryByte(uint32_t address);
    void writeMemoryWord(uint32_t address, uint32_t word);
    void writeMemoryByte(uint32_t address, uint8_t byte);

    // Registers
    uint32_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint32_t word);
};


#endif
