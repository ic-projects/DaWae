# qf316
# BLEZ on -16 should branch
    .globl entry

entry:
    li $t0, -16
    blez $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
