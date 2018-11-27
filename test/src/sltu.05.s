# ns4516
# SLTU Check 55 is less than 56
    .globl entry

entry:
    li $t0, 55
    li $t1, 56
    sltu $v0, $t0, $t1
    jr $zero
