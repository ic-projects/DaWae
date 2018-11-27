# ns4516
# SRAV 0xD80000CC by 27
    .globl entry

entry:
    li $t1, 0xD80000CC        #11011000000000000000000011001100
    li $t2, 27
    srav $v0, $t1, $t2         #1...11111011 -> 251
    jr $zero
