# qf316
# BEQ on 2147483647 (MAX_INT) and -2147483648 (MIN_INT) should not branch
    .globl entry

entry:
    li $t0, 2147483647
    li $t1, -2147483648
    beq $t0, $t1, exit
    add $v0, $zero, 50

exit:
    jr $zero
