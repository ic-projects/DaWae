# qf316
# BGEZAL on 2147483647 (MAX_INT) should branch
    .globl entry
    .set noreorder

entry:
    lui $t0, 0x7FFF
    ori $t0, $t0, 0xFFFF
    bgezal $t0, other
    jr $zero # Instruction at address 16

other:
    add $v0, $31, 0
    jr $zero
