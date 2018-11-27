# qf316
# BGTZ on -2147483648 (MIN_INT) should not branch
    .globl entry

entry:
    li $t0, -2147483648
    bgtz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
