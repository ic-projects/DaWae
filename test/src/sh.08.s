# ns4516
# SH 0xFFFF in 0x200000FF with -256 offset with exception
    .globl entry

entry:
    li $t0, 0xFFFF
    li $t1, 0x20000000
    sh $t0, -256($t1)
    jr $zero
