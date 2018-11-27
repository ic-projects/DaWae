# ns4516
# MULT 999 by 0 checking HI
    .globl entry

entry:
    li $t0, 999
    li $t1, 0
    mult $t0, $t1
    mfhi $v0
    jr $zero
