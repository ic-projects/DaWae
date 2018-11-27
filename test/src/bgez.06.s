# qf316
# BGEZ on -2147483648 (MIN_INT) should not branch
    .globl entry

entry:
    li $t0, -2147483648
    bgez $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
