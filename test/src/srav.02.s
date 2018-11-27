# ns4516
# SRAV 32 by 3
    .globl entry

entry:
    li $t1, 32
    li $t2, 3
    srav $v0, $t1, $t2
    jr $zero
