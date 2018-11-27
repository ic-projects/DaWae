# ns4516
# SLTUI Check 20 is not less than 5
    .globl entry

entry:
    li $t0, 20
    sltiu $v0, $t0, 5
    jr $zero
