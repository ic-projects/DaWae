# qf316
# BLTZ on -2147483648 (MIN_INT) should branch
    .globl entry

entry:
    li $t0, -2147483648
    bltz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
