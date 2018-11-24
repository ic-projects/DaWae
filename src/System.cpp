#include <iostream>
#include <bitset>
#include "System.h"
#include "Instruction.h"
#include "Errors.h"
#include <limits>

void System::start() {
    while (pc != ADDR_NULL) {
        // Execute
        if (decodedInstruction != nullptr) {
            executeInstruction(decodedInstruction);
        }

        // Decode
        if (hasStarted) {
            decodedInstruction = new Instruction(fetchedInstruction);
        } else {
            hasStarted = true;
        }

        // Fetch
        if (pc != ADDR_NULL) {
            fetchedInstruction = readMemoryWord(pc);
        }
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
        return static_cast<uint32_t>(getchar());
    }

    uint32_t result = 0;
    for (uint8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
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
        return static_cast<uint8_t>((getchar() >> ((3 - address + ADDR_GETC) * 8)) & MASK_BYTE);
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
        return static_cast<uint8_t>((getchar() >> ((1 - address + ADDR_GETC) * 16)) & MASK_HALF_WORD);
    }

    uint16_t result = 0;
    for (uint8_t i = 0; i < HALF_WORD_SIZE_IN_BYTES; i++) {
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

    for (uint8_t i = 0; i < WORD_SIZE_IN_BYTES; i++) {
        auto byte = static_cast<uint8_t>(word >> (8 * (WORD_SIZE_IN_BYTES - i - 1)) & MASK_BYTE);
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

    for (uint8_t i = 0; i < HALF_WORD_SIZE_IN_BYTES; i++) {
        auto byte = static_cast<uint8_t>(halfWord >> (8 * (HALF_WORD_SIZE_IN_BYTES - i - 1)) & MASK_BYTE);
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

void System::writeHIRegister(uint32_t word) {
    hi = word;
}
void System::writeLORegister(uint32_t word) {
    lo = word;
}
uint32_t System::readHIRegister() {
    return hi;
}
uint32_t System::readLORegister() {
    return lo;
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
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterT() <<
                  instruction->getShiftAmount()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_srl(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  (uint32_t)readRegister(instruction->getRegisterT() >>
                  instruction->getShiftAmount()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sra(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  (int32_t)readRegister(instruction->getRegisterT() >>
                  instruction->getShiftAmount()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_add(Instruction *instruction) {
    auto s = static_cast<int32_t>(readRegister(instruction->getRegisterS()));
    auto t = static_cast<int32_t>(readRegister(instruction->getRegisterT()));

    if ((t > 0 && s > INT32_MAX - t) ||
        (t < 0 && s < INT32_MIN - t)) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterD(), static_cast<uint32_t>(s + t));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_addu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) +
                  readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sub(Instruction *instruction) {
    auto s = static_cast<int32_t>(readRegister(instruction->getRegisterS()));
    auto t = static_cast<int32_t>(readRegister(instruction->getRegisterT()));

    if ((t < 0 && s > INT32_MAX + t) ||
        (t > 0 && s < INT32_MIN + t)) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterD(), static_cast<uint32_t>(s - t));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_subu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) - readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_and(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) &
                  readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_or(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) |
                  readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_xor(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) ^
                  readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_nor(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  ~(readRegister(instruction->getRegisterS()) |
                    readRegister(instruction->getRegisterT())));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_slt(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  (int32_t) readRegister(instruction->getRegisterS()) <
                  (int32_t) readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sltu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  (uint32_t) readRegister(instruction->getRegisterS()) <
                  (uint32_t) readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_jr(Instruction *instruction) {
    pc = readRegister(instruction->getRegisterS());
}

void System::_jalr(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_div(Instruction *instruction) {
    int32_t denom = readRegister(instruction->getRegisterS());
    int32_t num   = readRegister(instruction->getRegisterT());
    if (denom == 0) {
        pc += WORD_SIZE_IN_BYTES;
        return;
    }

    writeHIRegister((int32_t) num / denom);
    writeLORegister((int32_t) num % denom);
    pc += WORD_SIZE_IN_BYTES;
}

void System::_divu(Instruction *instruction) {
    uint32_t denom = readRegister(instruction->getRegisterS());
    uint32_t num   = readRegister(instruction->getRegisterT());
    if (denom == 0) {
        pc += WORD_SIZE_IN_BYTES;
        return;
    }

    writeHIRegister(num / denom);
    writeLORegister(num % denom);
    pc += WORD_SIZE_IN_BYTES;
}

void System::_mfhi(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(), readHIRegister());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_mflo(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(), readLORegister());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_mthi(Instruction *instruction) {
    writeHIRegister(readRegister(instruction->getRegisterS()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_mtlo(Instruction *instruction) {
    writeLORegister(readRegister(instruction->getRegisterS()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_mult(Instruction *instruction) {
    int64_t result = (int32_t) readRegister(instruction->getRegisterS()) *
                      (int32_t)readRegister(instruction->getRegisterT());
    writeHIRegister((uint32_t) ((result & 0xFFFFFFFF00000000) >> 32));
    writeLORegister((uint32_t) (result & 0xFFFFFFFF));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_multu(Instruction *instruction) {
    uint64_t result = (uint32_t) readRegister(instruction->getRegisterS()) *
                     (uint32_t)readRegister(instruction->getRegisterT());
    writeHIRegister((uint32_t) ((result & 0xFFFFFFFF00000000) >> 32));
    writeLORegister((uint32_t) (result & 0xFFFFFFFF));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_addiu(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) +
                  instruction->getImmediateOperand());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_slti(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  (int32_t) readRegister(instruction->getRegisterS()) <
                  (int16_t) instruction->getImmediateOperand());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sltiu(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  (uint32_t) readRegister(instruction->getRegisterS()) <
                  (uint16_t) instruction->getImmediateOperand());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_andi(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) &
                  instruction->getImmediateOperand());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_ori(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) |
                  instruction->getImmediateOperand());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_xori(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) ^
                  instruction->getImmediateOperand());
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lui(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  instruction->getImmediateOperand() << 16);
    pc += WORD_SIZE_IN_BYTES;
}

void System::_beq(Instruction *instruction) {
    if (readRegister(instruction->getRegisterS()) ==
        readRegister(instruction->getRegisterT())) {
        pc += static_cast<uint16_t>(instruction->getImmediateOperand()) << 2;
    } else {
        pc += WORD_SIZE_IN_BYTES;
    }
}

void System::_bne(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_blez(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_bgtz(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_b_spec(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lb(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryByte(instruction->getImmediateOperand() + instruction->getRegisterS()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lh(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryHalfWord(instruction->getImmediateOperand() + instruction->getRegisterS()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lbu(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lw(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryWord(instruction->getImmediateOperand() + readRegister(instruction->getRegisterS())));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sb(Instruction *instruction) {
    writeMemoryByte(readRegister(instruction->getRegisterS()) + instruction->getImmediateOperand(),
                    (uint8_t) (readRegister(instruction->getRegisterT()) & 0xFF));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sh(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sw(Instruction *instruction) {
    writeMemoryWord(readRegister(instruction->getRegisterS()) + instruction->getImmediateOperand(),
                    readRegister(instruction->getRegisterT()));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_addi(Instruction *instruction) {
    auto s = static_cast<int32_t>(readRegister(instruction->getRegisterS()));
    auto imm = static_cast<int16_t>(instruction->getImmediateOperand());

    if ((imm > 0 && s > INT32_MAX - imm) ||
        (imm < 0 && s < INT32_MIN - imm)) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterT(), static_cast<uint32_t>(s + imm));
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lhu(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lwl(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_lwr(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_sllv(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_srav(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_srlv(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_j(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}

void System::_jal(Instruction *instruction) {
    pc += WORD_SIZE_IN_BYTES;
}
