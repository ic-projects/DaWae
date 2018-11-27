# ns4516
# SLT Check -99 is less than 5
    .globl entry

entry:
    li $t0, -99
    li $t1, 20
    slt $v0, $t0, $t1
    jr $zero
