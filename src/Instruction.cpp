#include <iostream>
#include <bitset>
#include "Instruction.h"

using namespace std;

InstructionOpcode Instruction::getOpcode() {
    return (InstructionOpcode) (instruction >> OPCODE_SHIFT);
}

uint8_t Instruction::getRegisterS() {
    return static_cast<uint8_t>((instruction >> REG_S_SHIFT) & REG_MASK);
}

uint8_t Instruction::getRegisterT() {
    return static_cast<uint8_t>((instruction >> REG_T_SHIFT) & REG_MASK);
}

uint8_t Instruction::getRegisterD() {
    return static_cast<uint8_t>((instruction >> REG_D_SHIFT) & REG_MASK);
}

void Instruction::printRaw() {
    cout << bitset<WORD_SIZE_IN_BYTES * 8>(instruction) << endl;
}
