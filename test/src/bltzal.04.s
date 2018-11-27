# qf316
# BLTZAL on 2147483647 (MAX_INT) should not branch
    .globl entry

entry:
    li $t0, 0x7FFFFFFF
    bltzal $t0, other
    jr $zero

other:
    add $v0, $31, 0
    jr $zero
