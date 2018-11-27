# ns4516
# SUBU 100 and 17
    .globl entry

entry:
    li $t1, 100
    li $t2, 17
    subu $v0, $t1, $t2
    jr $zero
