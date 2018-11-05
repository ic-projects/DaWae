#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>

#define WORD_SIZE_IN_BYTES 4

// Masks
#define MASK_REG 0x1F
#define MASK_BYTE 0xFF
#define MASK_FUNCTION_CODE 0x3F
#define MASK_JUMP_ADDRESS 0x3FFFFFF
#define MASK_IMMEDIATE_OPERAND 0xFFFF

// Shifts
#define SHIFT_OPCODE 26
#define SHIFT_REG_S 21
#define SHIFT_REG_T 16
#define SHIFT_RED_D 11
#define SHIFT_SHIFT_AMOUNT 6

enum RTypeFunctionCode {
    SLL     = 0b000000,
    SRL     = 0b000010,
    SRA     = 0b000011,
    ADD     = 0b100000,
    ADDU    = 0b100001,
    SUB     = 0b100010,
    SUBU    = 0b100011,
    AND     = 0b100100,
    OR      = 0b100101,
    XOR     = 0b100110,
    NOR     = 0b100111,
    SLT     = 0b101010,
    SLTU    = 0b101011,
    JR      = 0b001000,
    JALR    = 0b001001,
    DIV     = 0b011010,
    DIVU    = 0b011011,
    MFHI    = 0b010000,
    MFLO    = 0b010010,
    MTHI    = 0b010001,
    MTLO    = 0b010011,
    MULT    = 0b011000,
    MULTU   = 0b011001,
};

enum InstructionOpcode {
    R       = 0b000000,

    // I-Type Instructions
    ADDIU   = 0b001001,
    SLTI    = 0b001010,
    SLTIU   = 0b001011,
    ANDI    = 0b001100,
    ORI     = 0b001101,
    XORI    = 0b001110,
    LUI     = 0b001111,
    BEQ     = 0b000100,
    BNE     = 0b000101,
    BLEZ    = 0b000110,
    BGTZ    = 0b000111,
    B_SPEC  = 0b000001,
    LB      = 0b100000,
    LH      = 0b100001,
    LBU     = 0b100100,
    LW      = 0b100011,
    SB      = 0b101000,
    SH      = 0b101001,
    SW      = 0b101011,
    ADDI    = 0b001000,
    LHU     = 0b100101,
    LWL     = 0b100010,
    LWR     = 0b100110,
    SLLV    = 0b000100,
    SRAV    = 0b000111,
    SRLV    = 0b000110,

    // J-Type Instructions
    J       = 0b000010,
    JAL     = 0b000011,
};

enum BTypeRegTCodes {
    BGEZ    = 0b00001,
    BGEZAL  = 0b10001,
    BLTZ    = 0b00000,
    BLTZAL  = 0b10000,
};

class Instruction {
private:
    uint32_t instruction;
public:
    explicit Instruction(uint32_t instruction) : instruction(instruction) {};
    InstructionOpcode getOpcode();
    uint8_t getRegisterS();
    uint8_t getRegisterT();
    uint8_t getRegisterD();
    uint8_t getShiftAmount();
    RTypeFunctionCode getFunctionCode();
    uint16_t getImmediateOperand();
    uint32_t getJumpAddress();
    void printRaw();
};

#endif
