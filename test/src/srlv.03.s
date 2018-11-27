# ns4516
# SRLV all 1s by 31, inserting 0s
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 31
    srlv $v0, $t0, $t1
    jr $zero
