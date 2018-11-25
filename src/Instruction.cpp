#include <iostream>
#include <bitset>
#include "Instruction.h"

using namespace std;

InstructionOpcode Instruction::getOpcode() {
    return (InstructionOpcode) (instruction >> SHIFT_OPCODE);
}

uint8_t Instruction::getRegisterS() {
    return static_cast<uint8_t>((instruction >> SHIFT_REG_S) & MASK_REG);
}

uint8_t Instruction::getRegisterT() {
    return static_cast<uint8_t>((instruction >> SHIFT_REG_T) & MASK_REG);
}

uint8_t Instruction::getRegisterD() {
    return static_cast<uint8_t>((instruction >> SHIFT_RED_D) & MASK_REG);
}

void Instruction::printRaw() {
    char buffer[50];
    sprintf(buffer, "0x%08x", instruction);
    cout << buffer << endl;
}

uint8_t Instruction::getShiftAmount() {
    return static_cast<uint8_t>((instruction >> SHIFT_SHIFT_AMOUNT) & MASK_REG);
}

RTypeFunctionCode Instruction::getFunctionCode() {
    return static_cast<RTypeFunctionCode>(instruction & MASK_FUNCTION_CODE);
}

uint16_t Instruction::getImmediateOperand() {
    return static_cast<uint16_t>(instruction & MASK_IMMEDIATE_OPERAND);
}

uint32_t Instruction::getJumpAddress() {
    return instruction & MASK_JUMP_ADDRESS;
}

uint32_t Instruction::getRaw() {
    return instruction;
}

BTypeCode Instruction::getBCode() {
    return static_cast<BTypeCode>(getRegisterT());
}
