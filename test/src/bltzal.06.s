# qf316
# BLTZAL on -2147483648 (MIN_INT) should branch
    .globl entry
    .set noreorder

entry:
    lui $t0, 0xFFFF
    ori $t0, $t0, 0xFFFF
    bltzal $t0, other
    nop
    jr $zero # Instruction at address 16

other:
    add $v0, $31, 0
    jr $zero
