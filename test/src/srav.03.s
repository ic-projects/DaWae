# ns4516
# SRAV 0xFFFFFFFF by 31
    .globl entry

entry:
    li $t1, 0xFFFFFFFF
    li $t2, 31
    srav $v0, $t1, $t2
    jr $zero
