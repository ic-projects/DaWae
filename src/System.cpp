#include <iostream>
#include <bitset>
#include "System.h"
#include "Instruction.h"
#include "Errors.h"

void System::start() {
    while (pc != 0) {
        uint32_t raw = readMemoryWord(pc);
        auto *instruction = new Instruction(raw);
        executeInstruction(instruction);
        pc += WORD_SIZE_IN_BYTES;
    }
}

void System::setMemoryFromStream(ifstream *stream) {
    // Read stream into memory starting at ADDR_INSTR
    stream->read((char *) memory + ADDR_INSTR, MEMORY_SIZE_BYTES);
}

void System::executeInstruction(Instruction *instruction) {
    switch (instruction->getOpcode()) {
        case R:
            break;
        case ADDIU:
            break;
        case SLTI:
            break;
        case SLTIU:
            break;
        case ANDI:
            break;
        case ORI:
            break;
        case XORI:
            break;
        case LUI:
            break;
        case BEQ:
            break;
        case BNE:
            break;
        case BLEZ:
            break;
        case BGTZ:
            break;
        case B_SPEC:
            break;
        case LB:
            break;
        case LH:
            break;
        case LBU:
            break;
        case LW:
            break;
        case SB:
            break;
        case SH:
            break;
        case SW:
            break;
        case ADDI:
            break;
        case LHU:
            break;
        case LWL:
            break;
        case LWR:
            break;
        case J:
            break;
        case JAL:
            break;
    }
}

uint32_t System::readMemoryWord(uint32_t address) {
    uint32_t result = 0;
    for (uint8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
        result += readMemoryByte(address + i) << (8 * (WORD_SIZE_IN_BYTES - i - 1));
    }
    return result;
}

uint8_t System::readMemoryByte(uint32_t address) {
    if (address < ADDR_INSTR || (address <= ADDR_PUTC && address < (ADDR_PUTC + 4))) {
        cerr << "Attempting to read from a write-only memory address." << endl;
        exit(ERROR_MEMORY_EXCEPTION);
    }
    return memory[address];
}

void System::writeMemoryWord(uint32_t address, uint32_t word) {
    for (uint8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
        auto byte = static_cast<uint8_t>(word >> (8 * (WORD_SIZE_IN_BYTES - i - 1)) & BYTE_MASK);
        writeMemoryByte(address + i, byte);
    }
}

void System::writeMemoryByte(uint32_t address, uint8_t byte) {
    if (address < ADDR_INSTR || (address >= ADDR_GETC && address < (ADDR_GETC + 4))) {
        cerr << "Attempting to write to a read-only memory address." << endl;
        exit(ERROR_MEMORY_EXCEPTION);
    }
    memory[address] = byte;
}

uint32_t System::readRegister(uint8_t reg) {
    if (reg >= 0 && reg < REGISTERS_SIZE) {
        return registers[reg];
    }
    cerr << "Attempting to read an invalid register." << endl;
    exit(ERROR_INVALID_INSTRUCTION);
}

void System::writeRegister(uint8_t reg, uint32_t word) {
    if (reg < 0 && reg >= REGISTERS_SIZE) {
        cerr << "Attempting to write to an invalid register." << endl;
        exit(ERROR_INVALID_INSTRUCTION);
    }
    registers[reg] = word;
}
