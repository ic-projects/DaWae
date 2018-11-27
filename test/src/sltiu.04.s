# ns4516
# SLTUI Check -99 isn't less than 5
    .globl entry

entry:
    li $t0, -99
    sltiu $v0, $t0, 20
    jr $zero
