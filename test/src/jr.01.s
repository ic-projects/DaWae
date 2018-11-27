# qf316
# JR should jump to address specified in register
    .globl entry

entry:
    li $t0, 0x10000000
    li $t2, 5
    beq $t1, $t2, exit
    add $t1, $t1, 1
    jr $t0

exit:
    add $v0, $t1, 0
    jr $zero
