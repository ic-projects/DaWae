# ns4516
# MULTU 0xFFFFFFFF by 0xFFFFFFFF checking HI
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0xFFFFFFFF
    multu $t0, $t1
    mfhi $v0
    jr $zero
