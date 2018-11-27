# ns4516
# SRLV 128 by 3
    .globl entry

entry:
    li $v0, 128
    li $t1, 3
    srlv $v0, $v0, $t1
    jr $zero
