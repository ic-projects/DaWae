# ns4516
# SLTUI Check 0 is not less than 0
    .globl entry

entry:
    sltiu $v0, $t0, 0
    jr $zero
