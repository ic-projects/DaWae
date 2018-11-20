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
    Instruction *decodedInstruction = nullptr;
    int32_t fetchedInstruction = 0;
    int32_t pc = ADDR_INSTR;
    int32_t hi = 0;
    int32_t lo = 0;
    int32_t registers[REGISTERS_SIZE] = {0};
    int8_t memoryInstr[MEMORY_INSTR_SIZE] = {0};
    int8_t memoryData[MEMORY_DATA_SIZE] = {0};

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
    void _nor(Instruction *instruction);
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
    int32_t readMemoryWord(int32_t address);
    int16_t readMemoryHalfWord(int32_t address);
    int8_t readMemoryByte(int32_t address);
    void writeMemoryWord(int32_t address, int32_t word);
    void writeMemoryByte(int32_t address, int8_t byte);
    void writeMemoryHalfWord(int32_t address, int16_t halfWord);

    // Registers
    int32_t readRegister(int8_t reg);
    void writeRegister(int8_t reg, int32_t word);

    // Get lower 8 bits of $2 register
    int8_t getExitCode();
};


#endif
