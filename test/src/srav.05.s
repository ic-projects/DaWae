# ns4516
# SRAV 12 by 0
    .globl entry

entry:
    li $t1, 12
    srav $v0, $t1, $t2
    jr $zero
