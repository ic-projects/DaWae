# qf316
# BLTZAL on -1 should branch
    .globl entry
    .set noreorder

entry:
    li $t0, -1
    bltzal $t0, other
    nop
    jr $zero # Instruction at address 12

other:
    add $v0, $31, 0
    jr $zero
