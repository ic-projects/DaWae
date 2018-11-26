# ns4516
# SH 0xFFFF in 0x200000FF with -255 offset without exception
    .globl entry

entry:
    li $t0, 0xFFFF
    li $t1, 0x200000FF
    sh $t0, -255($t1)
    jr $zero
