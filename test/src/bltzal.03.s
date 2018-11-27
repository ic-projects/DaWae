# qf316
# BLTZAL on 1 should not branch
    .globl entry

entry:
    addiu $t0, $zero, 1
    bltzal $t0, other
    jr $zero

other:
    add $v0, $31, 0
    jr $zero
