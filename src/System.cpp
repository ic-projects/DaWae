#include <iostream>
#include <bitset>
#include "System.h"
#include "Instruction.h"
#include "Errors.h"
#include <limits>

void System::start() {
    bool hasStarted = false;
    while (pc != ADDR_NULL) {
        // Execute
        if (decodedInstruction != nullptr) {
            // Check for zero instruction
            if (decodedInstruction->getRaw() == 0) {
                exit(getExitCode());
            }
            executeInstruction(decodedInstruction);
        }

        // Decode
        if (hasStarted) {
            decodedInstruction = new Instruction(fetchedInstruction);
        } else {
            hasStarted = true;
        }

        // Fetch
        fetchedInstruction = readMemoryWord(pc);

        pc += WORD_SIZE_IN_BYTES;
    }
    exit(getExitCode());
}

void System::loadInstructionsFromStream(ifstream *stream) {
    // Read stream into memory starting at ADDR_INSTR
    stream->read((char *) memoryInstr, MEMORY_INSTR_SIZE);
}

void System::executeInstruction(Instruction *instruction) {
    switch (instruction->getOpcode()) {
        case R: executeRTypeInstruction(instruction); break;
        case ADDIU: _addiu(instruction); break;
        case SLTI: _slti(instruction); break;
        case SLTIU: _sltiu(instruction); break;
        case ANDI: _andi(instruction); break;
        case ORI: _ori(instruction); break;
        case XORI: _xori(instruction); break;
        case LUI: _lui(instruction); break;
        case BEQ: _beq(instruction); break;
        case BNE: _bne(instruction); break;
        case BLEZ: _blez(instruction); break;
        case BGTZ: _bgtz(instruction); break;
        case B_SPEC: _b_spec(instruction); break;
        case LB: _lb(instruction); break;
        case LH: _lh(instruction); break;
        case LBU: _lbu(instruction); break;
        case LW: _lw(instruction); break;
        case SB: _sb(instruction); break;
        case SH: _sh(instruction); break;
        case SW: _sw(instruction); break;
        case ADDI: _addi(instruction); break;
        case LHU: _lhu(instruction); break;
        case LWL: _lwl(instruction); break;
        case LWR: _lwr(instruction); break;
        case J: _j(instruction); break;
        case JAL: _jalr(instruction); break;
    }
}

uint32_t System::readMemoryWord(uint32_t address) {
    if (address % WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to read a word on a non aligned memory address." << endl;
        exit(ERROR_CPU_EXCEPTION);
    }

    if (address == ADDR_GETC) {
        return static_cast<int32_t>(getchar());
    }

    int32_t result = 0;
    for (int8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
        result += readMemoryByte(address + i) << (8 * (WORD_SIZE_IN_BYTES - i - 1));
    }
    return result;
}

uint8_t System::readMemoryByte(uint32_t address) {
    if (address >= ADDR_INSTR && address < ADDR_DATA) {
        return memoryInstr[address - ADDR_INSTR];
    }
    if (address >= ADDR_DATA && address < ADDR_DATA + MEMORY_DATA_SIZE) {
        return memoryData[address - ADDR_DATA];
    }
    if (address >= ADDR_GETC && address < ADDR_GETC + 4) {
        return static_cast<int8_t>((getchar() >> ((3 - address + ADDR_GETC) * 8)) & MASK_BYTE);
    }

    cerr << "Attempted to read a byte from an invalid or write-only memory address." << endl;
    exit(ERROR_CPU_EXCEPTION);
}

uint16_t System::readMemoryHalfWord(uint32_t address) {
    if (address % HALF_WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to read a half word on a non aligned memory address." << endl;
        exit(ERROR_CPU_EXCEPTION);
    }

    if (address >= ADDR_GETC && address < ADDR_GETC + 2) {
        return static_cast<int8_t>((getchar() >> ((1 - address + ADDR_GETC) * 16)) & MASK_HALF_WORD);
    }

    int16_t result = 0;
    for (int8_t i = 0; i < HALF_WORD_SIZE_IN_BYTES; i++) {
        result += readMemoryByte(address + i) << (8 * (HALF_WORD_SIZE_IN_BYTES - i - 1));
    }
    return result;
}

void System::writeMemoryWord(uint32_t address, uint32_t word) {
    if (address % WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to write a word on a non aligned memory address." << endl;
        exit(ERROR_CPU_EXCEPTION);
    }

    if (address == ADDR_PUTC) {
        putchar(word);
        return;
    }

    for (int8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
        auto byte = static_cast<int8_t>(word >> (8 * (WORD_SIZE_IN_BYTES - i - 1)) & MASK_BYTE);
        writeMemoryByte(address + i, byte);
    }
}

