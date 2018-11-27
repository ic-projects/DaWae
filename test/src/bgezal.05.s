# qf316
# BGEZAL on 0 should branch
    .globl entry
    .set noreorder

entry:
    bgezal $t0, other
    nop
    jr $zero # Instruction at address 8

other:
    add $v0, $31, 0
    jr $zero
