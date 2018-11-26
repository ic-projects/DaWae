# ns4516
# SB 0xFF in 0x1FFFFFFF with exception
    .globl entry

entry:
    li $t0, 0xFF
    sb $t0, 0x1FFFFFFF($zero)
    jr $zero
