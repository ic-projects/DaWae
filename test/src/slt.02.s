# ns4516
# SLT Check 0 is not less than 0
    .globl entry

entry:
    slt $v0, $t0, $t1
    jr $zero
