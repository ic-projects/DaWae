#include <iostream>
#include <bitset>
#include "System.h"
#include "Instruction.h"
#include "Errors.h"
#include <limits>

void System::start() {
    while (pc != ADDR_NULL) {
        if (pc >= ADDR_INSTR && pc <= ADDR_INSTR + MEMORY_INSTR_SIZE) {
            auto *instruction = new Instruction(readMemoryWord(pc));
            executeInstruction(instruction);
        } else {
            cerr << "Attempted to execute an instruction outside of executable memory" << endl;
            exit(ERROR_CPU_EXCEPTION);
        }

        if (updatePC) {
            incrementPC(WORD_SIZE_IN_BYTES);
        }
        updatePC = true;
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
        case JAL: _jal(instruction); break;
    }
}

uint32_t System::readMemoryWord(uint32_t address) {
    if (address % WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to read a word on a non aligned memory address " << std::hex << address << endl;
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
    if (address >= ADDR_INSTR && address < ADDR_INSTR + MEMORY_INSTR_SIZE) {
        return memoryInstr[address - ADDR_INSTR];
    }
    if (address >= ADDR_DATA && address < ADDR_DATA + MEMORY_DATA_SIZE) {
        return memoryData[address - ADDR_DATA];
    }
    if (address >= ADDR_GETC && address < ADDR_GETC + 4) {
        return static_cast<uint8_t>((getchar() >> ((3 - address + ADDR_GETC) * 8)) & MASK_BYTE);
    }

    cerr << "Attempted to read a byte from an invalid or write-only memory address " << std::hex << address << endl;
    exit(ERROR_CPU_EXCEPTION);
}

uint16_t System::readMemoryHalfWord(uint32_t address) {
    if (address % HALF_WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to read a half word on a non aligned memory address " << std::hex << address << endl;
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
        cerr << "Attempted to write a word on a non aligned memory address " << std::hex << address << endl;
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

    cerr << "Attempted to write to an invalid or read-only memory address " << std::hex << address << endl;
    exit(ERROR_CPU_EXCEPTION);
}

void System::writeMemoryHalfWord(uint32_t address, uint16_t halfWord) {
    if (address % HALF_WORD_SIZE_IN_BYTES != 0) {
        cerr << "Attempted to write a half word on a non aligned memory address " << std::hex << address << endl;
        exit(ERROR_CPU_EXCEPTION);
    }

    if (address == ADDR_PUTC || address == ADDR_PUTC + WORD_SIZE_IN_BYTES) {
        putchar(halfWord << ((1 - (address + ADDR_PUTC) / 2) * 16));
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
        cerr << "Attempted to write to an invalid register " << std::hex << reg << endl;
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
        case SLLV: _sllv(instruction); break;
        case SRAV: _srav(instruction); break;
        case SRLV: _srlv(instruction); break;
    }
}

// R-Type Instructions
void System::_sll(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterT()) <<
                  instruction->getShiftAmount());
}

void System::_srl(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterT()) >>
                  instruction->getShiftAmount());
}

void System::_sra(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  static_cast<uint32_t>(static_cast<int32_t>(static_cast<int32_t>(readRegister(instruction->getRegisterT())) >>
                                        instruction->getShiftAmount())));
}

void System::_add(Instruction *instruction) {
    auto s = static_cast<int32_t>(readRegister(instruction->getRegisterS()));
    auto t = static_cast<int32_t>(readRegister(instruction->getRegisterT()));

    if ((t > 0 && s > INT32_MAX - t) ||
        (t < 0 && s < INT32_MIN - t)) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterD(), static_cast<uint32_t>(s + t));
}

void System::_addu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) +
                  readRegister(instruction->getRegisterT()));
}

void System::_sub(Instruction *instruction) {
    auto s = static_cast<int32_t>(readRegister(instruction->getRegisterS()));
    auto t = static_cast<int32_t>(readRegister(instruction->getRegisterT()));

    if ((t < 0 && s > INT32_MAX + t) ||
        (t > 0 && s < INT32_MIN + t)) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterD(), static_cast<uint32_t>(s - t));
}

void System::_subu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) - readRegister(instruction->getRegisterT()));
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

void System::_slt(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  static_cast<int32_t>(readRegister(instruction->getRegisterS())) <
                  static_cast<int32_t>(readRegister(instruction->getRegisterT())) ? 1 : 0);
}

void System::_sltu(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterS()) <
                  readRegister(instruction->getRegisterT()) ? 1 : 0);
}

