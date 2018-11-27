# ns4516
# SLLV all 1s by 31
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 31
    sllv $v0, $t0, $t1
    jr $zero
