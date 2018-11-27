# ns4516
# SRA 0xD80000CC by 27
    .globl entry

entry:
    li $t1, 0xD80000CC        #11011000000000000000000011001100
    sra $v0, $t1, 27          #1...11111011 -> 251
    jr $zero
