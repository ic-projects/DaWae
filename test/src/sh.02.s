# ns4516
# SH 0xFF in 0x1FFFFFFF with exception
    .globl entry

entry:
    li $t0, 0xFFFF
    sh $t0, 0x1FFFFFFF($zero)
    jr $zero
