# ns4516
# SB 0xF in 0x1FFFFFFF with exception
    .globl entry

entry:
    li $t0, 0xF
    sb $t0, 0x1FFFFFFF($zero)
    jr $zero
