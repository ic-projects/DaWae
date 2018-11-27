# ns4516
# SLLV 2 by 0
    .globl entry

entry:
    li $t0, 2
    sllv $v0, $t0, $t1
    jr $zero
