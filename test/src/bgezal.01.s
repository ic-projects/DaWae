# qf316
# BGEZAL on -16 should not branch
    .globl entry

entry:
    li $t0, -16
    bgezal $t0, other
    jr $zero

other:
    add $v0, $31, 0
    jr $zero
