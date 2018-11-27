# ns4516
# SLLV 2 by only lower 5 bits of t1 register (2)
    .globl entry

entry:
    li $t0, 2
    li $t1, 0x1FFFFFFE2
    sllv $v0, $t0, $t1
    jr $zero
