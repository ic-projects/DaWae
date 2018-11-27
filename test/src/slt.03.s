# ns4516
# SLT Check 20 is not less than 5
    .globl entry

entry:
    li $t0, 20
    li $t1, 5
    slt $v0, $t0, $t1
    jr $zero
