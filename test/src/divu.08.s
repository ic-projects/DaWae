# ns4516
# DIVU -112 by 12 checking remainder
    .globl entry

entry:
    li $t0, -112
    li $t1, 12
    divu $t0, $t1
    mfhi $v0
    jr $zero