void System::_jr(Instruction *instruction) {
    setPC(readRegister(instruction->getRegisterS()));
}

void System::_jalr(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(), nextPC + WORD_SIZE_IN_BYTES);
    setPC(readRegister(instruction->getRegisterS()));
}

void System::_div(Instruction *instruction) {
    int32_t num = readRegister(instruction->getRegisterS());
    int32_t denom = readRegister(instruction->getRegisterT());
    if (denom != 0) {
        hi = static_cast<uint32_t>(num % denom);
        lo = static_cast<uint32_t>(num / denom);
    }
}

void System::_divu(Instruction *instruction) {
    uint32_t num = readRegister(instruction->getRegisterS());
    uint32_t denom = readRegister(instruction->getRegisterT());
    if (denom != 0) {
        hi = num % denom;
        lo = num / denom;
    }
}

void System::_mfhi(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(), hi);
}

void System::_mflo(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(), lo);
}

void System::_mthi(Instruction *instruction) {
    uint32_t word = readRegister(instruction->getRegisterS());
    hi = word;
}

void System::_mtlo(Instruction *instruction) {
    uint32_t word = readRegister(instruction->getRegisterS());
    lo = word;
}

void System::_mult(Instruction *instruction) {
    int64_t result = static_cast<int64_t>(static_cast<int32_t>(readRegister(instruction->getRegisterS()))) *
                     static_cast<int64_t>(static_cast<int32_t>(readRegister(instruction->getRegisterT())));
    hi = static_cast<uint32_t>(result >> 32);
    lo = static_cast<uint32_t>(result);
}

void System::_multu(Instruction *instruction) {
    uint64_t result = static_cast<uint64_t>(readRegister(instruction->getRegisterS())) *
                      static_cast<uint64_t>(readRegister(instruction->getRegisterT()));
    hi = static_cast<uint32_t>(result >> 32);
    lo = static_cast<uint32_t>(result);
}

void System::_addiu(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) +
                  static_cast<int16_t>(instruction->getImmediateOperand()));
}

void System::_slti(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  static_cast<int32_t>(readRegister(instruction->getRegisterS())) <
                  static_cast<int16_t>(instruction->getImmediateOperand()) ? 1 : 0);
}

void System::_sltiu(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) <
                  static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(instruction->getImmediateOperand()))) ? 1 : 0);
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
    writeRegister(instruction->getRegisterT(),
                  readRegister(instruction->getRegisterS()) ^
                  instruction->getImmediateOperand());
}

void System::_lui(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  instruction->getImmediateOperand() << 16);
}

void System::_beq(Instruction *instruction) {
    if (readRegister(instruction->getRegisterS()) ==
        readRegister(instruction->getRegisterT())) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_bne(Instruction *instruction) {
    if (readRegister(instruction->getRegisterS()) !=
        readRegister(instruction->getRegisterT())) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_blez(Instruction *instruction) {
    if (static_cast<int32_t>(readRegister(instruction->getRegisterS())) <= 0) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_bgtz(Instruction *instruction) {
    if (static_cast<int32_t>(readRegister(instruction->getRegisterS())) > 0) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_b_spec(Instruction *instruction) {
    switch (instruction->getBCode()) {
        case BGEZ: _bgez(instruction); break;
        case BGEZAL: _bgezal(instruction); break;
        case BLTZ: _bltz(instruction); break;
        case BLTZAL: _bltzal(instruction); break;
    }
}

void System::_lb(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(readMemoryByte(static_cast<int16_t>(instruction->getImmediateOperand()) +
                                                                                                readRegister(instruction->getRegisterS()))))));
}

void System::_lh(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryHalfWord(static_cast<int16_t>(instruction->getImmediateOperand()) +
                                     readRegister(instruction->getRegisterS())));
}

void System::_lw(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryWord(static_cast<int16_t>(instruction->getImmediateOperand()) +
                                 readRegister(instruction->getRegisterS())));
}

void System::_sb(Instruction *instruction) {
    writeMemoryByte(readRegister(instruction->getRegisterS()) +
                    static_cast<int16_t>(instruction->getImmediateOperand()),
                    static_cast<uint8_t>(readRegister(instruction->getRegisterT()) & MASK_BYTE));
}

void System::_sh(Instruction *instruction) {
    writeMemoryHalfWord(readRegister(instruction->getRegisterS()) +
                        static_cast<int16_t>(instruction->getImmediateOperand()),
                        static_cast<uint16_t>(readRegister(instruction->getRegisterT()) & MASK_HALF_WORD));
}

