# ns4516
# SW 0xFFFFFFFF in 0x1FFFFFFF with exception
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    sw $t0, 0x1FFFFFFF($zero)
    jr $zero
