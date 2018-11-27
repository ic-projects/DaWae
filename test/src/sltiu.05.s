# ns4516
# SLTUI Check 55 is less than 56
    .globl entry

entry:
    li $t0, 55
    sltiu $v0, $t0, 56
    jr $zero
