# ns4516
# SRLV 2 by 0
    .globl entry

entry:
    li $t0, 2
    li $t1, 0
    srlv $v0, $t0, $t1
    jr $zero
