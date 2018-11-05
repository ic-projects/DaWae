#include <iostream>
#include <bitset>
#include "System.h"
#include "Instruction.h"
#include "Errors.h"

void System::start() {
    while (pc != 0) {
        uint32_t raw = readMemoryWord(pc);

        // Check for zero instruction
        if (raw == 0) {
            exit(getExitCode());
        }

        auto *instruction = new Instruction(raw);
        executeInstruction(instruction);
        pc += WORD_SIZE_IN_BYTES;
    }
    exit(getExitCode());
}

void System::setMemoryFromStream(ifstream *stream) {
    // Read stream into memory starting at ADDR_INSTR
    stream->read((char *) memory + ADDR_INSTR, MEMORY_SIZE_BYTES);
}

void System::executeInstruction(Instruction *instruction) {
    switch (instruction->getOpcode()) {
        case R:
            executeRTypeInstruction(instruction);
            break;
        case ADDIU:
            _addiu(instruction);
            break;
        case SLTI:
            _slti(instruction);
            break;
        case SLTIU:
            _sltiu(instruction);
            break;
        case ANDI:
            _andi(instruction);
            break;
        case ORI:
            _ori(instruction);
            break;
        case XORI:
            _xori(instruction);
            break;
        case LUI:
            _lui(instruction);
            break;
        case BEQ:
            _beq(instruction);
            break;
        case BNE:
            _bne(instruction);
            break;
        case BLEZ:
            _blez(instruction);
            break;
        case BGTZ:
            _bgtz(instruction);
            break;
        case B_SPEC:
            _b_spec(instruction);
            break;
        case LB:
            _lb(instruction);
            break;
        case LH:
            _lh(instruction);
            break;
        case LBU:
            _lbu(instruction);
            break;
        case LW:
            _lw(instruction);
            break;
        case SB:
            _sb(instruction);
            break;
        case SH:
            _sh(instruction);
            break;
        case SW:
            _sw(instruction);
            break;
        case ADDI:
            _addi(instruction);
            break;
        case LHU:
            _lhu(instruction);
            break;
        case LWL:
            _lwl(instruction);
            break;
        case LWR:
            _lwr(instruction);
            break;
        case J:
            _j(instruction);
            break;
        case JAL:
            _jalr(instruction);
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
    if (address < ADDR_INSTR || (address >= ADDR_PUTC && address < (ADDR_PUTC + 4))) {
        cerr << "Attempted to read from an invalid or write-only memory address." << endl;
        exit(ERROR_MEMORY_EXCEPTION);
    }
    return memory[address];
}

uint16_t System::readMemoryHalfWord(uint32_t address) {
    uint16_t result = 0;
    for (uint8_t i = 0; i < HALF_WORD_SIZE_IN_BYTES / 2; i++) {
        result += readMemoryByte(address + i) << (8 * (HALF_WORD_SIZE_IN_BYTES - i - 1));
    }
    return result;
}

void System::writeMemoryWord(uint32_t address, uint32_t word) {
    for (uint8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
        auto byte = static_cast<uint8_t>(word >> (8 * (WORD_SIZE_IN_BYTES - i - 1)) & MASK_BYTE);
        writeMemoryByte(address + i, byte);
    }
}

void System::writeMemoryByte(uint32_t address, uint8_t byte) {
    if (address < ADDR_INSTR || (address >= ADDR_GETC && address < (ADDR_GETC + 4))) {
        cerr << "Attempted to write to an invalid or read-only memory address." << endl;
        exit(ERROR_MEMORY_EXCEPTION);
    }
    memory[address] = byte;
}

uint32_t System::readRegister(uint8_t reg) {
    if (reg < REGISTERS_SIZE) {
        return registers[reg];
    }
    cerr << "Attempted to read an invalid register." << endl;
    exit(ERROR_INVALID_INSTRUCTION);
}

void System::writeRegister(uint8_t reg, uint32_t word) {
    if (reg >= REGISTERS_SIZE) {
        cerr << "Attempted to write to an invalid register." << endl;
        exit(ERROR_INVALID_INSTRUCTION);
    }
    registers[reg] = word;
}

uint8_t System::getExitCode() {
    return(readRegister(2) & 0x8F);
}

void System::executeRTypeInstruction(Instruction *instruction) {
    switch (instruction->getFunctionCode()) {
        case SLL:
            _sll(instruction);
            break;
        case SRL:
            _srl(instruction);
            break;
        case SRA:
            _sra(instruction);
            break;
        case ADD:
            _add(instruction);
            break;
        case ADDU:
            _addu(instruction);
            break;
        case SUB:
            _sub(instruction);
            break;
        case SUBU:
            _subu(instruction);
            break;
        case AND:
            _and(instruction);
            break;
        case OR:
            _or(instruction);
            break;
        case XOR:
            _xor(instruction);
            break;
        case NOR:
            _nor(instruction);
            break;
        case SLT:
            _slt(instruction);
            break;
        case SLTU:
            _sltu(instruction);
            break;
        case JR:
            _jr(instruction);
            break;
        case JALR:
            _jalr(instruction);
            break;
        case DIV:
            _div(instruction);
            break;
        case DIVU:
            _divu(instruction);
            break;
        case MFHI:
            _mfhi(instruction);
            break;
        case MFLO:
            _mflo(instruction);
            break;
        case MTHI:
            _mthi(instruction);
            break;
        case MTLO:
            _mtlo(instruction);
            break;
        case MULT:
            _mult(instruction);
            break;
        case MULTU:
            _multu(instruction);
            break;
    }
}

// R-Type Instructions
void System::_sll(Instruction *instruction) {

}

void System::_srl(Instruction *instruction) {

}

void System::_sra(Instruction *instruction) {

}

void System::_add(Instruction *instruction) {

}

void System::_addu(Instruction *instruction) {
    uint32_t result = readRegister(instruction->getRegisterS())
                    + readRegister(instruction->getRegisterT());
    writeRegister(instruction->getRegisterD(), result);
}

void System::_sub(Instruction *instruction) {

}

void System::_subu(Instruction *instruction) {

}

void System::_and(Instruction *instruction) {

}

void System::_or(Instruction *instruction) {

}

void System::_xor(Instruction *instruction) {

}

void System::_nor(Instruction *instruction) {

}

void System::_slt(Instruction *instruction) {

}

void System::_sltu(Instruction *instruction) {

}

void System::_jr(Instruction *instruction) {

}

void System::_jalr(Instruction *instruction) {

}

void System::_div(Instruction *instruction) {

}

void System::_divu(Instruction *instruction) {

}

void System::_mfhi(Instruction *instruction) {

}

void System::_mflo(Instruction *instruction) {

}

void System::_mthi(Instruction *instruction) {

}

void System::_mtlo(Instruction *instruction) {

}

void System::_mult(Instruction *instruction) {

}

void System::_multu(Instruction *instruction) {

}

void System::_addiu(Instruction *instruction) {
    uint32_t result = readRegister(instruction->getRegisterS())
                    + instruction->getImmediateOperand();
    writeRegister(instruction->getRegisterT(), result);
}

void System::_slti(Instruction *instruction) {

}

void System::_sltiu(Instruction *instruction) {

}

void System::_andi(Instruction *instruction) {

}

void System::_ori(Instruction *instruction) {

}

void System::_xori(Instruction *instruction) {

}

void System::_lui(Instruction *instruction) {

}

void System::_beq(Instruction *instruction) {

}

void System::_bne(Instruction *instruction) {

}

void System::_blez(Instruction *instruction) {

}

void System::_bgtz(Instruction *instruction) {

}

void System::_b_spec(Instruction *instruction) {

}

void System::_lb(Instruction *instruction) {
    uint8_t byte = readMemoryByte( instruction->getImmediateOperand()
                                   + instruction->getRegisterS());
    writeRegister(instruction->getRegisterT(), byte);
}

void System::_lh(Instruction *instruction) {
    uint16_t word = readMemoryHalfWord( instruction->getImmediateOperand()
                                        + instruction->getRegisterS());
    writeRegister(instruction->getRegisterT(), word);
}

void System::_lbu(Instruction *instruction) {

}

void System::_lw(Instruction *instruction) {
    uint32_t word = readMemoryWord( instruction->getImmediateOperand()
                                    + instruction->getRegisterS());
    writeRegister(instruction->getRegisterT(), word);
}

void System::_sb(Instruction *instruction) {

}

void System::_sh(Instruction *instruction) {

}

void System::_sw(Instruction *instruction) {

}

void System::_addi(Instruction *instruction) {

}

void System::_lhu(Instruction *instruction) {

}

void System::_lwl(Instruction *instruction) {

}

void System::_lwr(Instruction *instruction) {

}

void System::_sllv(Instruction *instruction) {

}

void System::_srav(Instruction *instruction) {

}

void System::_srlv(Instruction *instruction) {

}

void System::_j(Instruction *instruction) {

}

void System::_jal(Instruction *instruction) {

}
