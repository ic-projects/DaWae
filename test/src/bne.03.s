# qf316
# BNE on 1 and 0 should branch
    .globl entry

entry:
    li $t0, 1
    li $t1, 0
    bne $t0, $t1, exit
    add $v0, $zero, 50

exit:
    jr $zero
