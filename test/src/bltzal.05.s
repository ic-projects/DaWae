# qf316
# BLTZAL on 0 should not branch
    .globl entry

entry:
    bltzal $t0, other
    jr $zero

other:
    add $v0, $31, 0
    jr $zero
