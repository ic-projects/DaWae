# ns4516
# SLLV -72 by 3
    .globl entry

entry:
    li $t0, -72
    li $t1, 3
    srlv $v0, $t0, $t1
    jr $zero
