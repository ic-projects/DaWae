# qf316
# BEQ on -16 and 0 should not branch
    .globl entry

entry:
    li $t0, -16
    li $t1, 0
    beq $t0, $t1, exit
    add $v0, $zero, 50

exit:
    jr $zero
