#include <cstdint>
#include <fstream>
#include "Instruction.h"

using namespace std;

#ifndef SYSTEM_H
#define SYSTEM_H

#define MEMORY_INSTR_SIZE 0x1000000
#define MEMORY_DATA_SIZE 0x4000000
#define REGISTERS_SIZE 32

#define ADDR_NULL 0x0
#define ADDR_INSTR 0x10000000
#define ADDR_DATA 0x20000000
#define ADDR_GETC 0x30000000
#define ADDR_PUTC 0x30000004

class System {
private:
    uint32_t pc = ADDR_INSTR;
    uint32_t nextPC = ADDR_INSTR + WORD_SIZE_IN_BYTES;
    bool updatePC = true;

    uint32_t hi = 0;
    uint32_t lo = 0;
    uint32_t registers[REGISTERS_SIZE] = {0};
    uint8_t memoryInstr[MEMORY_INSTR_SIZE] = {0};
    uint8_t memoryData[MEMORY_DATA_SIZE] = {0};

    void setPC(uint32_t address);
    void incrementPC(uint32_t offset);

    // I-Type functions
    void _addiu(Instruction *instruction);
    void _slti(Instruction *instruction);
    void _sltiu(Instruction *instruction);
    void _andi(Instruction *instruction);
    void _ori(Instruction *instruction);
    void _xori(Instruction *instruction);
    void _lui(Instruction *instruction);
    void _beq(Instruction *instruction);
    void _bne(Instruction *instruction);
    void _blez(Instruction *instruction);
    void _bgtz(Instruction *instruction);
    void _b_spec(Instruction *instruction);
    void _lb(Instruction *instruction);
    void _lh(Instruction *instruction);
    void _lbu(Instruction *instruction);
    void _lw(Instruction *instruction);
    void _sb(Instruction *instruction);
    void _sh(Instruction *instruction);
    void _sw(Instruction *instruction);
    void _addi(Instruction *instruction);
    void _lhu(Instruction *instruction);
    void _lwl(Instruction *instruction);
    void _lwr(Instruction *instruction);
    void _sllv(Instruction *instruction);
    void _srav(Instruction *instruction);
    void _srlv(Instruction *instruction);
    void _j(Instruction *instruction);
    void _jal(Instruction *instruction);

    // R-Type functions
    void _sll(Instruction *instruction);
    void _srl(Instruction *instruction);
    void _sra(Instruction *instruction);
    void _add(Instruction *instruction);
    void _addu(Instruction *instruction);
    void _sub(Instruction *instruction);
    void _subu(Instruction *instruction);
    void _and(Instruction *instruction);
    void _or(Instruction *instruction);
    void _xor(Instruction *instruction);
    void _slt(Instruction *instruction);
    void _sltu(Instruction *instruction);
    void _jr(Instruction *instruction);
    void _jalr(Instruction *instruction);
    void _div(Instruction *instruction);
    void _divu(Instruction *instruction);
    void _mfhi(Instruction *instruction);
    void _mflo(Instruction *instruction);
    void _mthi(Instruction *instruction);
    void _mtlo(Instruction *instruction);
    void _mult(Instruction *instruction);
    void _multu(Instruction *instruction);

public:
    System(){};
    void start();
    void loadInstructionsFromStream(ifstream *stream);
    void executeInstruction(Instruction *instruction);
    void executeRTypeInstruction(Instruction *instruction);

    // Memory
    uint32_t readMemoryWord(uint32_t address);
    uint16_t readMemoryHalfWord(uint32_t address);
    uint8_t readMemoryByte(uint32_t address);
    void writeMemoryWord(uint32_t address, uint32_t word);
    void writeMemoryByte(uint32_t address, uint8_t byte);
    void writeMemoryHalfWord(uint32_t address, uint16_t halfWord);

    // Registers
    uint32_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint32_t word);
    void writeHIRegister(uint32_t word);
    void writeLORegister(uint32_t word);
    uint32_t readHIRegister();
    uint32_t readLORegister();

    // Get lower 8 bits of $2 register
    uint8_t getExitCode();
};


#endif
