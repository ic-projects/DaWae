# ns4516
# SRA 32 by 3
    .globl entry

entry:
    li $t1, 32
    sra $v0, $t1, 3
    jr $zero
