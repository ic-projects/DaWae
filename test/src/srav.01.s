# ns4516
# SRAV -1000 by 3 should give -125
    .globl entry

entry:
    li $t1, -1000
    li $t2, 3
    srav $v0, $t1, $t2
    jr $zero
