# ns4516
# LH from misaligned memory address 0x20000001
    .globl entry

entry:
    li $t0, 0x20000001
    lh $v0, 0($t0)
    jr $zero
