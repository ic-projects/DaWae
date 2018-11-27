# ns4516
# SRA 0xFFFFFFFF by 31
    .globl entry

entry:
    li $t1, 0xFFFFFFFF
    sra $v0, $t1, 31
    jr $zero
