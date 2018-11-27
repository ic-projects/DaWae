# ns4516
# SLLV -9 by 3
    .globl entry

entry:
    li $t0, -9
    li $t1, 3
    sllv $v0, $t0, $t1
    jr $zero
