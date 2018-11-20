#include <iostream>
#include <bitset>
#include "Instruction.h"

using namespace std;

InstructionOpcode Instruction::getOpcode() {
    return (InstructionOpcode) (instruction >> SHIFT_OPCODE);
}

int8_t Instruction::getRegisterS() {
    return static_cast<int8_t>((instruction >> SHIFT_REG_S) & MASK_REG);
}

int8_t Instruction::getRegisterT() {
    return static_cast<int8_t>((instruction >> SHIFT_REG_T) & MASK_REG);
}

int8_t Instruction::getRegisterD() {
    return static_cast<int8_t>((instruction >> SHIFT_RED_D) & MASK_REG);
}

void Instruction::printRaw() {
    char buffer[50];
    sprintf(buffer, "0x%08x", instruction);
    cout << buffer << endl;
}

int8_t Instruction::getShiftAmount() {
    return static_cast<int8_t>((instruction >> SHIFT_SHIFT_AMOUNT) & MASK_REG);
}

RTypeFunctionCode Instruction::getFunctionCode() {
    return static_cast<RTypeFunctionCode>(instruction & MASK_FUNCTION_CODE);
}

int16_t Instruction::getImmediateOperand() {
    return static_cast<int16_t>(instruction & MASK_IMMEDIATE_OPERAND);
}

int32_t Instruction::getJumpAddress() {
    return instruction & MASK_JUMP_ADDRESS;
}

int32_t Instruction::getRaw() {
    return instruction;
}
