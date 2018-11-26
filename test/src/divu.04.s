# ns4516
# DIVU -24 by 3 checking remainder
    .globl entry

entry:
    li $t0, -24
    li $t1, 3
    divu $t0, $t1
    mfhi $v0
    jr $zero
