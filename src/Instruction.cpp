#include <iostream>
#include "Instruction.h"

Instruction::Instruction(uint32_t instruction) {
    this->instruction = instruction;
}

InstructionOpcode Instruction::getOpcode() {
    return (InstructionOpcode) (this->instruction >> OPCODE_SHIFT);
}
