# qf316
# BGEZAL on 1 should branch
    .globl entry
    .set noreorder

entry:
    addiu $t0, $zero, 1
    bgezal $t0, other
    nop
    jr $zero # Instruction at address 12

other:
    add $v0, $31, 0
    jr $zero
