# qf316
# BLTZ on -16 should branch
    .globl entry

entry:
    li $t0, -16
    bltz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
