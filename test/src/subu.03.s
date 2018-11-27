# ns4516
# SUBU 0 and -5
    .globl entry

entry:
    li $t1, 0
    li $t2, -5
    subu $v0, $t1, $t2
    jr $zero
