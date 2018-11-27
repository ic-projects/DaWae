# ns4516
# SLLV 0 by 5
    .globl entry

entry:
    li $t0, 5
    sllv $v0, $v0, $t0
    jr $zero
