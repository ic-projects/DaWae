# ns4516
# SRAV 0 by 12
    .globl entry

entry:
    li $t2, 12
    srav $v0, $t1, $t2
    jr $zero