void System::_sw(Instruction *instruction) {
    writeMemoryWord(readRegister(instruction->getRegisterS()) +
                    static_cast<int16_t>(instruction->getImmediateOperand()),
                    readRegister(instruction->getRegisterT()));
}

void System::_addi(Instruction *instruction) {
    auto s = static_cast<int32_t>(readRegister(instruction->getRegisterS()));
    auto imm = static_cast<int16_t>(instruction->getImmediateOperand());

    if ((imm > 0 && s > INT32_MAX - imm) ||
        (imm < 0 && s < INT32_MIN - imm)) {
        exit(ERROR_ARITHMETIC);
    }

    writeRegister(instruction->getRegisterT(), static_cast<uint32_t>(s + imm));
}

void System::_lbu(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryByte(readRegister(instruction->getRegisterS()) +
                                 static_cast<int16_t>(instruction->getImmediateOperand())));
}

void System::_lhu(Instruction *instruction) {
    writeRegister(instruction->getRegisterT(),
                  readMemoryHalfWord(readRegister(instruction->getRegisterS()) +
                                     static_cast<int16_t>(instruction->getImmediateOperand())));
}

void System::_lwl(Instruction *instruction) {
    uint32_t address = readRegister(instruction->getRegisterS()) + static_cast<int16_t>(instruction->getImmediateOperand());
    uint32_t remainder = address % WORD_SIZE_IN_BYTES;
    uint32_t maskedMemoryData = readMemoryWord(address - remainder) & (0xFFFFFFFF >> (8 * remainder)) << (8 * remainder);
    uint32_t maskedRegisterData = readRegister(instruction->getRegisterT()) & (0xFFFFFFFF >> (8 * (3 - remainder)));

    writeRegister(instruction->getRegisterT(),
                  maskedMemoryData | maskedRegisterData);
}

void System::_lwr(Instruction *instruction) {
    uint32_t address = readRegister(instruction->getRegisterS()) + static_cast<int16_t>(instruction->getImmediateOperand());
    uint32_t remainder = address % WORD_SIZE_IN_BYTES;
    uint32_t maskedMemoryData = readMemoryWord(address - remainder) >> (8 * (3 - remainder));
    uint32_t maskedRegisterData = (readRegister(instruction->getRegisterT()) >> (8 * remainder)) << (8 * remainder);

    writeRegister(instruction->getRegisterT(),
                  maskedMemoryData | maskedRegisterData);
}

void System::_sllv(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterT()) <<
                  (readRegister(instruction->getRegisterS()) & 0x1F));
}

void System::_srav(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  static_cast<uint32_t>(static_cast<int32_t>(readRegister(instruction->getRegisterT())) >>
                                        readRegister(instruction->getRegisterS())));
}

void System::_srlv(Instruction *instruction) {
    writeRegister(instruction->getRegisterD(),
                  readRegister(instruction->getRegisterT()) >>
                  readRegister(instruction->getRegisterS()));
}

void System::_j(Instruction *instruction) {
    setPC((pc & 0xF0000000) | (instruction->getJumpAddress() << 2));
}

void System::_jal(Instruction *instruction) {
    writeRegister(31, nextPC + WORD_SIZE_IN_BYTES);
    setPC((pc & 0xF0000000) | (instruction->getJumpAddress() << 2));
}

void System::setPC(uint32_t address) {
    updatePC = false;
    pc = nextPC;
    nextPC = address;
}

void System::incrementPC(uint32_t offset) {
    setPC(nextPC + static_cast<int32_t>(offset));
}

// Special B-Type functions
void System::_bgezal(Instruction *instruction) {
    writeRegister(31, nextPC + WORD_SIZE_IN_BYTES);
    if (static_cast<int32_t>(readRegister(instruction->getRegisterS())) >= 0) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_bgez(Instruction *instruction) {
    if (static_cast<int32_t>(readRegister(instruction->getRegisterS())) >= 0) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_bltz(Instruction *instruction) {
    if (static_cast<int32_t>(readRegister(instruction->getRegisterS())) < 0) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}

void System::_bltzal(Instruction *instruction) {
    writeRegister(31, nextPC + WORD_SIZE_IN_BYTES);
    if (static_cast<int32_t>(readRegister(instruction->getRegisterS())) < 0) {
        incrementPC(static_cast<uint32_t>(static_cast<int16_t>(instruction->getImmediateOperand()) << 2));
    }
}
