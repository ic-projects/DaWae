# qf316
# BLTZ on 1 should not branch
    .globl entry

entry:
    li $t0, 1
    bltz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
