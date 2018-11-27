# qf316
# BEQ on -16 and -16 should branch
    .globl entry

entry:
    li $t0, -16
    li $t1, -16
    beq $t0, $t1, exit
    add $v0, $zero, 50

exit:
    jr $zero
