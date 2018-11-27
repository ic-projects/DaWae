# qf316
# BGEZAL on -2147483648 (MIN_INT) should not branch
    .globl entry

entry:
    li $t0, -2147483648
    bgezal $t0, other
    jr $zero

other:
    add $v0, $31, 0
    jr $zero
