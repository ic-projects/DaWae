# qf316
# BLTZ on 2147483647 (MAX_INT) should not branch
    .globl entry

entry:
    li $t0, 2147483647
    bltz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
