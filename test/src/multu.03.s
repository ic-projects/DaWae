# ns4516
# MULTU -25 by -5 checking LO
    .globl entry

entry:
    li $t0, -25
    li $t1, -5
    multu $t0, $t1
    mflo $v0
    jr $zero
