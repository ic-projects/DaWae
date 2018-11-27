# ns4516
# SLLV 2 by 3
    .globl entry

entry:
    li $v0, 2
    li $t1, 3
    sllv $v0, $v0, $t1
    jr $zero