void System::writeMemoryByte(uint32_t address, uint8_t byte) {
    if (address >= ADDR_DATA && address < ADDR_DATA + MEMORY_DATA_SIZE) {
        memoryData[address - ADDR_DATA] = byte;
        return;
    }
    if (address >= ADDR_PUTC && address < ADDR_PUTC + 4) {
        putchar(byte << ((3 - address + ADDR_PUTC) * 8));
        return;
    }

    cerr << "Attempted to write to an invalid or read-only memory address." << endl;
    exit(ERROR_CPU_EXCEPTION);
}

void System::writeMemoryHalfWord(uint32_t address, uint16_t halfWord) {
    if (address % HALF_WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to write a half word on a non aligned memory address." << endl;
        exit(ERROR_CPU_EXCEPTION);
    }

    if (address >= ADDR_PUTC && address < ADDR_PUTC + 2) {
        putchar(halfWord << ((1 - address + ADDR_PUTC) * 16));
        return;
    }

    for (int8_t i = 0; i < HALF_WORD_SIZE_IN_BYTES; i++) {
        auto byte = static_cast<int8_t>(halfWord >> (8 * (HALF_WORD_SIZE_IN_BYTES - i - 1)) & MASK_BYTE);
        writeMemoryByte(address + i, byte);
    }
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
    return static_cast<uint8_t>(readRegister(2) & MASK_BYTE);
}

void System::executeRTypeInstruction(Instruction *instruction) {
    switch (instruction->getFunctionCode()) {
        case SLL: _sll(instruction); break;
        case SRL: _srl(instruction); break;
        case SRA: _sra(instruction); break;
        case ADD: _add(instruction); break;
        case ADDU: _addu(instruction); break;
        case SUB: _sub(instruction); break;
        case SUBU: _subu(instruction); break;
        case AND: _and(instruction); break;
        case OR: _or(instruction); break;
        case XOR: _xor(instruction); break;
        case NOR: _nor(instruction); break;
        case SLT: _slt(instruction); break;
        case SLTU: _sltu(instruction); break;
        case JR: _jr(instruction); break;
        case JALR: _jalr(instruction); break;
        case DIV: _div(instruction); break;
        case DIVU: _divu(instruction); break;
        case MFHI: _mfhi(instruction); break;
        case MFLO: _mflo(instruction); break;
        case MTHI: _mthi(instruction); break;
        case MTLO: _mtlo(instruction); break;
        case MULT: _mult(instruction); break;
        case MULTU: _multu(instruction); break;
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
    int64_t result = static_cast<int64_t>(readRegister(instruction->getRegisterS())) +
                     static_cast<int64_t>(readRegister(instruction->getRegisterT()));

    if (result > INT32_MAX || result < INT32_MIN) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterD(), static_cast<uint32_t>(result));
}

void System::_addu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) +
                  readRegister(instruction->getRegisterT()));
}

void System::_sub(Instruction *instruction) {

}

void System::_subu(Instruction *instruction) {

}

void System::_and(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) &
                  readRegister(instruction->getRegisterT()));
}

void System::_or(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) |
                  readRegister(instruction->getRegisterT()));
}

void System::_xor(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) ^
                  readRegister(instruction->getRegisterT()));
}

void System::_nor(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  ~(readRegister(instruction->getRegisterS()) |
                    readRegister(instruction->getRegisterT())));
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
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) +
                  instruction->getImmediateOperand());
}

void System::_slti(Instruction *instruction) {

}

void System::_sltiu(Instruction *instruction) {

}

void System::_andi(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) &
                  instruction->getImmediateOperand());
}

void System::_ori(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) |
                  instruction->getImmediateOperand());
}

void System::_xori(Instruction *instruction) {

}

void System::_lui(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  instruction->getImmediateOperand() << 16);
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
    writeRegister(instruction->getRegisterT(),
                  readMemoryByte(instruction->getImmediateOperand() + instruction->getRegisterS()));
}

void System::_lh(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryHalfWord(instruction->getImmediateOperand() + instruction->getRegisterS()));
}

void System::_lbu(Instruction *instruction) {

}

void System::_lw(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryWord(instruction->getImmediateOperand() + instruction->getRegisterS()));
}

void System::_sb(Instruction *instruction) {

}

void System::_sh(Instruction *instruction) {

}

void System::_sw(Instruction *instruction) {
    writeMemoryWord(readRegister(instruction->getRegisterS()) + instruction->getImmediateOperand(),
                    readRegister(instruction->getRegisterT()));
}

void System::_addi(Instruction *instruction) {
    int64_t result = static_cast<uint64_t>(readRegister(instruction->getRegisterS())) +
                     static_cast<uint64_t>(instruction->getImmediateOperand());

    if (result > INT32_MAX || result < INT32_MIN) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterT(), static_cast<uint32_t>(result));
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
